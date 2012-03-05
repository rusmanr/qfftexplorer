/***************************************************************************
 *   Copyright (C) 2004 by Paul Lutus                                      *
 *   lutusp@pl-alpha                                                       *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/


#include "scopepane.h"
//#include "fftexplorerwin.h"
#include "dataprocessor.h"
#include <iostream>
#include <sstream>
#include <qcombobox.h>
#include <qwhatsthis.h>
#include <qcheckbox.h>



const double ScopePane::scale[] = {
                                      1.0,2.0,5.0,10.0,20.0,50.0,100.0,200.0,500.0,1000.0
                                      ,2000.0,5000.0,10000.0,20000.0,50000.0,100000.0,200000.0,500000.0,0
                                  };

const QColor ScopePane::backgroundColor = QColor(0,0,0);//(255,255,255);
const QColor ScopePane::lineColor = QColor(0,128,0);
const QColor ScopePane::gridColor = QColor(200,200,200);
const QColor ScopePane::textColor = QColor(128,128,128);
const QColor ScopePane::warningColor = QColor(0,0,128);

ScopePane::ScopePane(QWidget *par, fftexplorer *p, bool fd, const char *name)
    : ScopePaneForm(par, name)
{
//ScopePane::ScopePane(QWidget* par, fftexplorer *p,bool fd,const char* name) //, WFlags fl)
//    : QDialog(par)
//{
    parent = p;
    isFreqDisp = fd;
    busy = false;
    qpm = NULL;
    arraySize = -1;
    averagePeriod = parent->movingAveragePeriod;
    averageRe = NULL;
    averageIm = NULL;
    newAverageState = false;
    oldAverageState = false;
    oldXSize = -1;
    oldYSize = -1;
//    groupBox->setTitle(name);
    if(isFreqDisp) {
        this->setWhatsThis("This is a frequency-domain display. The horizontal axis has units of frequency (Hz).");
        horizComboBox->setWhatsThis(QString("This drop-down list sets the frequency range for the full width of the display. Differing choices for samples ")
                    + QString("per second and FFT array size (see the configuration tab) change the range and resolution available in this display.")
            );
    } else {
        this->setWhatsThis("This is a time-domain display. The horizontal axis has units of time (seconds).");
//        horizComboBox->setWhatsThis(QString("This drop-down list sets the time range for the full width of this display. Differing choices for samples ")
//                    + QString("per second and FFT array size (see the configuration tab) change the range and resolution available in this display.")
//            );
    }
//    vertComboBox->setWhatsThis(QString("This drop-down list sets the vertical gain for this display. Sound card outputs typically require higher settings than ")
//                + QString("signal generator sources do.")
//        );
//    averageCheckBox->setWhatsThis(QString("This feature averages signals over time, which greatly increases the ability to distinguish signals from noise. ")
//                + QString("The premise is that noise signals, being random, will cancel out over time, but signals that are buried in noise ")
//                + QString("will gradually build in the average by virtue of their consistency. The quality of the average is determined by ")
//                + QString("the \"Moving Average Period\" setting in the configuration window. This feature requires a lot of memory.")
//        );

}

ScopePane::~ScopePane() {
    delete qpm;
    deleteAverageArrays();
}

/*$SPECIALIZATION$*/

void ScopePane::setup() {
    int i = 0;
    int v = vertComboBox->currentItem();
    v = (v == 0)?9:v;
    int h = horizComboBox->currentItem();
    vertComboBox->clear();
    horizComboBox->clear();
    while(scale[i] != 0) {
        vertComboBox->insertItem(getVString(i).c_str());
        horizComboBox->insertItem(getHString(i).c_str());
        i++;
    }
    vertComboBox->setCurrentItem(v);
    horizComboBox->setCurrentItem(h);
    vertComboBox->updateGeometry();
    horizComboBox->updateGeometry();
}

void ScopePane::updateParameters() {
    setup();
    vChanged();
    hChanged();
}

void ScopePane::deleteAverageArrays() {
    if(averageRe != NULL) {
        for(int i = 0;i < averagePeriod;i++) {
            delete averageReRing[i];
            delete averageImRing[i];
        }
        delete averageReRing;
        delete averageImRing;
        delete averageRe;
        delete averageIm;
        averageReRing = NULL;
        averageImRing = NULL;
        averageRe = NULL;
        averageIm = NULL;
    }
}

