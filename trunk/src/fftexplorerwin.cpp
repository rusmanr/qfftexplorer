/***************************************************************************
 *   Copyright (C) 2004 by Paul Lutus                                      *
 *   lutusp@arachnoid.com                                                  *
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


#include "fftexplorerwin.h"
#include "ui_fftexplorergui4.h"
#include "workthread.h"
#include "deltatimemeasure.h"
#include "dataprocessor.h"
//#include "graphicdisplay.h"
#include <qslider.h>
#include <qpushbutton.h>
#include <qcombobox.h>
#include <qcheckbox.h>
#include <qtabwidget.h>
#include <qradiobutton.h>
#include <qwhatsthis.h>
//#include "PieGraph.xpm"

const string fftexplorer::programName = "FFTExplorer";
const string fftexplorer::programVersion = "1.16";

//fftexplorer::fftexplorer(QWidget* parent, const char* name, WFlags fl)
fftexplorer::fftexplorer(QWidget* parent, const char* name)
        : QWidget(parent),
          ui(new Ui::MainFrame)
//          QThread()
{
    ui->setupUi(this);


//        : MainFrame(parent,name,fl),QThread() {

    usrPath = getenv("HOMEPATH");
    progPath = usrPath + "/." + programName;

    initHandler = new InitFileHandler(usrPath,programName);

//    setIcon(QPixmap(PieGraph));
    this->setWindowTitle((programName + " " + programVersion).c_str());
    wt = new WorkThread(this);
    dp = new DataProcessor(this);

    //wt = new WorkThread(this);

    timePageLayout = new QGridLayout( ui->timePage);//, 1, 1);
    freqPageLayout = new QGridLayout( ui->frequencyPage);//, 1, 1);
    bothPageLayout = new QGridLayout( ui->bothPage);//, 2, 1);
    helpPageLayout = new QGridLayout( ui->helpPage);//, 1, 1);

    t1 = new ScopePane(ui->timePage,this,false,"Time Display");
    timePageLayout->addWidget( t1, 0, 0 );

    f1 = new ScopePane(ui->frequencyPage,this,true,"Frequency Display");
    freqPageLayout->addWidget( f1, 0, 0 );

    t2 = new ScopePane(ui->bothPage,this,false,"Time Display");
    bothPageLayout->addWidget( t2, 0, 0 );
    f2 = new ScopePane(ui->bothPage,this,true,"Frequency Display");
    bothPageLayout->addWidget( f2, 1, 0 );

    helpwidget = new HelpWidget(ui->helpPage,this);
    helpPageLayout->addWidget( helpwidget, 0, 0 );

//    layout3->remove(ui->dummyButton);
//    delete dummyButton;

    //whatsThisButton = new QPushButton( groupBox1, "whatsThisButton" );

//    QPushButton *wt = (QPushButton *) QWhatsThis::whatsThisButton(this);

//    ui->layout3->insertWidget(3,wt);
    
    setupWhatsThis();

    newParams = false;

    setDefaults();

    readConfigFile();

    writeControls();
    
    // now re-read the controls
    // to allow editing of array size to 2^n
    // also to perform parameter setup
    readControls();

    av = 0;
    n = 0;
    isRunning = false;
}

fftexplorer::~fftexplorer() {
    isRunning = false;
//    wait();
//    delete t1;
//    delete t2;
//    delete f1;
//    delete f2;
    delete dp;
    delete wt;
//    delete helpwidget;
    delete initHandler;
    delete ui;
}

void fftexplorer::setupWhatsThis()
{
ui->sampleRateText->setWhatsThis((QString)
  "This control accepts a sample rate, the number of samples "
+ "collected per second. Remember that higher sample rates "
+ "produce faster display refresh times, and many sound "
+ "cards will provide rates higher than CD-quality sound "
+ "(44100 samples per second). The highest frequency that FFTExplorer "
+ "can resolve is 1/2 this sample rate. If you enter a sample rate "
+ "that is too high, the program will automatically adjust to the "
+ "highest available rate.");
ui->arraySizeEdit->setWhatsThis((QString)
  "This control is used to set the FFT array size, which in turn "
+ "determines the resolution of the frequency display. Larger arrays offer "
+ "more resolution, but in exchange the FFT computation takes longer. "
+ "The array size must be a power of two (1024, 2048, 4096, etc.) "
+ "but do not worry about this -- the program will automatically "
+ "compute an appropriate power of two for you when you enter an approximate value.\n\n"
+ "Regardless of your computer's speed, the minimum time (seconds) "
+ "required to acquire a sound card "
+ "sample is equal to the array size divided by the selected "
+ "samples per second. Example: for an array size of 8192 and 44100 "
+ "samples per second, the sample acquisition time cannot be shorter "
+ "than 186 milliseconds, or roughly five samples per second."
);
ui->dataSourceText->setWhatsThis((QString)
  "This control accepts a file path to a data source, example /dev/dsp "
+ "(the default digital signal processor port). "
+ "This source can be something other than the sound card's DSP port. "
+ "It can be the path to a sound file, or it can be a named pipe "
+ "created with the command \"mkfifo\". Such a named pipe is an easy way to "
+ "connect FFTExplorer to an arbitrary data source, such as a program that "
+ "generates user-defined waveforms."
);
ui->dataFormatComboBox->setWhatsThis((QString)
  "This drop-down list allows you to choose the format of the input signal. "
+ "Most of the choices are typical sound formats, but the \"Plain Text "
+ "Floating-Point Values\" choice is included to allow many different kinds of programs "
+ "to provide data to FFTExplorer in a simple text format. This option is normally "
+ "used in connection with a named pipe created with \"mkfifo\" as the input source "
+ "(see the help file for more on this topic). "
+ "Just make sure the floating-point values are separated by linefeeds, and "
+ "FFTExplorer will read them correctly."
);
ui->internalRadioButton->setWhatsThis((QString)
  "Choose this option to enable an internal signal source that is useful for "
+ "experimenting with the relationship between time and frequency displays."
);
ui->externalRadioButton->setWhatsThis((QString)
  "Choose this option to allow FFTExplorer to read external data sources, such as "
+ "digital signal processors, sound files, and named pipes (see the help file "
+ "for more on this topic)."
);
ui->internalSourceBox->setWhatsThis((QString)
  "This set of controls allows the user to set up the internal signal source. "
+ "This internal signal source is useful for calibration and experimentation "
+ "with FFT methods. These controls are discussed more fully in the help file."
);
ui->movingAverageEdit->setWhatsThis((QString)
  "This control sets the size of the moving average feature used by the data displays. Larger values provide more "
+ "noise rejection but require more memory. "
+ "This feature requires a great deal of memory and will degrade the performance of a system that doesn't have a lot of RAM."
);
}

string fftexplorer::dataTypeNames[] = {"16-bit Unsigned","16-bit Signed" ,"8-bit Mu-law Encoded","Plain Text Floating-Point Values",""};

void fftexplorer::setDefaults() {
    useGrids = true;
    currentTab = 3;
    arraySize = 8000;
    sampleRate = 44100;
    carrierFreq = 1000;
    modFreq = 100;
    movingAveragePeriod = 32;
    modLevel = 1.0;
    noiseLevel = 1.0;
    externalSource = true;
    amModType = true;
    
    dataSource = "./";//dev/dsp";

    int i = 0;
    while(dataTypeNames[i] != "") {
        ui->dataFormatComboBox->insertItem(i,dataTypeNames[i].c_str());
        i++;
    }
    dataType = 0;

}

void fftexplorer::writeControls() {
    ostringstream ss;
    ss << arraySize;
    ui->arraySizeEdit->setText(ss.str().c_str());
    ss.clear();
    ss.str("");
    ss << sampleRate;
    ui->sampleRateText->setText(ss.str().c_str());
    
    ss.clear();
    ss.str("");
    ss << movingAveragePeriod;
    ui->movingAverageEdit->setText(ss.str().c_str());
    
    ss.clear();
    ss.str("");
    ss << carrierFreq;
    ui->carrierFrequencyEdit->setText(ss.str().c_str());
    
    ss.clear();
    ss.str("");
    ss << modFreq;
    ui->modulationFrequencyEdit->setText(ss.str().c_str());
    
    ss.clear();
    ss.str("");
    ss << (modLevel * 100.0);
    ui->modLevelEdit->setText(ss.str().c_str());
    
    ss.clear();
    ss.str("");
    ss << (noiseLevel * 100.0);
    ui->noiseLevelEdit->setText(ss.str().c_str());
    
    ui->amButton->setChecked(amModType);
    ui->fmButton->setChecked(!amModType);
    
    ui->externalRadioButton->setChecked(externalSource);
    ui->internalRadioButton->setChecked(!externalSource);
    
    ui->dataSourceText->setText(dataSource.c_str());
    ui->TabPane->setCurrentIndex(currentTab);
    ui->gridCheckBox->setChecked(useGrids);
    ui->dataFormatComboBox->setCurrentIndex(dataType);
    
}

void fftexplorer::readControls() {
    useGrids = ui->gridCheckBox->isChecked();
    amModType = ui->amButton->isChecked();
    
    externalSource = ui->externalRadioButton->isChecked();
    
    ui->externalSourceBox->setEnabled(externalSource);
    ui->internalSourceBox->setEnabled(!externalSource);
        
    istringstream iss;
//    iss.str(ui->sampleRateText->text());

//    iss >> sampleRate;
    sampleRate = ui->sampleRateText->text().toInt();
//    iss.clear();
//    iss.str(ui->movingAverageEdit->text());
//    iss >> movingAveragePeriod;
    movingAveragePeriod=ui->movingAverageEdit->text().toInt();
    carrierFreq= ui->carrierFrequencyEdit->text().toInt();
    modFreq = ui->modulationFrequencyEdit->text().toInt();
    modLevel = ui->modulationFrequencyEdit->text().toInt();
    noiseLevel = ui->noiseLevelEdit->text().toInt();
    arraySize = ui->arraySizeEdit->text().toInt();

//    iss.clear();
//    iss.str(ui->carrierFrequencyEdit->text());
//    iss >> carrierFreq;
    
//    iss.clear();
//    iss.str(ui->modulationFrequencyEdit->text());
//    iss >> modFreq;
    
//    iss.clear();
//    iss.str(ui->modLevelEdit->text());
//    iss >> modLevel;
    modLevel /= 100.0;
    
//    iss.clear();
//    iss.str(ui->noiseLevelEdit->text());
//    iss >> noiseLevel;
    noiseLevel /= 100.0;
    
//    iss.clear();
//    iss.str(ui->arraySizeEdit->text());
//    iss >> arraySize;
    arraySize = (arraySize > 128000)?128000:arraySize;
    arraySize = (int) (pow(2.0,ceil(log((double)arraySize)/log(2.0))));

    ostringstream oss;
    oss << arraySize;
    ui->arraySizeEdit->setText(oss.str().c_str());
    
    dataType =   ui->dataFormatComboBox->currentText().toInt();
    dataSource = (string) (const char*)ui->dataSourceText->text().toStdString().c_str();
    //printf("Array Size: %d\n",arraySize);
    //fflush(stdout);
    // can change sample rate
    dp->setParameters(arraySize,sampleRate,dataSource);
    t1->updateParameters();
    t2->updateParameters();
    f1->updateParameters();
    f2->updateParameters();
    oss.clear();
    oss.str("");
    oss << sampleRate;
    ui->sampleRateText->setText(oss.str().c_str());
    ui->applyButton->setEnabled(false);
}

// must have this to prevent abnormal suhutdown

void fftexplorer::closeEvent ( QCloseEvent * e ) {
    isRunning = false;
    //wt->wait();
    writeConfigFile();
    e->accept();
// printf("closeEvent called\n");
}

/*$SPECIALIZATION$*/

