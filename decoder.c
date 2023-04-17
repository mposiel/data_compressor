//
// Created by maks on 17.04.23.
//

#include "decoder.h"
#include <stdio.h>
#include <stdlib.h>

//1 - incorrect input
//2 - couldn't open file
//3 - failed to allocate memory
//4 - file corrupted

int decode(char *filename1, char *filename2) {
    if (filename1 == NULL || filename2 == NULL) {
        return 1;
    }

    FILE *in = fopen(filename1, "rb");

    if (in == NULL) {
        return 2;
    }

    FILE *out = fopen(filename2, "w");

    if (out == NULL) {
        return 2;
    }

    int size;
    if (fread(&size, sizeof(int), 1, in) <= 0) {
        return 4;
    }

    struct node *root = read_huffman_tree(in);

    if (root == NULL) {
        return 3;
    }

    union buffer buf;
    int count = 0;

    for (int i = 0; i < size; ++i) {
        struct node cur;
        cur.left = root->left;
        cur.right = root->right;
        cur.freq = root->freq;
        cur.data = root->data;
        cur.is_leaf = root->is_leaf;
        fread(&buf.byte,sizeof(union buffer),1,in);
        while(cur.is_leaf != 1) {
            if(buf.bits.bit0)
        }

    }




    return 0;
}


struct node *read_huffman_tree(FILE *f) {
    int is_leaf;
    fread(&is_leaf, sizeof(int), 1, f);

    struct node *n = (struct node *) malloc(sizeof(struct node));
    if (n == NULL) {
        return NULL;
    }

    if (is_leaf) {
        char value;
        fread(&value, sizeof(char), 1, f);
        n->data = value;
        n->is_leaf = 1;
        n->left = NULL;
        n->right = NULL;
    } else {
        n->is_leaf = 0;
        n->left = read_huffman_tree(f);
        n->right = read_huffman_tree(f);
    }

    return n;
}