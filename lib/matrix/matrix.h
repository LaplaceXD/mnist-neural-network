#ifndef MATRIX_H_
#define MATRIX_H_

typedef struct {
    double **entries;
    int row;
    int col;
} Matrix;

typedef enum { ROW, COL } MatrixAxis;

Matrix createMatrix(int, int);
void fillMatrix(Matrix*, int);

Matrix add(Matrix, Matrix);
Matrix scale(int, Matrix); 
Matrix dot(int, Matrix); 
void transpose(Matrix*); 
void flatten(Matrix*, MatrixAxis); 

#endif