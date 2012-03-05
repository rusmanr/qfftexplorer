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
#ifndef INITFILEHANDLER_H
#define INITFILEHANDLER_H

#include <cstdio>
#include <iostream>
#include <sstream>
#include <map>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cctype>
#include <functional>
#include <string>

#include <cstdio>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

using namespace std;

typedef map<string,string> MSS;
typedef map<string,MSS> MMSS;

/**
@author Paul Lutus
*/

class InitFileHandler {
public:
    InitFileHandler(string, string);

    ~InitFileHandler();

    string homePath;
    string appPath;
    string progName;
    string iniPath;

    vector <string> split(string s,string delim);
    string trimWhitespace(string s);
    void createConfigPath();
    void writeConfigFile();
    void readConfigFile();
    MSS readFile(string path);

    // these templated functions MUST be defined in the header
    // to avoid a weird compiler bug
    
    // pass the read value back through a reference
    // to a default value in the event it is not defined
    // rather than as a returned value
    template <typename A,typename B>
    void readValue(A key, B& value) {
        istringstream ss(dataMap[key]);
        ss >> value;
    }

    template <typename A,typename B>
    void writeValue(A key, B value) {
        ostringstream ss;
        ss << value;
        dataMap[key] = ss.str();
    }

private:

    MSS dataMap;
    static const char **dataNames;
};

#endif
