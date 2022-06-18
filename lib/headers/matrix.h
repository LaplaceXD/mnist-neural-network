/** @file matrix.h
 *  @brief Function prototypes for the matrix library.
 *
 *  This contains the prototypes, type definitions,
 *  constants, and globals for the matrix library.
 * 
 *  @author Jonh Alexis Buot (LaplaceXD)
 *  @bug No known bugs.
 */

#pragma once

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
/** @brief Returns a Matrix struct with a 0 x 0 dimension.
 * 
 *  @return A Matrix with dimensions 0 x 0.
 */
Matrix createZeroMatrix();
/** @brief Fills all of the entries of matrix m, with the given value.
 * 
 *  @param m A pointer to the matrix to be filled with a value. 
 *  @param val The value that is would occupy the entries of m.
 *  @return Void.
 */
void fillMatrix(Matrix* m, double val);
/** @brief Fills all of the entries of matrix m, with a randomly generated
 *  value.
 * 
 *  @param m A pointer to the matrix to be filled with a value. 
 *  @param min The minimum possible value to be randomly generated. 
 *  @param max The maximum possible value to be randomly generated. 
 *  @param mult A scaling factor to the randomly generated values
 *  (set to 1, if you don't want to scale the values).
 *  @return Void.
 */
void fillMatrixRandn(Matrix* m, double min, double max, double mult);
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

/** @brief Checks if the matrix supplied is
 *  valid. 
 * 
 *  @param m The matrix to be checked. 
 *  @return 1 - If matrix is valid. 0 - If it is not.
 */
int isValidMatrix(Matrix m);
/** @brief Checks if the matrix supplied is
 *  a column matrix. 
 * 
 *  @param m The matrix to be checked. 
 *  @return 1 - If matrix is a column matrix. 
 *  0 - If it is not.
 */
int isColumnMatrix(Matrix m);
/** @brief Checks if the matrix supplied is
 *  a row matrix. 
 * 
 *  @param m The matrix to be checked. 
 *  @return 1 - If matrix is a row matrix. 
 *  0 - If it is not.
 */
int isRowMatrix(Matrix m);
/** @brief Checks if the matrix supplied is
 *  a zero matrix. 
 * 
 *  @param m The matrix to be checked. 
 *  @return 1 - If matrix is a zero matrix. 
 *  0 - If it is not.
 */
int isZeroMatrix(Matrix m);

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
Matrix scale(Matrix a, double val); 
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

/** @brief Copies the entries of a src matrix into
 *  the the entries of a destination matrix with similar
 *  size. If the src is smaller than the dest, then the 
 *  dest entries is padded with 0s.
 *  
 *  NOTE: The dimensions of the destination matrix must be bigger
 *  or equal to the dimensions of the source matrix.
 *  
 *  @param dest The destination matrix. 
 *  @param src The source matrix. 
 *  @return Void.
 */
void copyMatrix(Matrix src, Matrix dest);
/** @brief Copies the contents of an array into 
 *  a matrix following a row-first order. 
 *  
 *  If the size of the array is lesser than 
 *  that of the matrix, then the matrix is padded
 *  with 0s. Else if, the size of the array is bigger
 *  then only the contents up to the size of the 
 *  matrix size would be copied, and the rest would be 
 *  cut-off.
 * 
 *  @param src The source array whose contents are 
 *  to be copied.
 *  @param size The size of the source array.
 *  @param dest The matrix destination for the contents.
 *  @return Void.
 */
void copyArrToMatrix(double *src, int size, Matrix dest);
/** @brief Copies the contents of a matrix into an array
 *  following a row-first order.
 *  
 *  If the matrix has a bigger size than the destination
 *  array, then only the contents up to the size of the
 *  array would be copied, and teh rest would be cut-off.
 * 
 *  @param src The source matrix whose contents are 
 *  to be copied.
 *  @param dest The array destination for the contents.
 *  @param size The size of the destination array.
 *  @return Void.
 */ 
void copyMatrixToArr(Matrix src, double *dest, int size);