void ScopePane::testAveraging(double dataRe[],double dataIm[]) {
//    newAverageState = averageCheckBox->isChecked();
    if(newAverageState) {
        int newArraySize = parent->dp->getArraySize();
        if(!oldAverageState
                || averageRe == NULL
                || averageIm == NULL
                || newArraySize != arraySize
                || parent->movingAveragePeriod != averagePeriod) {
            averageCount = 0;
            deleteAverageArrays();
            arraySize = newArraySize;
            averagePeriod = parent->movingAveragePeriod;
            averageN = 0;
            averageRe = new double[arraySize];
            averageIm = new double[arraySize];
            averageReRing = new double*[averagePeriod];
            averageImRing = new double*[averagePeriod];
            for(int i = 0;i < averagePeriod;i++) {
                averageReRing[i] = new double[arraySize];
                averageImRing[i] = new double[arraySize];
                for(int j = 0;j < arraySize;j++) {
                    averageReRing[i][j] = 0;
                    averageImRing[i][j] = 0;
                }
            }
            for(int i = 0;i < arraySize;i++) {
                averageRe[i] = 0;
                averageIm[i] = 0;
            }
            //printf("init average\n");
            //fflush(stdout);

            oldAverageState = true;
        }
        //printf("%d\n",averageN);
        //fflush(stdout);
        for(int i = 0; i < arraySize;i++) {
            averageRe[i] -= averageReRing[averageCount][i];
            averageIm[i] -= averageImRing[averageCount][i];
            averageReRing[averageCount][i] = dataRe[i];
            averageImRing[averageCount][i] = dataIm[i];
            averageRe[i] += dataRe[i];
            averageIm[i] += dataIm[i];
        }
	// make the count variable cycle through the array
        averageCount = (averageCount + 1) % averagePeriod;
        if(averageN < averagePeriod) {
            averageN++;
        }
    } else if(newAverageState != oldAverageState) {
        oldAverageState = false;
        deleteAverageArrays();
    }

}

void ScopePane::ShowData(double dataRe[],double dataIm[], int size,double gain,double zeroPoint,bool valid,string source) {
    if(!busy) {
        busy = true;

        testAveraging(dataRe,dataIm);
        int xSize = scopeArea->width();
        int ySize = scopeArea->height();

//        printf("x: %d, y: %d\n",xSize,ySize);
        double hSize = size * hScale;
        printf("x: %d, y: %d, s: %d, hs: %lf\n",xSize,ySize,size,hScale);
        if(qpm == NULL || oldXSize != xSize || oldYSize != ySize) {
            delete(qpm);
            qpm = new QPixmap(xSize,ySize);
            oldXSize = xSize;
            oldYSize = ySize;
        }
        qpm->fill(QColor(255,255,255));
        QPainter pixpainter(qpm);
        pixpainter.begin(qpm);

        if(parent->useGrids) {
            drawGrid(pixpainter,xSize,ySize,hScale,gridColor,textColor);
        }
        if(!valid) {
            string s = "No data from source " + source;
            pixpainter.setPen(QColor(0,0,255));
            pixpainter.setFont(QFont("Courier",xSize/48));
            QRect r = pixpainter.boundingRect(0,0,0,0,0,s.c_str());
            pixpainter.drawText((xSize-r.width())/2,ySize/2,s.c_str());
            //qApp->processEvents();
            //usleep(10000);
        } else {
            pixpainter.setPen(lineColor);
            if(dataRe != NULL && (parent->isRunning)) {
                int py0 = scalePoint(zeroPoint,ySize-1,0);
                int opx = 0,opy = 0;
                // avoid some repetitive divisions
                double fact = (double)2.0/size;
                double avgn = 1.0/averageN;
                for(int i = 0;i <= hSize && parent->isRunning;i++) {
                    double dx = (double)i / hSize;
                    double dp;
                    if(isFreqDisp) {
                        if(newAverageState) {
                            dp = (sqrt((averageRe[i] * averageRe[i] + averageIm[i] * averageIm[i]) * fact)) * avgn;
                        } else {
                            dp = sqrt((dataRe[i] * dataRe[i] + dataIm[i] * dataIm[i]) * fact);
                        }
                    } else { // time display
                        if(newAverageState) {
                            dp = averageRe[i] * avgn;
                        } else {
                            dp = dataRe[i];
                        }
                    }
                    double dy = (i < size)?(dp * vScale * gain) + zeroPoint:0;
                    int px = scalePoint(dx,0,xSize);
                    int py = scalePoint(dy,ySize-1,0);
                    if(i == 0) {
                        opx = 0;
                        opy = py;
                    }
                    if(isFreqDisp) {
                        int qx = (px > opx)?px:px+1;
                        //int qy = (py != opy)?py:opy-1;
                        pixpainter.fillRect(opx,py0,qx-opx,py-py0,lineColor);
                        printf("x: %d, y: %d\n",px,py);
                    } else {
                        pixpainter.drawLine(opx,opy,px,py);
                    }
                    opx = px;
                    opy = py;
                }

            } else {
                printf("data = NULL.\n");
            }
            //usleep(100);
        }
        pixpainter.end();
        scopeArea->setPixmap(*qpm);
//        bitBlt(scopeArea,0,0,qpm);
        qApp->processEvents();
        busy = false;
    }
}

