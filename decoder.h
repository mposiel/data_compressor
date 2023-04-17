//
// Created by maks on 17.04.23.
//

#ifndef DATA_COMPRESSOR_DECODER_H
#define DATA_COMPRESSOR_DECODER_H

#include <stdio.h>

union buffer {
    struct {
        unsigned char bit0: 1;
        unsigned char bit1: 1;
        unsigned char bit2: 1;
        unsigned char bit3: 1;
        unsigned char bit4: 1;
        unsigned char bit5: 1;
        unsigned char bit6: 1;
        unsigned char bit7: 1;
    } bits;
    unsigned char byte;
};

struct node {
    char data;
    int freq;
    struct node *left;
    struct node *right;
    int is_leaf;
};


int decode(char *filename1, char *filename2);
struct node *read_huffman_tree(FILE *f);

#endif //DATA_COMPRESSOR_DECODER_H