void fftexplorer::StopDisplay() {
    isRunning = false;
}

void fftexplorer::StartDisplay() {
//    if(!running()) {
        isRunning = true;
//        start();
//    }
    displayFunction();
}

void fftexplorer::run() {
    displayFunction();
}

// this is run in a separate thread

void fftexplorer::displayFunction() {
//    while(isRunning) {

        if(newParams) {
            newParams = false;
        }
//        qApp->lock()
        ;
//        printf("calling createData()\n");
        //fflush(stdout);
        bool valid = dp->createData();
        //printf("returning createData() %d\n",valid);
        //fflush(stdout);
        if(isRunning) {
            int size = dp->getArraySize();
            qDebug()<< size;

            if(ui->timePage->isVisible()) {
                t1->ShowData(dp->raw,dp->raw,size,.5,.5,valid,dp->audioSource);
            } else if(ui->frequencyPage->isVisible()) {
                f1->ShowData(dp->re,dp->im,size/2,1,0.0,valid,dp->audioSource);
            } else if(ui->bothPage->isVisible()) {
                t2->ShowData(dp->raw,dp->raw,size,.5,.5,valid,dp->audioSource);
                f2->ShowData(dp->re,dp->im,size/2,1,0.0,valid,dp->audioSource);
            }

        }
//        qApp->unlock();
//        usleep(100);
//    }
    //wt->exit();
    //printf("exiting thread\n");
    //fflush(stdout);
}

