/** @file matrix.c
 *  @brief A library made for working with matrices.
 * 
 *  This library contains various functions which allows
 *  users to create, and manipulate matrices through various
 *  operations (e.g., add, dot, scale, transpose, etc.). 
 *
 *  @author Jonh Alexis Buot (LaplaceXD)
 *  @bug No know bugs.
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "headers/matrix.h"

#define throwInvalidArgs(arg, msg) { fprintf(stderr, "Invalid %s Argument. %s", arg, msg); exit(1); }
#define throwMallocFailed() { fprintf(stderr, "Memory Allocation Failed."); exit(1); }
#define throwMismatchedDimensions(msg) { fprintf(stderr, "Matrix Dimensions Mismatched. %s", msg); exit(1); }
#define SHOULD_BE_POSITIVE "It should be a positive integer."
#define NOT_A_MATRIX "Argument is not a valid matrix."

Matrix createMatrix(int row, int col)
{
    if(row <= 0) throwInvalidArgs("row", SHOULD_BE_POSITIVE);
    if(col <= 0) throwInvalidArgs("col", SHOULD_BE_POSITIVE);
    
    Matrix m = { NULL, row, col };
    int idx;

    m.entries = (double **) malloc(row * sizeof(double*));
    if(m.entries == NULL) throwMallocFailed();
    
    for(idx = 0; idx < row; idx++) {
        m.entries[idx] = (double *) malloc(col * sizeof(double));
        if(m.entries[idx] == NULL) throwMallocFailed();
    }
    
    return m; 
}

Matrix createZeroMatrix()
{
    Matrix m = { NULL, 0, 0 };
    return m;
}

void fillMatrix(Matrix* m, double val)
{
    if(!isValidMatrix(*m)) throwInvalidArgs("m", NOT_A_MATRIX);

    int row, col;
    for(row = 0; row < m->row; row++) {
        for(col = 0; col < m->col; col++) {
            m->entries[row][col] = val;
        }
    }
}

void fillMatrixRandn(Matrix* m, double min, double max, double mult)
{
    if(!isValidMatrix(*m)) throwInvalidArgs("m", NOT_A_MATRIX);
    
    int row, col;
    double boundRand, range = min - max;

    for(row = 0; row < m->row; row++) {
        for(col = 0; col < m->col; col++) {
            boundRand = min + ((double) (rand() % RAND_MAX) / RAND_MAX) * range;
            m->entries[row][col] = boundRand * mult;
        }
    }
}

void freeMatrix(Matrix* m)
{
    if(!isValidMatrix(*m)) throwInvalidArgs("m", NOT_A_MATRIX);
    
    int row;
    for(row = 0; row < m->row; row++) {
        free(m->entries[row]);
    }

    free(m->entries);
    *m = createZeroMatrix();
}

void printMatrix(Matrix m)
{
    if(!isValidMatrix(m)) throwInvalidArgs("m", NOT_A_MATRIX);
    
    int row, col;
    for(row = 0; row < m.row; row++) {
        for(col = 0; col < m.col; col++) {
            printf("%5.2lf ", m.entries[row][col]);
        }

        printf("\n");
    }
}

int isValidMatrix(Matrix m)
{
    return (m.row > 0 && m.col > 0) || isZeroMatrix(m) ? 1 : 0;
}

int isColumnMatrix(Matrix m)
{
    if(!isValidMatrix(m)) throwInvalidArgs("m", NOT_A_MATRIX);
    // m.row > 1, since 1 x 1 matrices can be
    // tagged as column matrices, when they are not
    return m.row > 1 && m.col == 1 ? 1 : 0;
}

int isRowMatrix(Matrix m)
{
    if(!isValidMatrix(m)) throwInvalidArgs("m", NOT_A_MATRIX);
    // m.col > 1, since 1 x 1 matrices can be
    // tagged as row matrices, when they are not
    return m.row == 1 && m.col > 1 ? 1 : 0; 
}

int isZeroMatrix(Matrix m)
{
    return m.row == 0 && m.col == 0 ? 1 : 0;
}

Matrix add(Matrix a, Matrix b)
{
    if(!isValidMatrix(a)) throwInvalidArgs("a", NOT_A_MATRIX);
    if(!isValidMatrix(b)) throwInvalidArgs("b", NOT_A_MATRIX);
    if(a.row != b.row || a.col != b.col) throwInvalidArgs("Matrices can't be added.", "");

    Matrix m;
    int row, col;

    m = createMatrix(a.row, a.col);
    for(row = 0; row < a.row; row++) {
        for(col = 0; col < a.col; col++) {
            m.entries[row][col] = a.entries[row][col] + b.entries[row][col];
        }
    }

    return m;
}

Matrix scale(Matrix a, double val)
{
    if(!isValidMatrix(a)) throwInvalidArgs("a", NOT_A_MATRIX);
    
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
    if(!isValidMatrix(a)) throwInvalidArgs("a", NOT_A_MATRIX);
    if(!isValidMatrix(b)) throwInvalidArgs("b", NOT_A_MATRIX);
    if(a.col != b.row && b.col != a.row) throwMismatchedDimensions("Matrices can't be dotted.");
    
    Matrix m;
    int row, addTrav, col, sum;

    // swap a and b, if a.col != b.row, since it's possible that
    // b.col == a.row. This is also necessary for the dot calculation
    // to work, since it is required that a is to be traversed by row
    // and b to be traversed by col
    if(a.col != b.row) {
        m = a;
        a = b;
        b = m;
    }

    m = createMatrix(a.row, b.col);
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

void transpose(Matrix* a)
{
    if(!isValidMatrix(*a)) throwInvalidArgs("a", NOT_A_MATRIX);
    
    Matrix m = createMatrix(a->col, a->row);
    int row, col;
    
    for(row = 0; row < a->row; row++) {
        for(col = 0; col < a->col; col++) {
            m.entries[col][row] = a->entries[row][col];
        }
    }

    freeMatrix(a);
    *a = m;
}

void flatten(Matrix* a, MatrixAxis axis)
{
    if(!isValidMatrix(*a)) throwInvalidArgs("a", NOT_A_MATRIX);
    
    Matrix m;
    int row, col, matrixSize;

    matrixSize = a->row * a->col;
    if(axis == COL) {
        m = createMatrix(matrixSize, 1);
    } else if (axis == ROW) {
        m = createMatrix(1, matrixSize);
    } else {
        throwInvalidArgs("axis", "");
    }

    for(row = 0; row < a->row; row++) {
        for(col = 0; col < a->col; col++) {
            if(axis == COL) {
                m.entries[row * a->col + col][0] = a->entries[row][col];
            } else if (axis == ROW) {
                m.entries[0][row * a->col + col] = a->entries[row][col];
            }
        }
    } 
    
    freeMatrix(a);
    *a = m;
}

void copyMatrix(Matrix src, Matrix dest)
{
    if(!isValidMatrix(src)) throwInvalidArgs("src", NOT_A_MATRIX);
    if(!isValidMatrix(dest)) throwInvalidArgs("dest", NOT_A_MATRIX);
    if(dest.col < src.col && dest.row < src.row)
        throwInvalidArgs("", "Dimensions of source matrix must be equal or less than the dimensions of the dest matrix.");

    int row, col;

    for(row = 0; row < dest.row; row++) {
        for(col = 0; col < dest.col; col++) {
            dest.entries[row][col] = row < src.row && col < src.col ? src.entries[row][col] : 0;
        }
    }
}