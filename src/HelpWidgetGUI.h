/****************************************************************************
** Form interface generated from reading ui file '/netbackup/data/cpp_linux/fftexplorer/src/HelpWidgetGUI.ui'
**
** Created: Mon Oct 31 23:10:06 2005
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.4   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef HELPFORM_H
#define HELPFORM_H

#include <qvariant.h>
#include <qwidget.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QLabel;
class QLineEdit;
class QTextBrowser;

class HelpForm : public QWidget
{
    Q_OBJECT

public:
    HelpForm( QWidget* parent = 0, const char* name = 0);
    ~HelpForm();

    QLabel* textLabel1;
    QLineEdit* SearchString;
    QTextBrowser* HelpBrowser;

public slots:
    virtual void helpSearchString();

protected:
    QGridLayout* HelpFormLayout;
    QGridLayout* layout2;
    QHBoxLayout* layout1;

protected slots:
    virtual void languageChange();

};

#endif // HELPFORM_H
