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

//copy vector with tot_elem
void wVectorCopy(float wvector_to[], float wvector_from[],int tot_elem){
    for (int i=0; i<tot_elem; i++) wvector_to[i]=wvector_from[i];

}
//shift vector byte of MAX_BYTE64 element for bit_maschera position
void shiftLeft(uint64_t bit_maschera,uint64_t byte[]){
    for (int i=0; i<MAX_BYTE64; i++){
        uint64_t precedente_msb = byte[i]>>63;
        byte[i] = (byte[i]<<1) | bit_maschera;
        bit_maschera = precedente_msb;
    }   

}

//check equals for 2 structure used for quick sort decrescent
int cmp_value(const void *a, const void *b) {
    const Risultato *pa = (const Risultato *)a;
    const Risultato *pb = (const Risultato *)b;

    if (pa->valore < pb->valore) return 1;
    else if (pa->valore > pb->valore) return -1;
    else return 0;
}





//count how many 1 bit are present in x
int count_ones(uint64_t x) {
    //int count = 0;
    //while (x) {
    //    count += x & 1;  
    //    x >>= 1;         
    //}
    //int count = 0;
    //while (x) {
    //    x &= (x - 1); // rimuove il bit più basso a 1
    //    count++;
    //}
    return __builtin_popcountll(x);
}


//initialize lista_risultato_similarity
void init_lista_risultato_similarity(void){
    for (unsigned long i = 0; i<MAX_LEN_VOCABULARY; i++){
        lista_risultato_similarity[i].voce[0]='\0';
        lista_risultato_similarity[i].valore = -INFINITY;
    }
}

//initialize lista_risultato
void init_lista_risultato(void){
    for (unsigned long i = 0; i<MAX_LEN_QUANTIZATION_RESULT; i++){
        lista_risultato[i].voce[0]='\0';
        lista_risultato[i].valore = -INFINITY;
    }
}



