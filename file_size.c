//
// Created by Maks on 18.04.2023.
//

#include "file_size.h"

long file_size(char *filename) {
    if (filename == NULL) {
        return -1;
    }
    FILE *f = fopen(filename, "rb");
    if (f == NULL) {
        return -2;
    }
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fclose(f);
    return size;
}
