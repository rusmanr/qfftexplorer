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
#include "quickfft.h"

#include <cmath>

QuickFFT::QuickFFT() {}


QuickFFT::~QuickFFT() {}


// zero the im array

void QuickFFT::fftPre(double re[],double im[], int size) {
    for(int i = 0;i < size;++i) {
        im[i] = 0.0;
    }
    fftConvert(re,im,size);
}

// produce separate real and imaginary results

// the re and im arrays must have a length
// that is a power of 2

void QuickFFT::fftConvert(double re[], double im[],int size) {
    double scale = sqrt(1.0/(double)size);
    int i,j;
    double tempr,tempi;
    for (i=j=0; i<size; ++i) {
        if (j>=i) {
            tempr = re[j]*scale;
            tempi = im[j]*scale;
            re[j] = re[i]*scale;
            im[j] = im[i]*scale;
            re[i] = tempr;
            im[i] = tempi;
        }
        int m = size>>1;
        while (m>=1 && j>=m) {
            j -= m;
            m>>=1;
        }
        j += m;
    }

    int imax = 1,istep = 2,m;
    double w,wr,wi,tr,ti,delta;
    while (imax<size) {
        delta = M_PI/imax;
        for (m=0; m<imax; ++m) {
            w = m*delta;
            wr = cos(w);
            wi = sin(w);
            for (i=m; i<size; i+=istep) {
                j = i+imax;
                tr = wr*re[j]-wi*im[j];
                ti = wr*im[j]+wi*re[j];
                re[j] = re[i] - tr;
                im[j] = im[i] - ti;
                re[i] += tr;
                im[i] += ti;
            }
        }
        imax<<=1;
        istep<<=1;
    }
}
