//
// Created by maks on 16.04.23.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "encoder.h"

//1 - incorrect input
//2 - failed to open file
//3 - failed to allocate memory
//4 - file corrupted


// struktura pliku:
// 1. ilość znaków (int)
// 2. drzewo
// 3. zakodowany tekst


int encode(char *filename1, char *filename2) {
    if (filename1 == NULL || filename2 == NULL) {
        return 1;
    }

    FILE *in = fopen(filename1, "r");
    if (in == NULL) {
        return 2;
    }
    if (fgetc(in) == EOF) {
        return 4;
    }
    fseek(in, 0, SEEK_SET);

    FILE *out = fopen(filename2, "wb");
    if (out == NULL) {
        fclose(in);
        return 2;
    }


    int size;
    struct node *node_heap = char_freq(in, &size);

    if (node_heap == NULL) {
        fclose(in);
        fclose(out);
        return 5;
    }


    sort_by_freq(node_heap, size);


    while (size > 1) {
        struct node cur;
        cur.freq = node_heap->freq + (node_heap + 1)->freq;
        cur.right = (node_heap + 1);
        cur.is_leaf = 0;

        cur.left = malloc(sizeof(struct node));
        if (cur.left == NULL) {

            return 3;
        }
        *cur.left = *node_heap;
        node_heap = delete_first_element(node_heap, &size);
        node_heap[0] = cur;
        sort_by_freq(node_heap, size);
    }


    int size_of_txt = node_heap->freq;

    fwrite(&size_of_txt, sizeof(int), 1, out);

    int err1 = write_huffman_tree(node_heap, out);
    if (err1 == 1) {
        fclose(in);
        fclose(out);
        return 1;
    }


    union buffer buf;
    buf.byte = 0;
    int bits_in_buf = 0;

    fseek(in, 0, SEEK_SET);
    for (int i = 0; i < size_of_txt; ++i) {
        char c = (char) fgetc(in);
        char *code = code_of_char(node_heap, c);
        if (code == NULL) {
            fclose(in);
            fclose(out);
            return 1;
        }
        int code_size = (int) strlen(code);


        for (int j = 0; j < code_size; ++j) {
            if (bits_in_buf == 8) {
                fwrite(&buf, sizeof(buf), 1, out);
                buf.byte = 0;
                bits_in_buf = 0;
            }
            if (code[j] == '0') {
                buf.bits.bit0 = 0;
            } else {
                buf.bits.bit0 = 1;
            }
            if (bits_in_buf != 7) {
                buf.byte = buf.byte << 1;
            }
            bits_in_buf++;
        }


    }
    if (bits_in_buf > 0) {
        buf.byte <<= (8 - bits_in_buf);
        fwrite(&buf, sizeof(buf), 1, out);
    }

    fclose(in);
    fclose(out);
    return 0;
}

struct node *char_freq(FILE *f, int *size) {
    if (size == NULL) {
        return NULL;
    }

    struct char_frequencies {
        int data;
        int freq;
    };

    struct char_frequencies *freq_tab = malloc(256 * sizeof(struct char_frequencies));
    if (freq_tab == NULL) {
        return NULL;
    }
    for (int i = 0; i < 256; ++i) {
        (freq_tab + i)->data = i;
        (freq_tab + i)->freq = 0;
    }

    char c;
    while ((c = fgetc(f)) != EOF) {
        (freq_tab + c)->freq += 1;
    }

    *size = 0;
    for (int i = 0; i < 256; ++i) {
        if ((freq_tab + i)->freq != 0) {
            (*size)++;
        }
    }

    if (*size == 0) {
        free(freq_tab);
        return NULL;
    }

    struct node *node_tab = malloc(*size * sizeof(struct node));
    if (node_tab == NULL) {
        free(freq_tab);
        return NULL;
    }

    int j = 0;
    for (int i = 0; i < 256; ++i) {
        if ((freq_tab + i)->freq != 0) {
            (node_tab + j)->freq = (freq_tab + i)->freq;
            (node_tab + j)->data = (freq_tab + i)->data;
            (node_tab + j)->left = NULL;
            (node_tab + j)->right = NULL;
            (node_tab + j)->is_leaf = 1;
            j++;
        }
    }

    free(freq_tab);
    return node_tab;
}

int compare(const void *a, const void *b) {

    struct node *nodeA = (struct node *) a;
    struct node *nodeB = (struct node *) b;

    return (nodeA->freq - nodeB->freq);
}

void sort_by_freq(struct node *tab, int size) {
    if (tab == NULL) {
        return;
    }
    qsort(tab, size, sizeof(struct node), compare);
}


struct node *delete_first_element(struct node *tab, int *size) {
    if (tab == NULL || size == NULL || *size <= 0) {
        return NULL;
    }

    struct node *new_tab = malloc((*size - 1) * sizeof(struct node));
    if (new_tab == NULL) {
        return NULL;
    }

    for (int i = 1; i < *size; ++i) {
        *(new_tab + i - 1) = *(tab + i);
    }
    free(tab);
    *size -= 1;
    return new_tab;
}

int write_huffman_tree(struct node *node, FILE *out) {
    if (node == NULL) {
        return 0;
    }

    if (node->is_leaf) {
        unsigned char bit = 1;
        fwrite(&bit, sizeof(unsigned char), 1, out);
        fwrite(&(node->data), sizeof(char), 1, out);
        return 0;
    }

    unsigned char bit = 0;
    fwrite(&bit, sizeof(unsigned char), 1, out);

    int err1 = write_huffman_tree(node->left, out);
    int err2 = write_huffman_tree(node->right, out);

    if (err1 == 1 || err2 == 1) {
        return 1;
    }

    return 0;
}


char *code_of_char(struct node *root, char ch) {
    if (root == NULL) {
        return NULL;
    }

    if (root->left == NULL && root->right == NULL && root->data == ch) {
        char *code = (char *) malloc(sizeof(char));
        code[0] = '\0';
        return code;
    }


    char *left_code = code_of_char(root->left, ch);
    if (left_code != NULL) {

        size_t len = strlen(left_code);
        char *code = (char *) malloc(len + 2);
        code[0] = '0';
        strcpy(code + 1, left_code);
        free(left_code);
        return code;
    }


    char *right_code = code_of_char(root->right, ch);
    if (right_code != NULL) {
        size_t len = strlen(right_code);
        char *code = (char *) malloc(len + 2);
        code[0] = '1';
        strcpy(code + 1, right_code);
        free(right_code);
        return code;
    }


    return NULL;
}


