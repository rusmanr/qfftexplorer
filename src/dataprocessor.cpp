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

#define MODE_MONO	0
#define MODE_STEREO	1

#include "dataprocessor.h"
#include "fftexplorerwin.h"
#include "mulawconverter.h"
#include "quickfft.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
//#include <sys/ioctl.h>
//#include <sys/soundcard.h>


#include <qstring.h>

#include <cmath>

DataProcessor::DataProcessor(fftexplorer *p) {
    parent = p;
    fp = 0;
    fpp = NULL;
    oldAudioSource = "";
    arraySize = 0;
    raw = NULL;
    re = NULL;
    im = NULL;
}

DataProcessor::~DataProcessor() {
    close(fp);
    fp = -1;
    delete raw;
    delete re;
    delete im;
}

int DataProcessor::getArraySize() {
    return arraySize;
}

void DataProcessor::setParameters(int as,int& sr,string src) {
    newArraySize = as;
    sampleRate = sr;
    audioSource = src;
    if(parent->externalSource) {
        if(audioSource != oldAudioSource) {
            oldAudioSource = audioSource;
            if(fp > 0) {
//                close(fp);
            }
//	    // must use non-blocking mode
//	    // to avoid application lock-ups
//	    // even though this hurts performance
//            fp = open(audioSource.c_str(),O_RDONLY|O_NONBLOCK,0);
        }
        if(fp > 0) {
//            fpp = fdopen(fp,"r");
            // this can change caller's sample rate
//            setOptions(fp,sampleRate);
            sr = sampleRate;
        }
    }
    timeSpan = (double)newArraySize / sampleRate;
    freqSpan = (double)sampleRate/2.0;
}

void DataProcessor::setupStorage() {
    if(arraySize != newArraySize) {
        arraySize = newArraySize;
        delete raw;
        delete re;
        delete im;
        //printf("%d %d\n",arraySize,fftArraySize);
        //fflush(stdout);
        raw = new double[arraySize];
        re = new double[arraySize];
        im = new double[arraySize];
        double v = 0.0;
        for(int i = 0;i < arraySize;i++) {
            raw[i] = v;
            re[i] = v;
            im[i] = v;
        }
    }
}

const int DataProcessor::dataFormats[] = {
//            AFMT_U16_LE, AFMT_S16_LE,AFMT_MU_LAW,0
        };

// can change caller's "sr" value
void DataProcessor::setOptions(int audio,int& sr) {
    int format = dataFormats[parent->dataType];
//    int r = ioctl(audio, SNDCTL_DSP_SETFMT, &format);
    //printf("ioctl r 1 = %d\n",r);
    //fflush(stdout);
    int v = sr;
//    r = ioctl(audio, SNDCTL_DSP_SPEED, &v);
    //printf("ioctl r 2 = %d\n",r);
    //fflush(stdout);
    // did the DSP accept our sample rate?
    if(v != sr) {
        // if not, accept the reply
        sr = v;
    }
    // this produces more reliable performance
    int val = (int) (( 2 << 16 ) + log2(512));
//    r = ioctl(audio, SNDCTL_DSP_SETFRAGMENT, &val);
}

double DataProcessor::getRandom() {
    return (double)rand() / (double)RAND_MAX;
    //return cellRandom->random();
}

bool DataProcessor::readAudio(double ta[]) {
    if(fp <= 0) {
        //printf("file descriptor fp < 0!\n");
        //fflush(stdout);
        //exit(1);
        return false;
    } else {
        switch(parent->dataType) {
        case 0:
            return read16BitUnsigned(ta);
            break;
        case 1:
            return read16BitSigned(ta);
            break;
        case 2:
            return read8BitMuLawEncoded(ta);
            break;
        case 3:
            return readPlainText(ta);
            break;
        }
    }
    return false;
}

