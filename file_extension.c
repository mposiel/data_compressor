//
// Created by maks on 17.04.23.
//

#include "file_extension.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//1 - .bin
//2 - .txt
//0 - none


int valid_type(char *filename) {
    if (filename == NULL) {
        return -1;
    }

    int size = strlen(filename);

    if (*(filename + size - 1) == 'n' && *(filename + size - 2) == 'i' && *(filename + size - 3) == 'b' &&
        *(filename + size - 4) == '.') {
        return 1;
    } else if (*(filename + size - 1) == 't' && *(filename + size - 2) == 'x' && *(filename + size - 3) == 't' &&
               *(filename + size - 4) == '.') {
        return 2;
    } else {
        return 0;
    }
}

char *filename_encoded(char *filename1) {
    if (filename1 == NULL) {
        return NULL;
    }
    int size = strlen(filename1);
    if (size > 15) {
        if (*(filename1 + size - 1) == 'd' && *(filename1 + size - 2) == 'e' && *(filename1 + size - 3) == 's' &&
            *(filename1 + size - 4) == 's' && *(filename1 + size - 5) == 'e' && *(filename1 + size - 6) == 'r' &&
            *(filename1 + size - 7) == 'p' && *(filename1 + size - 8) == 'm' && *(filename1 + size - 9) == 'o' &&
            *(filename1 + size - 10) == 'c' && *(filename1 + size - 11) == '_') {
            char *filename2 = malloc((size - 11) * sizeof(char));
            if(filename2==NULL) {
                return NULL;
            }
            fprintf(filename2,)
        }
    }
}



