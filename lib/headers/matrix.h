/** @file matrix.h
 *  @brief Function prototypes for the matrix library.
 *
 *  This contains the prototypes, type definitions,
 *  constants, and globals for the matrix library.
 * 
 *  @author Jonh Alexis Buot (LaplaceXD)
 *  @bug No known bugs.
 */

#ifndef _MATRIX_H
#define _MATRIX_H

/** @brief Structure of the Matrix which contains its 
 *  entries, and dimensions (rows, columns).
 */
typedef struct Matrix {
    double **entries;
    int row;
    int col;
} Matrix;

/** @brief Specifies the Axis of the Matrix. */
typedef enum MatrixAxis { ROW, COL } MatrixAxis;

/** @brief Returns a Matrix struct with the given row and column dimensions.
 * 
 *  @param row Number of rows in the matrix. 
 *  @param col Number of columns in the matrix.
 *  @return A Matrix with dimensions row x col.
 */
Matrix createMatrix(int row, int col);
/** @brief Fills all of the entries of matrix m, with the given value.
 * 
 *  @param m A pointer to the matrix to be filled with a value. 
 *  @param val The value that is would occupy the entries of m.
 *  @return Void.
 */
void fillMatrix(Matrix* m, double val);
/** @brief Frees the dynamically stored entries of the matrix,
 *  and sets the matrix's dimensions to 0x0.
 * 
 *  @param m A pointer to the matrix to be freed. 
 *  @return Void.
 */
void freeMatrix(Matrix* m);
/** @brief Print's the values of the matrix in the console,
 *  based on its dimensions. 
 * 
 *  @param m The matrix to be printed. 
 *  @return Void.
 */
void printMatrix(Matrix m);

/** @brief Adds two matrices together.
 * 
 *  The two matrices should be of the same dimensions.
 *  If the dimensions of the matrices do not match, then
 *  this function will throw an error. Else, it returns a
 *  matrix that contains the added result of the two
 *  matrices.
 * 
 *  @param a Addend matrix. 
 *  @param b Addend matrix. 
 *  @return A Matrix that is the sum of a and b.
 */
Matrix add(Matrix a, Matrix b);
/** @brief Scales the values of a matrix a by a factor val.
 * 
 *  @param a The matrix to be scaled. 
 *  @param val The factor the matrix should be scaled by. 
 *  @return A Matrix that has been scaled by a factor val.
 */
Matrix scale(double val, Matrix a); 
/** @brief Dot multiplies two matrices.
 * 
 *  The two matrices should have a row and column that are equal.
 *  If there is no row in one matrix that equals the column of the
 *  other matrix, then the function throws an error. Else, it
 *  returns the resulting matrix of the dot operation.
 * 
 *  @param a Factor matrix. 
 *  @param b Factor matrix. 
 *  @return A Matrix that contains the values of the dot operation.
 */
Matrix dot(Matrix a, Matrix b); 
/** @brief Flips the matrix's row and columns.
 * 
 *  @param a A pointer to the matrix to be transposed. 
 *  @return Void.
 */
void transpose(Matrix* a); 
/** @brief Flattens the matrix into a unit column or unit row matrix.
 * 
 *  @param a A pointer to the matrix to be flattened. 
 *  @param axis The axis [ROW, COL] the matrix is to be flattened. 
 *  @return Void.
 */
void flatten(Matrix* a, MatrixAxis axis); 

#endif /* _MATRIX_H */