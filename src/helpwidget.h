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

#ifndef HELPWIDGET_H
#define HELPWIDGET_H

#include "HelpWidgetGUI.h"
#include <QDialog>
#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <qapplication.h>
#include <qtextbrowser.h>
#include <qlineedit.h>

class fftexplorer;

using namespace std;

class HelpWidget : public HelpForm {
    Q_OBJECT

public:
    HelpWidget(QWidget *par,fftexplorer* p, const char* name = 0);//, WFlags fl = 0 );
    ~HelpWidget();
    /*$PUBLIC_FUNCTIONS$*/
    
    void loadFile();
    void helpSearchString();
    
    string searchReplace(string& data, string find, string replace, bool global);
    
    fftexplorer *parent;
    
    string oldSearch;

public slots:
    /*$PUBLIC_SLOTS$*/

protected:
    /*$PROTECTED_FUNCTIONS$*/

protected slots:
    /*$PROTECTED_SLOTS$*/

};

#endif

