//
// Created by maks on 17.04.23.
//

#ifndef DATA_COMPRESSOR_DECODER_H
#define DATA_COMPRESSOR_DECODER_H

#include <stdio.h>
#include "encoder.h"



int decode(char *filename1, char *filename2);
struct node *read_huffman_tree(FILE *f);

#endif //DATA_COMPRESSOR_DECODER_H
