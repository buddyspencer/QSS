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


#include <limits.h>
#include "wutils.h"

/*
 * This function perform linear semantic search for the search_word in 2 steps:
 * 1° STEP: check if the word i_esima in the list in xor with search_word have different bits <= then TOTAL_1_CHECK
 * 2° STEP: for the word found in the previous step, put it into lista_risultato and provide the cosine_similarity with search_word
 * 
 * NEXT STEP this search should be optimized with a structure like BK-Tree
 */
void wquantization_similarity_search(const EmbeddingVoice * search_word){
    
    int count = 0 ;
    int count_bit_1;
    int total_1 = TOTAL_1_CHECK;
    float result;
    char found ;
    clock_t start,end;
    double total_seconds;
    start = clock();
    for (unsigned long i = 0; i < MAX_LEN_VOCABULARY; i++){
        found = 1;
        count_bit_1 = 0;
        
        //1° STEP: check if the xor contains number of 1 > TOTAL_1_CHECK in this case ignore word in the vocabulary else put the word in lista_risultato and calculate cosine_similarity   
        for (int y = 0; y < MAX_BYTE64; y++){
            count_bit_1 = count_bit_1 + count_ones(search_word->byte[y] ^ embedding_list[i].byte[y]);
            if (count_bit_1 > total_1) {
                found=0;
                break;
            }   
        }
        //2° STEP: put the word in lista_risultato anche calculate cosin_similarity
        if (found==1){
            result = cosine_similarity(embedding_list[i].embedding,search_word->embedding,embedding_list[i].norm, search_word->norm,MAX_EMBEDDING);
            lista_risultato[count].valore=result;
            wstrcpy(lista_risultato[count].voce,embedding_list[i].voce);
            count=count+1;
        }   


    }   

    end = clock();
    total_seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\n\n Quantization time:   %.6f seconds\n", total_seconds);
    
    start = clock();
    qsort(lista_risultato, MAX_LEN_QUANTIZATION_RESULT, sizeof(Risultato), cmp_value);  //perform sort on value of cosine_similaty
    end = clock();

    total_seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\n Sort time:   %.6f seconds\n", total_seconds);
    for (int i=0; i<30; i++) printf("%s %f \n",lista_risultato[i].voce,lista_risultato[i].valore);
    


    printf("\n Total elements found %d \n",count);

}


/*
 * search cosine similarity with search word to all embedding list
 * this function is used to compare similarity search vs quantization similarity search
 */
void wsimilarity_search(const EmbeddingVoice * search_word){
    int count=0;    
    float result;
    clock_t start,end;
    double total_seconds;
    start = clock();
    for (unsigned long i = 0; i < MAX_LEN_VOCABULARY; i++){
        result = cosine_similarity(embedding_list[i].embedding,search_word->embedding,embedding_list[i].norm,search_word->norm,MAX_EMBEDDING);
        lista_risultato_similarity[count].valore=result;
        wstrcpy(lista_risultato_similarity[count].voce,embedding_list[i].voce);
        count=count+1;
    
    }   
    end = clock();
    total_seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\n\n Similarity time:   %.6f seconds\n", total_seconds);
    
    start = clock();
    qsort(lista_risultato_similarity, MAX_LEN_VOCABULARY, sizeof(Risultato), cmp_value);
    end = clock();

    total_seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\n Sort time:   %.6f seconds\n", total_seconds); 
    for (int i=0; i<30; i++) printf("%s %f \n",lista_risultato_similarity[i].voce,lista_risultato_similarity[i].valore);


    printf("\n Total elements found %d \n",count);

}


/*
 * calculate classic cosine similarity
 */
float cosine_similarity(const float *a, const float *b, const double norm_a, const double norm_b, int n) {
    float dot = 0.0 ;
    //printf("%f %f",a[0],b[0]);
    for (int i = 0; i < n; i++) {
        dot += a[i] * b[i];
    }
    //printf("%f\n",dot);
    if (norm_a == 0.0 || norm_b == 0.0)
        return 0.0f; // evita divisione per zero
    return dot / (float)(norm_a * norm_b);
}

/*
 * calculate normalization.
 * During the math computation use double cast to avoid loss useful value
 */

double normalization(const float *a) {
    double  norm = 0.0;
    //printf("%f %f",a[0],b[0]);
    for (int i = 0; i < MAX_EMBEDDING; i++) {
        norm += a[i] * a[i];

    }   
    return sqrt(norm);
}


