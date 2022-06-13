#ifndef MATRIX_H_
#define MATRIX_H_

typedef struct Matrix {
    double **entries;
    int row;
    int col;
} Matrix;

typedef enum { ROW, COL } MatrixAxis;

Matrix createMatrix(int, int);
void fillMatrix(Matrix*, double);
void freeMatrix(Matrix*);
void printMatrix(Matrix);

Matrix add(Matrix, Matrix);
Matrix scale(double, Matrix); 
Matrix dot(Matrix, Matrix); 
void transpose(Matrix*); 
void flatten(Matrix*, MatrixAxis); 

#endif