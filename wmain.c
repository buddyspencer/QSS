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



#include "wlibs/wutils.h"

int main(int argc, char *argv[]){
    if (argc!=3) {
        printf("Please used --glove <filename.txt> or --word2vec <filename.bin>\n");
        return 1;
    }
    if (check_equals(argv[1],"--glove")) read_embedding_glove(argv[2]);

    else if (check_equals(argv[1],"--word2vec")) read_embedding_bin_file(argv[2]);
    else {
        printf("Please used --glove <filename.txt> or --word2vec <filename.bin>\n");
        return 1;
    }

    uint8_t arr[2];
    arr[0]=1;
    arr[1]=0;
    
    int found;
    char word[100];
    char *exit="EXIT";
    
    clock_t start,end;
    double seconds_quantization, seconds_similarity;
    
    printf("\n hello world \n\n");

    printf("\nPlease insert a word to search, digit EXIT to terminate \n");

    while(scanf("%s", word)==1 && check_equals(word,exit)==0){

        init_lista_risultato();

        init_lista_risultato_similarity();
        
        found = -1;
        
        for (unsigned long i=0; i<MAX_LEN_VOCABULARY; i++){
            if (check_equals(word,embedding_list[i].voce)==1){
                found=i;
                break;
            }
        }
        
        if (found==-1) {
            printf("\n word %s doesn't found, please write another word \n\n",word);
            continue;
        }

        printf("****** Quantization Similarity Search *****\n\n");
        
        start = clock();
        wquantization_similarity_search(&embedding_list[found]);
        end = clock();

        seconds_quantization = (double)(end - start) / CLOCKS_PER_SEC;
        
        printf("\n\n***** Similarity Search *****\n\n");
        start = clock();
        wsimilarity_search(&embedding_list[found]);
        end = clock();
       
        seconds_similarity = (double)(end - start) / CLOCKS_PER_SEC;


        printf("\n\nelapsed vector search with quantization similarity:   %.6f seconds\n", seconds_quantization);

        printf("elapsed vector search with similarity             :   %.6f seconds\n", seconds_similarity);


        printf("\n\n\nPlease insert a word to search, digit EXIT to terminate \n");

    }

    return 0;
}
