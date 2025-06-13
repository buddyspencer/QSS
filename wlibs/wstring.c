/*  
 *   Copyright (C) 2025 Walter Rosario Molino
 *
 *   This file is part of QSS (Quantized Similarity Search).
 *   QSS (Quantized Similarity Search) is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU Lesser General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   QSS (Quantized Similarity Search) is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU Lesser General Public License for more details.
 *
 *   You should have received a copy of the GNU Lesser General Public License
 *   along with QSS (Quantized Similarity Search).  If not, see <http://www.gnu.org/licenses/>.
*/

#include "wutils.h"

//check equals for string
char check_equals(char * wstring_from, char * wstring_to){
    while(*wstring_from == *wstring_to){
        if(*wstring_from == '\0') return 1;
        wstring_from++;
        wstring_to++;
    }   
    return 0;

}

//return length of a string
int wlen(char * wstring){

    int l;
    char c;
    for(l=0;(c=wstring[l])!='\0';l++);
    return l;

}

//copy a string
void wstrcpy(char * wstring_to, char * wstring_from){

    while((*wstring_to = *wstring_from) != '\0') {
        wstring_to++;
        wstring_from++;
    }   
}