bool DataProcessor::read16BitUnsigned(double ta[]) {
    bool validData = true;
    for(int i = 0; validData && parent->isRunning && i < arraySize && fp > 0;i++) {
        int v = 0;
        // this fd is opened using O_NONBLOCK
        // so it can return with no data
        int j = 0;
        while(validData && parent->isRunning && read(fp,&v,2) != 2) {
            qApp->processEvents();
            if(j++ > 1000) {
                validData = false;
                break;
            }
        }
        //read(fp,&v,2);
        ta[i] = ((double)v-32768.0) / 32768.0;
    }
    return validData;
}

bool DataProcessor::read16BitSigned(double ta[]) {
    bool validData = true;
    short v = 0;
    for(int i = 0; validData && parent->isRunning && i < arraySize && fp > 0;i++) {
        // this fd is opened using O_NONBLOCK
        // so it can return with no data
        int j = 0;
        while(validData && parent->isRunning && read(fp,&v,2) != 2) {
            qApp->processEvents();
            if(j++ > 1000) {
                validData = false;
                break;
            }
        }
        ta[i] = (double)v / 32768.0;
    }
    return validData;
}

bool DataProcessor::read8BitMuLawEncoded(double ta[]) {
    bool validData = true;
    for(int i = 0; validData && parent->isRunning && i < arraySize && fp > 0;i++) {
        unsigned char c = 0;
        // this fd is opened using O_NONBLOCK
        // so it can return with no data
        int j = 0;
        while(validData && parent->isRunning && read(fp,&c,1) != 1) {
            qApp->processEvents();
            if(j++ > 1000) {
                validData = false;
                break;
            }
        }
        //read(fp,&c,1);
        ta[i] = MulawConverter::mu2linfast(c) / 32768.0;
    }
    return validData;
}

bool DataProcessor::readPlainText(double ta[]) {
    int buflen = 512;
    char buf[buflen];
    bool validData = true;
    int i = 0;
    istringstream ss;
    while(validData && parent->isRunning && i < arraySize && fp > 0) {
        // this fd is opened using O_NONBLOCK
        // so it can return with no data
        int j = 0;
        while(fgets(buf,buflen,fpp) == NULL) {
            qApp->processEvents();
            if(j++ > 1000) {
                validData = false;
                break;
            }
        }
        //fgets(buf,buflen,fpp);
        double n = 0;
        sscanf(buf,"%lf",&n);
        ta[i++] = n;
    }
    qApp->processEvents();
    return validData;
}

// create AM signal

void DataProcessor::createAMSignal(double ta[]) {
    for(int t = 0;parent->isRunning && t < arraySize; t++) {
        double dt = (double)t/(double)sampleRate;
        ta[t] = sin(2 * M_PI * parent->carrierFreq * dt) * (1.0 + (sin(2 * M_PI * parent->modFreq * dt) * parent->modLevel));
        double r = (getRandom() - 0.5) * parent->noiseLevel;
        ta[t] += r;
    }
}

// create FM signal

void DataProcessor::createFMSignal(double ta[]) {
    for(int t = 0;parent->isRunning && t < arraySize; t++) {
        double dt = (double)t/(double)sampleRate;
        double mod = sin(2 * M_PI * parent->modFreq * dt) * (parent->modLevel / parent->carrierFreq);
        ta[t] = sin(2 * M_PI * parent->carrierFreq * (dt + mod));
        double r = (getRandom() - 0.5) * parent->noiseLevel;
        ta[t] += r;
    }
}

bool DataProcessor::createData() {

    // must validate storage areas here
    setupStorage();
    bool valid = true;
    if(parent->externalSource && (fp == 0 || fpp == NULL))
        return false;
    if(parent->externalSource) {
        valid = readAudio(raw);
    } else { // internal signal source
        if(parent->amModType) {
            createAMSignal(raw);
        } else {
            createFMSignal(raw);
        }
    }
    if(valid && parent->isRunning) {
        // keep a copy of the original data set
        for(int i = 0;i < arraySize;i++) {
            re[i] = raw[i];
        }
        QuickFFT::fftPre(re,im,arraySize);
    }
    return valid;
}
