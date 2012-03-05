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

#include "helpwidget.h"
#include "HelpText.h"
#include "fftexplorerwin.h"

HelpWidget::HelpWidget(QWidget *par,fftexplorer* p, const char* name)
        : HelpForm(par,name) {
    parent = p;
    loadFile();
}

HelpWidget::~HelpWidget() {}

/*$SPECIALIZATION$*/

void HelpWidget::loadFile() {
    string help = HelpText;
    help = searchReplace(help,"[PROGDIR]",parent->progPath,true);
    HelpBrowser->setText(help.c_str());
}

void HelpWidget::helpSearchString() {
    SearchString->setBackgroundColor(QColor(255,255,255));
    string s = SearchString->text().toStdString();
    if(oldSearch != s) {
//        HelpBrowser->setSelection(0,0,0,0);
    }
    if(!HelpBrowser->find(s.c_str(),false,false)) {
        QApplication::beep();
        HelpBrowser->clear();//setSelection(0,0,0,0);
        //printf("not found.\n");
        //fflush(stdout);
        SearchString->setBackgroundColor(QColor(255,240,240));
    }
    oldSearch = s;
}

string HelpWidget::searchReplace(string& data, string find, string replace, bool global) {
    string r;
    unsigned int a = 0,b;
    unsigned int len = find.length();
    while((b = data.find(find,a)) != string::npos) {
        r += data.substr(a,b-a) + replace;
        a = b + len;
	if(!global) break;
    }
    r += data.substr(a);
    return r;
}

//#include "helpwidget.moc"

