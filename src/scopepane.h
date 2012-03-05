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

#ifndef SCOPEPANE_H
#define SCOPEPANE_H

#include "ScopePaneGUI.h"
#include <QDialog>
#include <qpixmap.h>
#include <qpainter.h>
#include <qcolor.h>
#include <qlabel.h>
#include <qgroupbox.h>
#include <ui_ScopePaneGUI4.h>

#include <cmath>
#include <string>

using namespace std;

class fftexplorer;
class ScopePaneForm;

class ScopePane : public ScopePaneForm
//        class ScopePane : public QDialog
{
    Q_OBJECT

public:
    ScopePane(QWidget* par = 0, fftexplorer *p = 0,bool fd = true,const char* name = 0);//, WFlags fl = 0 );
    ~ScopePane();
    /*$PUBLIC_FUNCTIONS$*/

    fftexplorer *parent;

    static const double scale[];
    static const char *timeUnits[];
    static const char *freqUnits[];

    static const QColor backgroundColor;
    static const QColor lineColor;
    static const QColor gridColor;
    static const QColor textColor;
    static const QColor warningColor;

    bool isFreqDisp;
    bool busy;
    int averagePeriod,averageN;
    unsigned int averageCount;
    double *averageRe;
    double *averageIm;
    double **averageReRing;
    double **averageImRing;
    int arraySize,newArraySize;
    bool newAverageState,oldAverageState;

    void setup();

    void ShowData(double dataRe[],double dataIm[], int size,double gain,double zeroPoint,bool valid,string source);
    void drawGrid(QPainter& qp,int xs,int ys,double hs,QColor grid,QColor text);
    int scalePoint(double v,int a, int b);
    void updateParameters();
    double rawVScale(int i);
    double rawHScale(int i);
    string getHString(int i);
    string getVString(int i);
    string getEngFormatString(double hs);
    string getEngFormatString(double hs,double span);
    void testAveraging(double dataRe[],double dataIm[]);
    void deleteAverageArrays();

    QPixmap *qpm;
    int oldXSize;
    int oldYSize;

public slots:
    /*$PUBLIC_SLOTS$*/

protected:
    double vScale, hScale;
    /*$PROTECTED_FUNCTIONS$*/

protected slots:
    /*$PROTECTED_SLOTS$*/
    void vChanged();
    void hChanged();
    void averageClicked();

};

#endif

