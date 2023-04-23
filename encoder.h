//
// Created by maks on 16.04.23.
//

#ifndef DATA_COMPRESSOR_ENCODER_H
#define DATA_COMPRESSOR_ENCODER_H



struct node {
    char data;
    int freq;
    struct node *left;
    struct node *right;
    int is_leaf;
};

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

int encode(char *filename1, char *filename2);

struct node *char_freq(FILE *f, int *size);

void sort_by_freq(struct node *tab, int size);

struct node *delete_first_element(struct node *tab, int *size);

int write_huffman_tree(struct node *node, FILE *out);

char *code_of_char(struct node *root, char ch);

#endif //DATA_COMPRESSOR_ENCODER_H
