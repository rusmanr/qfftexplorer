//#include <klocale.h>
/****************************************************************************
** Form implementation generated from reading ui file '/netbackup/data/cpp_linux/fftexplorer/src/HelpWidgetGUI.ui'
**
** Created: Mon Oct 31 23:10:19 2005
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.4   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "HelpWidgetGUI.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qtextbrowser.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

/*
 *  Constructs a HelpForm as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
HelpForm::HelpForm( QWidget* parent, const char* name)
    : QWidget( parent, name)
{
    if ( !name )
	setName( "HelpForm" );
    HelpFormLayout = new QGridLayout( this, 1, 1, 11, 6, "HelpFormLayout"); 

    layout2 = new QGridLayout( 0, 1, 1, 0, 6, "layout2"); 

    layout1 = new QHBoxLayout( 0, 0, 6, "layout1"); 

    textLabel1 = new QLabel( this, "textLabel1" );
    layout1->addWidget( textLabel1 );

    SearchString = new QLineEdit( this, "SearchString" );
    layout1->addWidget( SearchString );

    layout2->addLayout( layout1, 1, 0 );

    HelpBrowser = new QTextBrowser( this, "HelpBrowser" );
    QFont HelpBrowser_font(  HelpBrowser->font() );
    HelpBrowser_font.setFamily( "Courier 10 Pitch" );
    HelpBrowser->setFont( HelpBrowser_font ); 

    layout2->addWidget( HelpBrowser, 0, 0 );

    HelpFormLayout->addLayout( layout2, 0, 0 );
    languageChange();
    resize( QSize(600, 480).expandedTo(minimumSizeHint()) );
//    clearWState( WState_Polished );

    // signals and slots connections
    connect( SearchString, SIGNAL( textChanged(const QString&) ), this, SLOT( helpSearchString() ) );
    connect( SearchString, SIGNAL( returnPressed() ), this, SLOT( helpSearchString() ) );
}

/*
 *  Destroys the object and frees any allocated resources
 */
HelpForm::~HelpForm()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void HelpForm::languageChange()
{
    setCaption( tr( "Help" ) );
    textLabel1->setText( tr( "Search for:" ) );
    QToolTip::add( SearchString, tr( "Type a search string here, press \"Enter\" to find next case" ) );
}

void HelpForm::helpSearchString()
{
    qWarning( "HelpForm::helpSearchString(): Not implemented yet" );
}

//#include "HelpWidgetGUI.moc"
