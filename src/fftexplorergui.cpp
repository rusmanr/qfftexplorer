#include <klocale.h>
/****************************************************************************
** Form implementation generated from reading ui file '/netbackup/data/cpp_linux/fftexplorer/src/fftexplorergui.ui'
**
** Created: Mon Oct 31 23:10:16 2005
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.4   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "fftexplorergui.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qtabwidget.h>
#include <qgroupbox.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qcheckbox.h>
#include <qbuttongroup.h>
#include <qradiobutton.h>
#include <qcombobox.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "/netbackup/data/cpp_linux/fftexplorer/src/fftexplorergui.ui.h"

/*
 *  Constructs a MainFrame as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
MainFrame::MainFrame( QWidget* parent, const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "MainFrame" );
    MainFrameLayout = new QGridLayout( this, 1, 1, 11, 6, "MainFrameLayout"); 

    layout3 = new QHBoxLayout( 0, 0, 6, "layout3"); 

    StartButton = new QPushButton( this, "StartButton" );
    layout3->addWidget( StartButton );

    StopButton = new QPushButton( this, "StopButton" );
    layout3->addWidget( StopButton );
    spacer1 = new QSpacerItem( 60, 31, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout3->addItem( spacer1 );

    dummyButton = new QPushButton( this, "dummyButton" );
    layout3->addWidget( dummyButton );

    QuitButton = new QPushButton( this, "QuitButton" );
    layout3->addWidget( QuitButton );

    MainFrameLayout->addLayout( layout3, 1, 0 );

    TabPane = new QTabWidget( this, "TabPane" );
    TabPane->setTabPosition( QTabWidget::Bottom );
    TabPane->setTabShape( QTabWidget::Rounded );

    timePage = new QWidget( TabPane, "timePage" );
    TabPane->insertTab( timePage, QString::fromLatin1("") );

    frequencyPage = new QWidget( TabPane, "frequencyPage" );
    TabPane->insertTab( frequencyPage, QString::fromLatin1("") );

    bothPage = new QWidget( TabPane, "bothPage" );
    TabPane->insertTab( bothPage, QString::fromLatin1("") );

    configurationPage = new QWidget( TabPane, "configurationPage" );
    configurationPageLayout = new QGridLayout( configurationPage, 1, 1, 11, 6, "configurationPageLayout"); 

    groupBox17 = new QGroupBox( configurationPage, "groupBox17" );
    groupBox17->setColumnLayout(0, Qt::Vertical );
    groupBox17->layout()->setSpacing( 0 );
    groupBox17->layout()->setMargin( 4 );
    groupBox17Layout = new QGridLayout( groupBox17->layout() );
    groupBox17Layout->setAlignment( Qt::AlignTop );

    groupBox2 = new QGroupBox( groupBox17, "groupBox2" );
    groupBox2->setColumnLayout(0, Qt::Vertical );
    groupBox2->layout()->setSpacing( 4 );
    groupBox2->layout()->setMargin( 4 );
    groupBox2Layout = new QGridLayout( groupBox2->layout() );
    groupBox2Layout->setAlignment( Qt::AlignTop );

    textLabel9 = new QLabel( groupBox2, "textLabel9" );

    groupBox2Layout->addWidget( textLabel9, 0, 0 );

    sampleRateText = new QLineEdit( groupBox2, "sampleRateText" );
    sampleRateText->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)1, (QSizePolicy::SizeType)0, 0, 0, sampleRateText->sizePolicy().hasHeightForWidth() ) );
    sampleRateText->setMinimumSize( QSize( 0, 0 ) );

    groupBox2Layout->addWidget( sampleRateText, 0, 1 );

    arraySizeEdit = new QLineEdit( groupBox2, "arraySizeEdit" );
    arraySizeEdit->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)1, (QSizePolicy::SizeType)0, 0, 0, arraySizeEdit->sizePolicy().hasHeightForWidth() ) );

    groupBox2Layout->addWidget( arraySizeEdit, 0, 3 );

    textLabel10 = new QLabel( groupBox2, "textLabel10" );

    groupBox2Layout->addMultiCellWidget( textLabel10, 0, 1, 2, 2 );

    applyButton = new QPushButton( groupBox2, "applyButton" );

    groupBox2Layout->addMultiCellWidget( applyButton, 1, 2, 3, 3 );

    textLabel1_3 = new QLabel( groupBox2, "textLabel1_3" );

    groupBox2Layout->addWidget( textLabel1_3, 2, 0 );

    movingAverageEdit = new QLineEdit( groupBox2, "movingAverageEdit" );
    movingAverageEdit->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)1, (QSizePolicy::SizeType)0, 0, 0, movingAverageEdit->sizePolicy().hasHeightForWidth() ) );

    groupBox2Layout->addWidget( movingAverageEdit, 2, 1 );

    gridCheckBox = new QCheckBox( groupBox2, "gridCheckBox" );

    groupBox2Layout->addWidget( gridCheckBox, 2, 2 );

    groupBox17Layout->addWidget( groupBox2, 0, 0 );

    layout4 = new QHBoxLayout( 0, 0, 6, "layout4"); 

    sourceButtonGroup = new QButtonGroup( groupBox17, "sourceButtonGroup" );
    sourceButtonGroup->setExclusive( TRUE );
    sourceButtonGroup->setRadioButtonExclusive( TRUE );
    sourceButtonGroup->setColumnLayout(0, Qt::Vertical );
    sourceButtonGroup->layout()->setSpacing( 0 );
    sourceButtonGroup->layout()->setMargin( 4 );
    sourceButtonGroupLayout = new QHBoxLayout( sourceButtonGroup->layout() );
    sourceButtonGroupLayout->setAlignment( Qt::AlignTop );

    internalRadioButton = new QRadioButton( sourceButtonGroup, "internalRadioButton" );
    sourceButtonGroupLayout->addWidget( internalRadioButton );

    externalRadioButton = new QRadioButton( sourceButtonGroup, "externalRadioButton" );
    sourceButtonGroupLayout->addWidget( externalRadioButton );
    layout4->addWidget( sourceButtonGroup );

    externalSourceBox = new QGroupBox( groupBox17, "externalSourceBox" );
    externalSourceBox->setColumnLayout(0, Qt::Vertical );
    externalSourceBox->layout()->setSpacing( 4 );
    externalSourceBox->layout()->setMargin( 4 );
    externalSourceBoxLayout = new QHBoxLayout( externalSourceBox->layout() );
    externalSourceBoxLayout->setAlignment( Qt::AlignTop );

    textLabel11 = new QLabel( externalSourceBox, "textLabel11" );
    externalSourceBoxLayout->addWidget( textLabel11 );

    dataSourceText = new QLineEdit( externalSourceBox, "dataSourceText" );
    dataSourceText->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)1, (QSizePolicy::SizeType)0, 0, 0, dataSourceText->sizePolicy().hasHeightForWidth() ) );
    externalSourceBoxLayout->addWidget( dataSourceText );

    textLabel1 = new QLabel( externalSourceBox, "textLabel1" );
    externalSourceBoxLayout->addWidget( textLabel1 );

    dataFormatComboBox = new QComboBox( FALSE, externalSourceBox, "dataFormatComboBox" );
    externalSourceBoxLayout->addWidget( dataFormatComboBox );
    layout4->addWidget( externalSourceBox );

    groupBox17Layout->addLayout( layout4, 1, 0 );

    internalSourceBox = new QGroupBox( groupBox17, "internalSourceBox" );
    internalSourceBox->setColumnLayout(0, Qt::Vertical );
    internalSourceBox->layout()->setSpacing( 4 );
    internalSourceBox->layout()->setMargin( 4 );
    internalSourceBoxLayout = new QGridLayout( internalSourceBox->layout() );
    internalSourceBoxLayout->setAlignment( Qt::AlignTop );

    textLabel3 = new QLabel( internalSourceBox, "textLabel3" );

    internalSourceBoxLayout->addWidget( textLabel3, 1, 0 );

    textLabel1_2 = new QLabel( internalSourceBox, "textLabel1_2" );

    internalSourceBoxLayout->addWidget( textLabel1_2, 0, 0 );

    textLabel4 = new QLabel( internalSourceBox, "textLabel4" );

    internalSourceBoxLayout->addWidget( textLabel4, 2, 0 );

    carrierFrequencyEdit = new QLineEdit( internalSourceBox, "carrierFrequencyEdit" );
    carrierFrequencyEdit->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)1, (QSizePolicy::SizeType)0, 0, 0, carrierFrequencyEdit->sizePolicy().hasHeightForWidth() ) );

    internalSourceBoxLayout->addWidget( carrierFrequencyEdit, 0, 1 );

    modLevelEdit = new QLineEdit( internalSourceBox, "modLevelEdit" );
    modLevelEdit->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)1, (QSizePolicy::SizeType)0, 0, 0, modLevelEdit->sizePolicy().hasHeightForWidth() ) );

    internalSourceBoxLayout->addWidget( modLevelEdit, 1, 1 );

    noiseLevelEdit = new QLineEdit( internalSourceBox, "noiseLevelEdit" );
    noiseLevelEdit->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)1, (QSizePolicy::SizeType)0, 0, 0, noiseLevelEdit->sizePolicy().hasHeightForWidth() ) );

    internalSourceBoxLayout->addWidget( noiseLevelEdit, 2, 1 );

    textLabel2 = new QLabel( internalSourceBox, "textLabel2" );

    internalSourceBoxLayout->addWidget( textLabel2, 0, 2 );

    modTypeButtonGroup = new QButtonGroup( internalSourceBox, "modTypeButtonGroup" );
    modTypeButtonGroup->setMargin( 0 );
    modTypeButtonGroup->setExclusive( TRUE );

    amButton = new QRadioButton( modTypeButtonGroup, "amButton" );
    amButton->setGeometry( QRect( 11, 22, 50, 21 ) );

    fmButton = new QRadioButton( modTypeButtonGroup, "fmButton" );
    fmButton->setGeometry( QRect( 70, 20, 60, 21 ) );

    internalSourceBoxLayout->addMultiCellWidget( modTypeButtonGroup, 1, 2, 2, 3 );

    modulationFrequencyEdit = new QLineEdit( internalSourceBox, "modulationFrequencyEdit" );
    modulationFrequencyEdit->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)1, (QSizePolicy::SizeType)0, 0, 0, modulationFrequencyEdit->sizePolicy().hasHeightForWidth() ) );

    internalSourceBoxLayout->addWidget( modulationFrequencyEdit, 0, 3 );

    groupBox17Layout->addWidget( internalSourceBox, 2, 0 );

    configurationPageLayout->addWidget( groupBox17, 0, 0 );
    TabPane->insertTab( configurationPage, QString::fromLatin1("") );

    helpPage = new QWidget( TabPane, "helpPage" );
    TabPane->insertTab( helpPage, QString::fromLatin1("") );

    MainFrameLayout->addWidget( TabPane, 0, 0 );
    languageChange();
    resize( QSize(598, 356).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( StartButton, SIGNAL( clicked() ), this, SLOT( StartDisplay() ) );
    connect( StopButton, SIGNAL( clicked() ), this, SLOT( StopDisplay() ) );
    connect( QuitButton, SIGNAL( clicked() ), this, SLOT( close() ) );
    connect( gridCheckBox, SIGNAL( clicked() ), this, SLOT( applyPressed() ) );
    connect( dataFormatComboBox, SIGNAL( activated(int) ), this, SLOT( applyPressed() ) );
    connect( sampleRateText, SIGNAL( textChanged(const QString&) ), this, SLOT( enableApply() ) );
    connect( arraySizeEdit, SIGNAL( textChanged(const QString&) ), this, SLOT( enableApply() ) );
    connect( dataSourceText, SIGNAL( textChanged(const QString&) ), this, SLOT( enableApply() ) );
    connect( applyButton, SIGNAL( clicked() ), this, SLOT( applyPressed() ) );
    connect( internalRadioButton, SIGNAL( clicked() ), this, SLOT( applyPressed() ) );
    connect( externalRadioButton, SIGNAL( clicked() ), this, SLOT( applyPressed() ) );
    connect( carrierFrequencyEdit, SIGNAL( textChanged(const QString&) ), this, SLOT( enableApply() ) );
    connect( modLevelEdit, SIGNAL( textChanged(const QString&) ), this, SLOT( enableApply() ) );
    connect( noiseLevelEdit, SIGNAL( textChanged(const QString&) ), this, SLOT( enableApply() ) );
    connect( modulationFrequencyEdit, SIGNAL( textChanged(const QString&) ), this, SLOT( enableApply() ) );
    connect( amButton, SIGNAL( clicked() ), this, SLOT( applyPressed() ) );
    connect( fmButton, SIGNAL( clicked() ), this, SLOT( applyPressed() ) );
    connect( carrierFrequencyEdit, SIGNAL( returnPressed() ), this, SLOT( applyPressed() ) );
    connect( modLevelEdit, SIGNAL( returnPressed() ), this, SLOT( applyPressed() ) );
    connect( noiseLevelEdit, SIGNAL( returnPressed() ), this, SLOT( applyPressed() ) );
    connect( modulationFrequencyEdit, SIGNAL( returnPressed() ), this, SLOT( applyPressed() ) );
    connect( sampleRateText, SIGNAL( returnPressed() ), this, SLOT( applyPressed() ) );
    connect( arraySizeEdit, SIGNAL( returnPressed() ), this, SLOT( applyPressed() ) );
    connect( dataSourceText, SIGNAL( returnPressed() ), this, SLOT( applyPressed() ) );
    connect( movingAverageEdit, SIGNAL( textChanged(const QString&) ), this, SLOT( enableApply() ) );
    connect( movingAverageEdit, SIGNAL( returnPressed() ), this, SLOT( applyPressed() ) );
}

/*
 *  Destroys the object and frees any allocated resources
 */
