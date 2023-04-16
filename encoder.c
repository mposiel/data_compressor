//
// Created by maks on 16.04.23.
//
#include <stdio.h>
#include <stdlib.h>

#include "encoder.h"

//1 - incorrect input
//2 - failed to open file
//3 - failed to allocate memory
//4 - file corrupted

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
        return 3;
    }
    sort_by_freq(node_heap, size);

    while (size > 1) {
        struct node cur;
        cur.freq = node_heap->freq + (node_heap + 1)->freq;
        cur.right = (node_heap + 1);
        cur.left = node_heap;
        node_heap = delete_first_element(node_heap,&size);
        node_heap[0] = cur;
        sort_by_freq(node_heap, size);
    }



    return 0;
}

struct node *char_freq(FILE *f, int *size) {

    if (f == NULL) {
        return NULL;
    }

    struct char_frequencies *freq_tab = malloc(256 * sizeof(struct char_frequencies));
    if (freq_tab == NULL) {
        return NULL;
    }
    for (int i = 0; i < 256; ++i) {
        (freq_tab + i)->data = i;
        (freq_tab + i)->freq = 0;
    }

    char c;
    while (1) {
        c = fgetc(f);
        if (c == EOF) {
            break;
        }
        (freq_tab + c)->freq += 1;
    }


    for (int i = 0; i < 256; ++i) {
        if ((freq_tab + i)->freq != 0) {
            (*size)++;
        }
    }

    struct node *node_tab = malloc(*size * sizeof(struct node));

    if (node_tab == NULL) {
        return NULL;
    }

    int j = 0;
    for (int i = 0; i < 256; ++i) {
        if ((freq_tab + i)->freq != 0) {
            (node_tab + j)->freq = (freq_tab + i)->freq;
            (node_tab + j)->data = (freq_tab + i)->data;
            (node_tab + j)->right = NULL;
            (node_tab + j)->left = NULL;
            j++;
        }
    }


    return node_tab;
}

int compare(const void *a, const void *b) {

    struct node *nodeA = (struct node *) a;
    struct node *nodeB = (struct node *) b;

    return (nodeB->freq - nodeA->freq);
}

void sort_by_freq(struct node *tab, int size) {
    if (tab == NULL) {
        return;
    }
    qsort(tab, size, sizeof(struct node), compare);
}


struct node *delete_first_element(struct node *tab, int *size) {
    if(tab==NULL || size==NULL || *size<=0) {
        return NULL;
    }

    struct node *new_tab = malloc((*size-1) * sizeof(struct node));
    if(new_tab==NULL) {
        return NULL;
    }

    for (int i = 1; i < *size; ++i) {
        *(new_tab + i - 1) = *(tab + i);
    }
    free(tab);
    *size -=1;
    return new_tab;
}