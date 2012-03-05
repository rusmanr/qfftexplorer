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
#include "initfilehandler.h"

const char *dataNames[] = {}
                          ;

InitFileHandler::InitFileHandler(string hp,string pn) {

    homePath = hp;
    progName = pn;
    appPath = homePath + "/." + progName;
    iniPath = appPath + "/" + progName + ".ini";
    createConfigPath();
}

InitFileHandler::~InitFileHandler() {}

void InitFileHandler::createConfigPath() {
    mkdir(appPath.c_str());//,0777);
}

void InitFileHandler::readConfigFile() {
    dataMap = readFile(iniPath);
    //string sv = dataMap["currentshow"];
    //int v = 0;
    //sscanf(sv.c_str(),"%d",&v);
    //int max = ShowComboBox->count();
    //v = (v >= max)?max-1:v;
    //ShowComboBox->setCurrentItem(v);
}

void InitFileHandler::writeConfigFile() {
    ofstream ofs(iniPath.c_str());
    MSS::iterator i;
    for(i = dataMap.begin();i != dataMap.end();++i) {
        ofs << i->first << " = " << i->second << endl;
    }
    ofs.close();
}

MSS InitFileHandler::readFile(string path) {
    MSS m;
    ifstream ifs(path.c_str());
    string s;
    while(getline(ifs,s)) {
        vector <string> sp = split(s,string("="));
        if(sp.size() == 2) {
            m[sp[0]] = sp[1];
        }
    }
    ifs.close();
    return m;
}

// the functions readValue and writeValue
// are (must be) defined in the header

vector <string> InitFileHandler::split(string s,string delim) {
    vector <string> v;
    size_t p = s.find(delim);
    if(p != string::npos) {
        string a = trimWhitespace(s.substr(0,p));
        string b = trimWhitespace(s.substr(p+delim.length()));
        v.push_back(a);
        v.push_back(b);
    }
    return v;
}

string InitFileHandler::trimWhitespace(string s) {
    // trim left
    size_t p = s.find_first_not_of(" \n\r\t");
    if(p != string::npos) {
        s.erase(0,p);
    } else {
        s = "";
    }
    // trim right
    p = s.find_last_not_of(" \n\r\t");
    if(p != string::npos) {
        s.erase(p+1);
    }
    return s;
}
