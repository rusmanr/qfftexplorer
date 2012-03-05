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

#ifndef FFTEXPLORER_H
#define FFTEXPLORER_H

#include <QWidget>
#include <QtGui>
//#include "fftexplorergui.h"
#include <QDialog>
#include "scopepane.h"
#include "helpwidget.h"
#include "initfilehandler.h"
#include <qlayout.h>
#include <qthread.h>
#include <string>

using namespace std;

//class GraphicDisplay;
class DataProcessor;
class WorkThread;

namespace Ui {
    class MainFrame;
}

class fftexplorer : public QWidget
//class fftexplorer : public QMainWindow, public QThread
{
    Q_OBJECT

public:
    explicit fftexplorer(QWidget* parent = 0, const char* name = 0);//, WFlags fl = 0 );
    ~fftexplorer();

    static const string programName;
    static const string programVersion;
    
    int sampleRate;
    int movingAveragePeriod;
    int arraySize;
    int currentTab;
    string dataSource;
    bool useGrids;
    double carrierFreq;
    double modFreq;
    double modLevel;
    double noiseLevel;
    bool externalSource;
    bool amModType;

    string usrPath,progPath;
    
    HelpWidget *helpwidget;
    
    //WorkThread *wt;
    
    InitFileHandler *initHandler;

    bool isRunning;
    bool newParams;

    double av;
    int n;
    static string dataTypeNames[];
    int dataType;

    WorkThread *wt;

    DataProcessor* dp;
    ScopePane *t1,*f1,*t2,*f2;
    QGridLayout *timePageLayout,*freqPageLayout,*bothPageLayout,*helpPageLayout;

    /*$PUBLIC_FUNCTIONS$*/
    
    void setDefaults();
    void readControls();
    void writeControls();
    
    void run();

    void ShowData(double ta[], int size);
    int scalePoint(double v,int a, int b);
    void displayFunction();
    void closeEvent ( QCloseEvent * e );
    
    void readConfigFile();
    void writeConfigFile();
    void setupWhatsThis();


public slots:
    /*$PUBLIC_SLOTS$*/
    virtual void StopDisplay();
    virtual void StartDisplay();
    void enableApply();
    void applyPressed();

protected:
    /*$PROTECTED_FUNCTIONS$*/

protected slots:
    /*$PROTECTED_SLOTS$*/

private:
    Ui::MainFrame *ui;
    //double timeV,timeH,freqV,freqH;

};

#endif

