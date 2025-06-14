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

/*
 * 
 */
void wquantization_similarity_search(const EmbeddingVoice * search_word){
    
    int count = 0;
    int total_1 = TOTAL_1_CHECK;
    double result;
    char found ;
    
    for (unsigned long i = 0; i < MAX_LEN_VOCABULARY; i++){
        found = 1;
        for (int y = 0; y < MAX_BYTE64; y++)
            if (count_ones(search_word->byte[y] ^ embedding_list[i].byte[y]) > total_1) {
                found=0;
                break;
            }   

        if (found==1){
            result = cosine_similarity(embedding_list[i].embedding,search_word->embedding,MAX_EMBEDDING);
            lista_risultato[count].valore=result;
            wstrcpy(lista_risultato[count].voce,embedding_list[i].voce);
            count=count+1;
        }   


    }   



    qsort(lista_risultato, MAX_LEN_QUANTIZATION_RESULT, sizeof(Risultato), cmp_value);
    
    for (int i=0; i<30; i++) printf("%s %f \n",lista_risultato[i].voce,lista_risultato[i].valore);
    


    printf("\ntotal elements %d \n",count);

}


/*
 * search cosise similarity with search word to all embedding list
 * this function is used to compare similarity search vs quantization similarity search
 */
void wsimilarity_search(const EmbeddingVoice * search_word){
    int count=0;    
    double result;
    for (unsigned long i = 0; i < MAX_LEN_VOCABULARY; i++){
        result = cosine_similarity(embedding_list[i].embedding,search_word->embedding,MAX_EMBEDDING);
        lista_risultato_similarity[count].valore=result;
        wstrcpy(lista_risultato_similarity[count].voce,embedding_list[i].voce);
        count=count+1;
    
    }   
    qsort(lista_risultato_similarity, MAX_LEN_VOCABULARY, sizeof(Risultato), cmp_value);
   
    for (int i=0; i<30; i++) printf("%s %f \n",lista_risultato_similarity[i].voce,lista_risultato_similarity[i].valore);


    printf("\ntotal elements %d \n",count);

}


/*
 * calculate classic cosine similarity
 */
double cosine_similarity(const double *a, const double *b, int n) {
    double dot = 0.0, norm_a = 0.0, norm_b = 0.0;
    //printf("%f %f",a[0],b[0]);
    for (int i = 0; i < n; i++) {
        dot += a[i] * b[i];
        norm_a += a[i] * a[i];
        norm_b += b[i] * b[i];
    }
    //printf("%f\n",dot);
    if (norm_a == 0.0 || norm_b == 0.0)
        return 0.0; // evita divisione per zero

    return dot / (sqrt(norm_a) * sqrt(norm_b));
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
 */
void read_embedding(char * name){
    FILE * fp; 
    unsigned long count;
    char read_voice[MAX_PAROLA_VOC];
    double read_embedding[MAX_EMBEDDING];
    unsigned long count_embedding=0;

    if((fp = fopen(name,"r")) == NULL) {
        printf("\n ERROR - filaname %s doesn't exist \n",name);
        exit(1);
    }   

    while ((count=fscanf(fp,"%s",read_voice)) != EOF){
        
        //these 2 cicle for to perform quantization for embedding
        for (int i = 0 ; i < MAX_BYTE64; i++) embedding_list[count_embedding].byte[i]=0; 
        
        for (int i = 0 ; i<MAX_EMBEDDING; i++){
            fscanf(fp,"%lf",&read_embedding[i]);
            read_embedding[i] >= 0 ? shiftLeft(1,embedding_list[count_embedding].byte) : shiftLeft(0,embedding_list[count_embedding].byte);
        }
        wVectorCopy(embedding_list[count_embedding].embedding,read_embedding,MAX_EMBEDDING);
        wstrcpy(embedding_list[count_embedding].voce,read_voice);

        ++count_embedding;
    }

}



