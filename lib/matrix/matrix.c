#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

Matrix createMatrix(int row, int col)
{
    Matrix m = { NULL, row, col };
    int idx;
    
    if(row <= 0 || col <= 0) {
        fprintf(
            stderr,
            "Matrix creation failed. Invalid dimensions were supplied: %d x %d.",
            row, col
        );
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

void fillMatrix(Matrix* m, double val)
{
    int row, col;
    for(row = 0; row < m->row; row++) {
        for(col = 0; col < m->col; col++) {
            m->entries[row][col] = val;
        }
    }
}

void freeMatrix(Matrix* m)
{
    int row;
    for(row = 0; row < m->row; row++) {
        free(m->entries[row]);
    }

    free(m->entries);
    m->row = 0;
    m->col = 0;
}

void printMatrix(Matrix m)
{
    int row, col;
    for(row = 0; row < m.row; row++) {
        for(col = 0; col < m.col; col++) {
            printf("%20d ", m.entries[row][col]);
        }

        printf("\n");
    }
}

Matrix add(Matrix a, Matrix b)
{
    Matrix m;
    int row, col;

    if(a.row != b.row || a.col != b.col) {
        fprintf(
            stderr,
            "Matrices supplied can't be added. Mismatch in dimensions [A: %d x %d][B: %d x %d]",
            a.row, a.col, b.row, b.col
        );
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

Matrix scale(double val, Matrix a)
{
    Matrix m = createMatrix(a.row, a.col);
    int row, col;
    
    for(row = 0; row < a.row; row++) {
        for(col = 0; col < a.col; col++) {
            m.entries[row][col] = val * a.entries[row][col];
        }
    }

    return m;
}

Matrix dot(Matrix a, Matrix b)
{
    Matrix m;
    // addTrav is for traversing the column a matrix col, and b matrix row for getting the products
    // col is for traversing the b columns, and row is for traversing the a rows
    // sum is used to store the sum for each row-col dot multiplication
    int row, addTrav, col, sum;

    if(a.col != b.row) {
        fprintf(
            stderr, 
            "Matrices supplied can't be dotted. Mismatch in dimensions [A: %d x %d][B: %d x %d]",
            a.row, a.col, b.row, b.col
        );
        exit(1);
    }

    m = createMatrix(a.col, b.row);
    for(row = 0; row < a.row; row++) {
        for(col = 0; col < b.col; col++) {
            sum = 0;
            
            for(addTrav = 0; addTrav < a.col; addTrav++) {
                sum += a.entries[row][addTrav] * b.entries[addTrav][col];
            }

            m.entries[row][col] = sum;
        }
    }

    return m;
}