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




#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <math.h>
#define MAX_PAROLA_VOC  100                  //max length for word in clear in input embedding file
#define MAX_LEN_VOCABULARY 400000            //total number of rows in input embedding file 
#define MAX_LEN_QUANTIZATION_RESULT 400000   //total number of rows for list of results by quantization similarity search.  
#define MAX_EMBEDDING 300                    //Number of embedding elements
#define MAX_BYTE64 5                        //Total bit capacity of the 64-bit element array to store the count of embedding elements. For example for embedding 50 elements it's ok array 64bit with 1 element. For embedding 300 use 5.  
#define PLUS_POSITIVE 0.0
#define PLUS_NEGATIVE -0.0
#define TOTAL_1_CHECK 32                    //tuning parameter. Total number of '1' bits allowed after XOR the search word with the dictionary word. This number could increment number of results obtained from XOR filter. if you see -inf it means you have to increment this value.
                                            



/*
 * STRUCTURE DEFINED
 */

struct struct_embedding_voice{
    char     voce[MAX_PAROLA_VOC];          //text in clear 
    double   embedding[MAX_EMBEDDING];      //array of embedding
    uint64_t byte[MAX_BYTE64];              //array to bit grouped in 64 bit to perform xor
};

typedef struct struct_embedding_voice EmbeddingVoice;

EmbeddingVoice embedding_list[MAX_LEN_VOCABULARY];  //this list contains all rows in input embedding file 


/*
 * This structure contains the voice in clear and the value calculate from cosine similarity
 */
struct struct_risultato{
    char   voce[MAX_PAROLA_VOC];
    double valore;
};

typedef struct struct_risultato Risultato;

Risultato lista_risultato[MAX_LEN_QUANTIZATION_RESULT], lista_risultato_similarity[MAX_LEN_VOCABULARY];




/*
 * LIST OF FUNCTION
 */

char check_equals(char * from, char * to);

int wlen(char * name);

void wstrcpy(char * to, char * from);

void wVectorCopy(double to[], double from[],int tot_elem);

void shiftLeft(uint64_t bit_maschera,uint64_t byte[]);

double cosine_similarity(const double *a, const double *b, int n);

int count_ones(uint64_t x);

void init_lista_risultato_similarity(void);

void init_lista_risultato(void);

int cmp_value(const void *a, const void *b);

void wquantization_similarity_search(const EmbeddingVoice * search_word);

void wsimilarity_search(const EmbeddingVoice * search_word);

void read_embedding(char * name);


