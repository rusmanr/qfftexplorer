//#include <klocale.h>
/****************************************************************************
** Form implementation generated from reading ui file '/netbackup/data/cpp_linux/fftexplorer/src/ScopePaneGUI.ui'
**
** Created: Mon Oct 31 23:10:18 2005
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.4   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "ScopePaneGUI.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qgroupbox.h>
#include <qlabel.h>
#include <qcheckbox.h>
#include <qcombobox.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

/*
 *  Constructs a ScopePaneForm as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
ScopePaneForm::ScopePaneForm( QWidget* parent, const char* name)//, WFlags fl )
    : QWidget( parent, name)//, fl )
{
    if ( !name )
        setName( "ScopePaneForm" );
    ScopePaneFormLayout = new QGridLayout( this, 1, 1, 2, 6, "ScopePaneFormLayout");

    groupBox = new QGroupBox( this, "groupBox" );
//    groupBox->setLayoutDirection(Qt::Vertical );
//    groupBox->layout()->setSpacing( 6 );
//    groupBox->layout()->setMargin( 5 );
    groupBoxLayout = new QGridLayout();// groupBox->layout() );
    groupBoxLayout->setAlignment( Qt::AlignTop );

    scopeArea = new QLabel( groupBox, "scopeArea" );
    scopeArea->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)7, 0, 0, scopeArea->sizePolicy().hasHeightForWidth() ) );
    scopeArea->setPaletteBackgroundColor( QColor( 255, 255, 255 ) );

    groupBoxLayout->addMultiCellWidget( scopeArea, 0, 0, 0, 3 );

    averageCheckBox = new QCheckBox( groupBox, "averageCheckBox" );

    groupBoxLayout->addWidget( averageCheckBox, 1, 1 );
    spacer1 = new QSpacerItem( 240, 31, QSizePolicy::Expanding, QSizePolicy::Minimum );
    groupBoxLayout->addItem( spacer1, 1, 0 );

    horizComboBox = new QComboBox( FALSE, groupBox, "horizComboBox" );

    groupBoxLayout->addWidget( horizComboBox, 1, 2 );

    vertComboBox = new QComboBox( FALSE, groupBox, "vertComboBox" );

    groupBoxLayout->addWidget( vertComboBox, 1, 3 );

    groupBox->setLayout(groupBoxLayout);

    ScopePaneFormLayout->addWidget( groupBox, 0, 0 );
//    languageChange();
    resize( QSize(319, 133).expandedTo(minimumSizeHint()) );
////    clearWState( WState_Polished );

//    // signals and slots connections
    connect( vertComboBox, SIGNAL( activated(int) ), this, SLOT( vChanged() ) );
    connect( horizComboBox, SIGNAL( activated(int) ), this, SLOT( hChanged() ) );
    connect( averageCheckBox, SIGNAL( clicked() ), this, SLOT( averageClicked() ) );
}

/*
 *  Destroys the object and frees any allocated resources
 */
ScopePaneForm::~ScopePaneForm()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void ScopePaneForm::languageChange()
{
    setCaption( tr( "Form1" ) );
    groupBox->setTitle( tr( "Scope Title" ) );
    scopeArea->setText( QString::null );
    averageCheckBox->setText( tr( "Averaging" ) );
    QToolTip::add( averageCheckBox, tr( "Enable/disable data averaging" ) );
    QToolTip::add( horizComboBox, tr( "Select a horizontal scale" ) );
    QToolTip::add( vertComboBox, tr( "Select a vertical scale (amplification)" ) );
}

void ScopePaneForm::vChanged()
{
    qWarning( "ScopePaneForm::vChanged(): Not implemented yet" );
}

void ScopePaneForm::hChanged()
{
    qWarning( "ScopePaneForm::hChanged(): Not implemented yet" );
}

void ScopePaneForm::averageClicked()
{
    qWarning( "ScopePaneForm::averageClicked(): Not implemented yet" );
}

//#include "ScopePaneGUI.moc"
