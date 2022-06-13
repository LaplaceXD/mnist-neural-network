#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

Matrix createMatrix(int row, int col)
{
    Matrix m = { NULL, row, col };
    int idx;
    
    if(row <= 0 || col <= 0) {
        fprintf(stderr, "Matrix creation failed. Invalid dimensions were supplied: %d x %d.", row, col);
        exit(1);
    }
    
    m.entries = (double **) malloc(row * sizeof(double*));
    if(m.entries == NULL) {
        fprintf(stderr, "Memory allocation failed.");
        exit(1);
    }
    
    for(idx = 0; idx < col; idx++) {
        m.entries[idx] = (double *) malloc(col * sizeof(double));
        if(m.entries[idx] == NULL) {
            fprintf(stderr, "Memory allocation failed.");
            exit(1);
        }
    }

    return m; 
}

void fillMatrix(Matrix* m, int val)
{
    int row, col;
    for(row = 0; row < m->row; row++) {
        for(col = 0; col < m->col; col++) {
            m->entries[row][col] = val;
        }
    }
}