MainFrame::~MainFrame()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void MainFrame::languageChange()
{
    setCaption( tr2i18n( "FFTExplorer" ) );
    StartButton->setText( tr2i18n( "&Start" ) );
    StartButton->setAccel( QKeySequence( tr2i18n( "Alt+S" ) ) );
    QToolTip::add( StartButton, tr2i18n( "Begin FFT conversion process" ) );
    StopButton->setText( tr2i18n( "S&top" ) );
    StopButton->setAccel( QKeySequence( tr2i18n( "Alt+T" ) ) );
    QToolTip::add( StopButton, tr2i18n( "Stop conversion process, freeze the display" ) );
    dummyButton->setText( tr2i18n( "pushButton5" ) );
    dummyButton->setAccel( QKeySequence( QString::null ) );
    QuitButton->setText( tr2i18n( "&Quit" ) );
    QuitButton->setAccel( QKeySequence( tr2i18n( "Alt+Q" ) ) );
    QToolTip::add( QuitButton, tr2i18n( "Exit FFTExplorer" ) );
    QToolTip::add( TabPane, QString::null );
    TabPane->changeTab( timePage, tr2i18n( "Time" ) );
    TabPane->changeTab( frequencyPage, tr2i18n( "Frequency" ) );
    TabPane->changeTab( bothPage, tr2i18n( "Both" ) );
    groupBox17->setTitle( tr2i18n( "Configuration" ) );
    groupBox2->setTitle( tr2i18n( "General" ) );
    textLabel9->setText( tr2i18n( "Sample Rate" ) );
    QToolTip::add( sampleRateText, tr2i18n( "Set the sample rate in samples per second" ) );
    QToolTip::add( arraySizeEdit, tr2i18n( "Set the FFT conversion array size" ) );
    textLabel10->setText( tr2i18n( "FFT Array Size" ) );
    applyButton->setText( tr2i18n( "Apply" ) );
    QToolTip::add( applyButton, tr2i18n( "If this button is enabled, click it to accept your changes" ) );
    textLabel1_3->setText( tr2i18n( "Moving Average Period" ) );
    QToolTip::add( movingAverageEdit, tr2i18n( "Set the window size for moving averages" ) );
    gridCheckBox->setText( tr2i18n( "Grids in charts" ) );
    QToolTip::add( gridCheckBox, tr2i18n( "Include calibration grids in displays" ) );
    sourceButtonGroup->setTitle( tr2i18n( "Source" ) );
    internalRadioButton->setText( tr2i18n( "Internal" ) );
    QToolTip::add( internalRadioButton, tr2i18n( "Select the internal data source" ) );
    externalRadioButton->setText( tr2i18n( "External" ) );
    QToolTip::add( externalRadioButton, tr2i18n( "Select an external data source" ) );
    externalSourceBox->setTitle( tr2i18n( "External Source" ) );
    textLabel11->setText( tr2i18n( "Path" ) );
    QToolTip::add( dataSourceText, tr2i18n( "Specify a path to an external data source" ) );
    textLabel1->setText( tr2i18n( "Format" ) );
    QToolTip::add( dataFormatComboBox, tr2i18n( "Select the format for external data" ) );
    internalSourceBox->setTitle( tr2i18n( "Internal Source" ) );
    textLabel3->setText( tr2i18n( "Modulation level %" ) );
    textLabel1_2->setText( tr2i18n( "Carrier Freq. Hz" ) );
    textLabel4->setText( tr2i18n( "Noise Level %" ) );
    QToolTip::add( carrierFrequencyEdit, tr2i18n( "Enter the desired internal signal frequency" ) );
    QToolTip::add( modLevelEdit, tr2i18n( "Enter the desired carrier modulation level" ) );
    QToolTip::add( noiseLevelEdit, tr2i18n( "Enter a noise level, which is added to the internal signal" ) );
    textLabel2->setText( tr2i18n( "Modulation Freq. Hz" ) );
    modTypeButtonGroup->setTitle( tr2i18n( "Modulation Type" ) );
    amButton->setText( tr2i18n( "AM" ) );
    QToolTip::add( amButton, tr2i18n( "Choose amplitude modulation" ) );
    fmButton->setText( tr2i18n( "FM" ) );
    QToolTip::add( fmButton, tr2i18n( "Choose frequency modulation" ) );
    QToolTip::add( modulationFrequencyEdit, tr2i18n( "Enter a frequency by which the carrier signal is modulated" ) );
    TabPane->changeTab( configurationPage, tr2i18n( "Configuration" ) );
    TabPane->changeTab( helpPage, tr2i18n( "Help" ) );
}

#include "fftexplorergui.moc"
