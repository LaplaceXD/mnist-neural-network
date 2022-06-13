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

Matrix add(Matrix a, Matrix b)
{
    Matrix m;
    int row, col;

    if(a.row != b.row || a.col != b.col) {
        fprintf(stderr, "Matrices supplied can't be added. Mismatch in dimensions [A: %d x %d][B: %d x %d]", a.row, a.col, b.row, b.col);
        exit(1);
    }

    m = createMatrix(a.row, a.col);
    for(row = 0; row < a.row; row++) {
        for(col = 0; col < a.col; col++) {
            m.entries[row][col] = a.entries[row][col] + b.entries[row][col];
        }
    }

    return m;
}