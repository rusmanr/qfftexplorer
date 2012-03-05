/****************************************************************************
** Form interface generated from reading ui file '/netbackup/data/cpp_linux/fftexplorer/src/displaypanelgui.ui'
**
** Created: Sun Nov 14 10:19:59 2004
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.2   edited Nov 24 13:47 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef DISPLAYPANELGUI_H
#define DISPLAYPANELGUI_H

#include <qvariant.h>
#include <qwidget.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QLabel;
class QFrame;
class QSlider;

class DisplayPanelGUI : public QWidget
{
    Q_OBJECT

public:
    DisplayPanelGUI( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~DisplayPanelGUI();

    QLabel* DisplayName;
    QFrame* GraphicFrame;
    QSlider* vslider;
    QSlider* hslider;

public slots:
    virtual void hsliderValue(int);
    virtual void vslidervalue(int);

protected:
    QVBoxLayout* DisplayPanelGUILayout;
    QHBoxLayout* layout13;
    QSpacerItem* spacer1;
    QHBoxLayout* layout12;

protected slots:
    virtual void languageChange();

};

#endif // DISPLAYPANELGUI_H