void fftexplorer::enableApply() {
    ui->applyButton->setEnabled(true);
}

void fftexplorer::applyPressed() {
    readControls();
}

void fftexplorer::readConfigFile() {

    initHandler->readConfigFile();

    // app size and location
    int xv = x();
    int yv = y();
    initHandler->readValue("PosX",xv);
    initHandler->readValue("PosY",yv);
    move(xv,yv);

    xv = width();
    yv = height();
    initHandler->readValue("SizeX",xv);
    initHandler->readValue("SizeY",yv);
    resize(xv,yv);

    // program values
    initHandler->readValue("ArraySize",arraySize);
    initHandler->readValue("SampleRate",sampleRate);
    initHandler->readValue("DataSource",dataSource);
    initHandler->readValue("CurrentTab",currentTab);
    initHandler->readValue("UseGrids",useGrids);
    initHandler->readValue("DataType",dataType);
    
    initHandler->readValue("CarrierFrequency",carrierFreq);
    initHandler->readValue("ModulationFrequency",modFreq);
    initHandler->readValue("ModulationLevel",modLevel);
    initHandler->readValue("NoiseLevel",noiseLevel);
    initHandler->readValue("ExternalSource",externalSource);
    initHandler->readValue("AMModType",amModType);
    initHandler->readValue("MovingAveragePeriod",movingAveragePeriod);

}

void fftexplorer::writeConfigFile() {

    // app size and location
    initHandler->writeValue("PosX",x());
    initHandler->writeValue("PosY",y());
    initHandler->writeValue("SizeX",width());
    initHandler->writeValue("SizeY",height());

    // program values
    initHandler->writeValue("ArraySize",arraySize);
    initHandler->writeValue("SampleRate",sampleRate);
    initHandler->writeValue("DataSource",dataSource);
    initHandler->writeValue("CurrentTab",ui->TabPane->currentIndex());
    initHandler->writeValue("UseGrids",useGrids);
    initHandler->writeValue("DataType",dataType);
    
    initHandler->writeValue("CarrierFrequency",carrierFreq);
    initHandler->writeValue("ModulationFrequency",modFreq);
    initHandler->writeValue("ModulationLevel",modLevel);
    initHandler->writeValue("NoiseLevel",noiseLevel);
    initHandler->writeValue("ExternalSource",externalSource);
    initHandler->writeValue("AMModType",amModType);
    initHandler->writeValue("MovingAveragePeriod",movingAveragePeriod);

    initHandler->writeConfigFile();
}

//#include "fftexplorer.moc"
