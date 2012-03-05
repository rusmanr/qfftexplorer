/****************************************************************************
** Form interface generated from reading ui file '/netbackup/data/cpp_linux/fftexplorer/src/fftexplorergui.ui'
**
** Created: Mon Oct 31 23:10:06 2005
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.4   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <qvariant.h>
#include <qwidget.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QPushButton;
class QTabWidget;
class QGroupBox;
class QLabel;
class QLineEdit;
class QCheckBox;
class QButtonGroup;
class QRadioButton;
class QComboBox;

class MainFrame : public QWidget
{
    Q_OBJECT

public:
    MainFrame( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~MainFrame();

    QPushButton* StartButton;
    QPushButton* StopButton;
    QPushButton* dummyButton;
    QPushButton* QuitButton;
    QTabWidget* TabPane;
    QWidget* timePage;
    QWidget* frequencyPage;
    QWidget* bothPage;
    QWidget* configurationPage;
    QGroupBox* groupBox17;
    QGroupBox* groupBox2;
    QLabel* textLabel9;
    QLineEdit* sampleRateText;
    QLineEdit* arraySizeEdit;
    QLabel* textLabel10;
    QPushButton* applyButton;
    QLabel* textLabel1_3;
    QLineEdit* movingAverageEdit;
    QCheckBox* gridCheckBox;
    QButtonGroup* sourceButtonGroup;
    QRadioButton* internalRadioButton;
    QRadioButton* externalRadioButton;
    QGroupBox* externalSourceBox;
    QLabel* textLabel11;
    QLineEdit* dataSourceText;
    QLabel* textLabel1;
    QComboBox* dataFormatComboBox;
    QGroupBox* internalSourceBox;
    QLabel* textLabel3;
    QLabel* textLabel1_2;
    QLabel* textLabel4;
    QLineEdit* carrierFrequencyEdit;
    QLineEdit* modLevelEdit;
    QLineEdit* noiseLevelEdit;
    QLabel* textLabel2;
    QButtonGroup* modTypeButtonGroup;
    QRadioButton* amButton;
    QRadioButton* fmButton;
    QLineEdit* modulationFrequencyEdit;
    QWidget* helpPage;

public slots:
    virtual void StartDisplay();
    virtual void StopDisplay();
    virtual void enableApply();
    virtual void applyPressed();

protected:
    QGridLayout* MainFrameLayout;
    QHBoxLayout* layout3;
    QSpacerItem* spacer1;
    QGridLayout* configurationPageLayout;
    QGridLayout* groupBox17Layout;
    QGridLayout* groupBox2Layout;
    QHBoxLayout* layout4;
    QHBoxLayout* sourceButtonGroupLayout;
    QHBoxLayout* externalSourceBoxLayout;
    QGridLayout* internalSourceBoxLayout;

protected slots:
    virtual void languageChange();

};

#endif // MAINFRAME_H
