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
#ifndef DATAPROCESSOR_H
#define DATAPROCESSOR_H

#include <qstring.h>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>

#include "fftexplorerwin.h"

using namespace std;

/**
@author Paul Lutus
*/
class DataProcessor {
public:
    DataProcessor(fftexplorer* p);
    DataProcessor();

    ~DataProcessor();
    
    static const int dataFormats[];

    fftexplorer *parent;

    double timeSpan,freqSpan;

    void setParameters(int as,int& sr,string src);

    void closeStream();
    bool readAudio(double ta[]);

    bool read16BitUnsigned(double ta[]);
    bool read16BitSigned(double ta[]);
    bool read8BitMuLawEncoded(double ta[]);
    bool readPlainText(double ta[]);

    void createAMSignal(double ta[]);
    void createFMSignal(double ta[]);
    bool createData();
    double getRandom();
    void setOptions(int fp,int& sr);
    int getArraySize();
    void setupStorage();
    double *raw,*re,*im;
    string audioSource;
    string oldAudioSource;

private:
    int arraySize;
    int newArraySize;
    int sampleRate;
    int fp;
    FILE *fpp;
    

};

#endif