/*
 * read file glove composed by  word and list of embedding 
 * the file read is put in embedding_list
 * if you want read with another embedding structure you have to use embedding_list to save embedding 
 * and to perform quantization for embedding:
 *      embedding element >=0 -> 1 bit
 *      embedding element <0 -> 0 bit
 *      
 *      for example:
 *      -1.3343434 -> 0
 *      0.4353343  -> 1
 *  NEXT STEP this structure should be optimized with a structure like BK-Tree
 */
void read_embedding_glove(char *filename){
    FILE * fp; 
    unsigned long count;
    char read_voice[MAX_PAROLA_VOC];
    float read_embedding_vector[MAX_EMBEDDING];
    unsigned long count_embedding=0;

    if((fp = fopen(filename,"r")) == NULL) {
        printf("\n ERROR - filaname %s doesn't exist \n",filename);
        exit(1);
    }   
    printf("Reading file binary....\n");

    while ((count=fscanf(fp,"%s",read_voice)) != EOF){
        
        //these 2 cicle for to perform quantization for embedding
        for (int i = 0 ; i < MAX_BYTE64; i++) embedding_list[count_embedding].byte[i]=0; 
        
        for (int i = 0 ; i<MAX_EMBEDDING; i++){
            fscanf(fp,"%f",&read_embedding_vector[i]);
            read_embedding_vector[i] >= 0 ? shiftLeft(1,embedding_list[count_embedding].byte) : shiftLeft(0,embedding_list[count_embedding].byte);
        
        } 
        wVectorCopy(embedding_list[count_embedding].embedding,read_embedding_vector,MAX_EMBEDDING);
        embedding_list[count_embedding].norm = normalization(embedding_list[count_embedding].embedding);
        wstrcpy(embedding_list[count_embedding].voce,read_voice);

        ++count_embedding;
    }
}

/*
 * read file word2vec binary. Please, pay attention the embedding is float type.
 * the word2vect is a binary file with this structure:
 * 
 * HEADER:              | vocabulary size | vector size | 
 * BODY for each word:  |word in string | vector with 300 floats elements |
 * 
 * all elements in BODY are put embedding_list array with quantization.
 * 
 * NEXT STEP this structure should be optimized with a structure like BK-Tree
 */

void read_embedding_bin_file(char *filename) {
    FILE *f = fopen(filename, "rb");
    if (!f) {
        printf("\n ERROR - filaname %s doesn't exist \n",filename);
        exit(1);
    }   
    printf("Reading file binary....\n");
    // Leggi header
    unsigned long vocab_size, vector_size;
    fscanf(f, "%lu %lu\n", &vocab_size, &vector_size);
    // Buffer per la parola
    char word[MAX_PAROLA_VOC];
    //double *vec = malloc(sizeof(double) * vector_size);
    float read_embedding_vector[MAX_EMBEDDING];
    float read_embedding_vector_float[MAX_EMBEDDING];
    for (unsigned long i = 0; i < vocab_size; i++) {
        // Leggi parola: carattere per carattere fino a spazio
        for (int j = 0 ; j < MAX_BYTE64; j++) embedding_list[i].byte[j]=0;

        int idx = 0;
        char ch; 
        while ( (ch = fgetc(f)) != ' ') {
            word[idx++] = ch; 
        }   
        word[idx] = '\0';
        wstrcpy(embedding_list[i].voce,word);

        // Leggi vettore float
        fread(read_embedding_vector_float, sizeof(float), vector_size, f); 

        for (int tmp=0; tmp<vector_size; tmp++)
            read_embedding_vector[tmp]=read_embedding_vector_float[tmp];
         
        // Per evitare problemi con i newline nel file,
        // c'è spesso un carattere extra da saltare (newline)
        //fgetc(f);
        for (int x = 0 ; x<MAX_EMBEDDING; x++){
            read_embedding_vector[x] >= 0 ? shiftLeft(1,embedding_list[i].byte) : shiftLeft(0,embedding_list[i].byte);
         }
        wVectorCopy(embedding_list[i].embedding,read_embedding_vector,MAX_EMBEDDING);
        embedding_list[i].norm = normalization(embedding_list[i].embedding);
    }   

    //free(vec);
    fclose(f);
}

