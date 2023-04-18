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
    char *filename2 = malloc(size * sizeof(char));
    if (filename2 == NULL) {
        return NULL;
    }
    strcpy(filename2, filename1);
    *(filename2 + size - 1) = 'n';
    *(filename2 + size - 1) = 'i';
    *(filename2 + size - 1) = 'b';
    return filename2;
}

char *filename_decoded(char *filename1) {
    if (filename1 == NULL) {
        return NULL;
    }
    int size = strlen(filename1);
    char *filename2 = malloc(size * sizeof(char));
    if (filename2 == NULL) {
        return NULL;
    }
    strcpy(filename2, filename1);
    *(filename2 + size - 1) = 't';
    *(filename2 + size - 1) = 'x';
    *(filename2 + size - 1) = 't';
    return filename2;
}


