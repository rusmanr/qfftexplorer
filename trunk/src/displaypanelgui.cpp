#include <klocale.h>
/****************************************************************************
** Form implementation generated from reading ui file '/netbackup/data/cpp_linux/fftexplorer/src/displaypanelgui.ui'
**
** Created: Sun Nov 14 10:19:59 2004
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.2   edited Nov 24 13:47 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "displaypanelgui.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qframe.h>
#include <qslider.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

/*
 *  Constructs a DisplayPanelGUI as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
DisplayPanelGUI::DisplayPanelGUI( QWidget* parent, const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "DisplayPanelGUI" );
    DisplayPanelGUILayout = new QVBoxLayout( this, 11, 6, "DisplayPanelGUILayout"); 

    layout13 = new QHBoxLayout( 0, 0, 6, "layout13"); 

    DisplayName = new QLabel( this, "DisplayName" );
    DisplayName->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)1, 0, 0, DisplayName->sizePolicy().hasHeightForWidth() ) );
    layout13->addWidget( DisplayName );
    spacer1 = new QSpacerItem( 361, 21, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout13->addItem( spacer1 );
    DisplayPanelGUILayout->addLayout( layout13 );

    GraphicFrame = new QFrame( this, "GraphicFrame" );
    GraphicFrame->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)3, 0, 0, GraphicFrame->sizePolicy().hasHeightForWidth() ) );
    GraphicFrame->setFrameShape( QFrame::StyledPanel );
    GraphicFrame->setFrameShadow( QFrame::Raised );
    DisplayPanelGUILayout->addWidget( GraphicFrame );

    layout12 = new QHBoxLayout( 0, 0, 6, "layout12"); 

    vslider = new QSlider( this, "vslider" );
    vslider->setOrientation( QSlider::Horizontal );
    layout12->addWidget( vslider );

    hslider = new QSlider( this, "hslider" );
    hslider->setOrientation( QSlider::Horizontal );
    layout12->addWidget( hslider );
    DisplayPanelGUILayout->addLayout( layout12 );
    languageChange();
    resize( QSize(637, 508).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( vslider, SIGNAL( valueChanged(int) ), this, SLOT( vslidervalue(int) ) );
    connect( hslider, SIGNAL( valueChanged(int) ), this, SLOT( hsliderValue(int) ) );
}

/*
 *  Destroys the object and frees any allocated resources
 */
DisplayPanelGUI::~DisplayPanelGUI()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void DisplayPanelGUI::languageChange()
{
    setCaption( tr2i18n( "Form1" ) );
    DisplayName->setText( tr2i18n( "Display" ) );
    QToolTip::add( vslider, tr2i18n( "Vertical Scale" ) );
    QToolTip::add( hslider, tr2i18n( "Horizontal Scale" ) );
}

void DisplayPanelGUI::hsliderValue(int)
{
    qWarning( "DisplayPanelGUI::hsliderValue(int): Not implemented yet" );
}

void DisplayPanelGUI::vslidervalue(int)
{
    qWarning( "DisplayPanelGUI::vslidervalue(int): Not implemented yet" );
}

#include "displaypanelgui.moc"
