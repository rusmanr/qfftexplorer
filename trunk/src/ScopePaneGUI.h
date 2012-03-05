/****************************************************************************
** Form interface generated from reading ui file '/netbackup/data/cpp_linux/fftexplorer/src/ScopePaneGUI.ui'
**
** Created: Mon Oct 31 23:10:06 2005
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.4   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef SCOPEPANEFORM_H
#define SCOPEPANEFORM_H

#include <qvariant.h>
#include <qwidget.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QGroupBox;
class QLabel;
class QCheckBox;
class QComboBox;

class ScopePaneForm : public QWidget
{
    Q_OBJECT

public:
    ScopePaneForm( QWidget* parent = 0, const char* name = 0);//, WFlags fl = 0 );
    ~ScopePaneForm();

    QGroupBox* groupBox;
    QLabel* scopeArea;
    QCheckBox* averageCheckBox;
    QComboBox* horizComboBox;
    QComboBox* vertComboBox;

public slots:
    virtual void vChanged();
    virtual void hChanged();
    virtual void averageClicked();

protected:
    QGridLayout* ScopePaneFormLayout;
    QGridLayout* groupBoxLayout;
    QSpacerItem* spacer1;

protected slots:
    virtual void languageChange();

};

#endif // SCOPEPANEFORM_H