void ScopePane::drawGrid(QPainter& qp,int xs,int ys,double hs,QColor grid,QColor text) {
    double sc;
    if(isFreqDisp) {
        sc = parent->dp->freqSpan * hs;
    } else {
        sc = parent->dp->timeSpan * hs;
    }
    double sc2 = pow(10.0,floor(log(sc)/log(10.0)));
    int q = (int) (sc/sc2);
    double sc3 = q * sc2/10.0;
    //printf("sc: %lf,sc2: %lf\n",sc,sc2);
    //fflush(stdout);
    for(double i = sc3; i < sc;i += sc3) {
        qp.setPen(grid);
        int px = scalePoint(i/sc,0,xs);
        int pya = scalePoint(0,ys-1,0);
        int pyb = scalePoint(1,ys-1,0);
        int pyt = scalePoint(.9,ys-1,0);
        qp.drawLine(px,pya,px,pyb);
        //double hi = i;
        string s = getEngFormatString(i/sc,sc);
        qp.setPen(text);
        QRect r = qp.boundingRect(0,0,0,0,0,s.c_str());
        qp.drawText(px-r.width()/2,pyt,s.c_str());
    }
}

int ScopePane::scalePoint(double v,int a, int b) {
    return (int) ((v * (b-a)) + a);
}

void ScopePane::vChanged() {
    vScale = rawVScale(vertComboBox->currentItem());
    //vScale *= parent->dp->timeSpan;
}

void ScopePane::hChanged() {
    hScale = rawHScale(horizComboBox->currentItem());
    //hScale *= parent->dp->freqSpan;
}

double ScopePane::rawVScale(int i) {
    return 1000.0 / scale[i];
}

double ScopePane::rawHScale(int i) {
    return 1.0 / scale[i];
}

const char *ScopePane::timeUnits[] = {"s","ms","us","ns"
                                     };

const char *ScopePane::freqUnits[] = {"Hz","KHz","MHz","GHz"
                                     };

string ScopePane::getHString(int i) {
    double hs = rawHScale(i);
    //hscale = 1.0 / (1 << horizComboBox->currentItem());
    return ((isFreqDisp)?"Frequency Span: ":"Time Span: ") + getEngFormatString(hs);
}

string ScopePane::getEngFormatString(double hs) {
    double sc;
    ostringstream ss;
    if(isFreqDisp) {
        sc = parent->dp->freqSpan * hs;
        int j = -1;
        while(++j < 4 && sc >= 1000.0) {
            sc = sc / 1000.0;
        }
        ss << sc << " " << freqUnits[j];
    } else {
        sc = parent->dp->timeSpan * hs;
        int j = -1;
        while(++j < 4 && sc < 1.0) {
            sc = sc * 1000.0;
        }
        if(j >= 4)
            j = 0;
        ss << sc << " " << timeUnits[j];
    }
    return ss.str();
}

string ScopePane::getEngFormatString(double hs,double span) {
    double sc = hs * span;
    ostringstream ss;
    if(isFreqDisp) {
        int j = -1;
        while(++j < 4 && sc >= 1000.0) {
            sc = sc / 1000.0;
        }
        ss << sc << " " << freqUnits[j];
    } else {
        int j = -1;
        while(++j < 4 && sc < 1.0) {
            sc = sc * 1000.0;
        }
        if(j >= 4)
            j = 0;
        ss << sc << " " << timeUnits[j];
    }
    return ss.str();
}

string ScopePane::getVString(int i) {
    double vs = rawVScale(i);
    //vscale = 1 << vertComboBox->currentItem();
    ostringstream ss;
    ss << "Amplitude: " << vs;
    return ss.str();
}

void ScopePane::averageClicked() {}

//#include "scopepane.moc"

