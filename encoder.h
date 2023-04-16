//
// Created by maks on 16.04.23.
//

#ifndef DATA_COMPRESSOR_ENCODER_H
#define DATA_COMPRESSOR_ENCODER_H

struct char_frequencies {
    char data;
    int freq;
};




struct node {
    char data;
    int freq;
    struct node *left;
    struct node *right;
};

int encode(char *filename1, char *filename2);

struct node *char_freq(FILE *f, int *size);

void sort_by_freq(struct node *tab, int size);

struct node *delete_first_element(struct node *tab, int *size);




#endif //DATA_COMPRESSOR_ENCODER_H
