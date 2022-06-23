/** @file ml.c
 *  @brief A machine learning library made for working 
 *  with neural network training.
 * 
 *  This library contains various functions which allows
 *  users to clean, forward propagate, and evaluate data 
 *  in a neural network. It also allows users to train 
 *  Neural Network based on a dataset.
 *
 *  DEPENDENCIES: matrix, stats, neural_net 
 *  
 *  @author Jonh Alexis Buot (LaplaceXD)
 *  @bug No know bugs.
 */
#include <math.h>
#include "headers/matrix.h"
#include "headers/stats.h"
#include "headers/neural_net.h"
#include "headers/ml.h"

#define throwInvalidArgs(arg, msg) { fprintf(stderr, "Invalid %s Argument. %s", arg, msg); exit(1); }
#define SHOULD_NOT_BE_NULL "It should not be a null value."
#define SHOULD_BE_POSITIVE "It should be a positive number."

void prepData(Data *data, MatrixAxis axis, TransformFunc transform)
{
    if(axis != ROW && axis != COL) throwInvalidArgs("axis", "");
    if(transform == NULL) throwInvalidArgs("transform", SHOULD_NOT_BE_NULL);

    flatten(&data->inputValues, ROW);
    transform(data->inputValues.entries[0], data->inputValues.col);

    if(axis == COL) {
        transpose(&data->inputValues);
    }
}

void prepDataset(Data dataset[], int size, MatrixAxis axis, TransformFunc transform)
{
    if(size <= 0) throwInvalidArgs("size", SHOULD_BE_POSITIVE);
    if(axis != ROW && axis != COL) throwInvalidArgs("axis", "");
    if(transform == NULL) throwInvalidArgs("transform", SHOULD_NOT_BE_NULL);

    int idx;    

    for(idx = 0; idx < size; idx++) {
        prepData(dataset+idx, axis, transform);
    }
}

Matrix forwardPropagate(Data data, NeuralNetwork nn, ActivationFunc activate)
{
    if(activate == NULL) throwInvalidArgs("activate", SHOULD_NOT_BE_NULL);

    int isFirst = 1;
    Layer *layer;
    Matrix res, weighted;

    res = data.inputValues;
    copyMatrix(data.inputValues, res);
    
    weighted = createZeroMatrix();
    layer = travNeuralNet(&nn, FORWARD);

    while(layer = travNeuralNet(NULL, FORWARD)) {
        weighted = dot(res, layer->weights);

        // The first run of the loop res is data.inputValues
        // It should not be freed only the succeeding ones
        !isFirst ? freeMatrix(&res) : !isFirst;
        res = add(weighted, layer->bias);

        mapMatrix(res, activate);
        
        // free weights before the next assignment
        freeMatrix(&weighted);
    }

    return res;
}

Matrix ssrPrime(Matrix obs[], Matrix exp[], int size)
{
    Matrix diff, sum, buffer;
    int idx;

    sum = createZeroMatrix();
    for(idx = 0; idx < size; idx++) {
        diff = subtract(exp[idx], obs[idx]);

        if(isZeroMatrix(sum)) {
            sum = diff;
        } else {
            buffer = add(sum, diff);
            freeMatrix(&sum);
            sum = buffer;
            freeMatrix(&diff);
        }
        printMatrix(sum);
    }

    buffer = scale(sum, -2.0);
    freeMatrix(&sum);

    return buffer;
}

double networkTest(Data dataset[], int size, NeuralNetwork nn, ActivationFunc activate)
{
    if(size <= 0) throwInvalidArgs("size", SHOULD_BE_POSITIVE);
    if(activate == NULL) throwInvalidArgs("activate", SHOULD_NOT_BE_NULL);
    
    int idx, resVal, correctItems;
    Matrix res;

    correctItems = 0;
    for(idx = 0; idx < size; idx++) {
        res = forwardPropagate(dataset[idx], nn, activate);
        resVal = evalResult(res);

        if(resVal == dataset[idx].expVal) {
            correctItems++;
        }

        freeMatrix(&res);
    }

    return (double) correctItems / size;
}

int evalResult(Matrix m)
{
    if(!isValidMatrix(m)) throwInvalidArgs("m", "Matrix is in an invalid format.");

    int row, col, maxRow, maxCol;

    maxRow = 0;
    maxCol = 0;
    for(row = 0; row < m.row; row++) {
        for(col = 0; col < m.col; col++) {
            if(m.entries[row][col] > m.entries[maxRow][maxCol]) {
                maxRow = row;
                maxCol = col;
            }
        }
    }

    return maxRow * m.col + maxCol;
}

double sigmoid(double val)
{
    return 1.0 / (1 + exp(-1 * val));
}

double reLU(double val)
{
    return val > 0 ? val : 0;
}

double sigmoidPrime(double val)
{
    double x = exp(-1 * val);
    double y = 1 + x;

    return x / (y * y);
}

double reLUPrime(double val)
{
    return val > 0 ? 1 : 0;
}

double tanhPrime(double val)
{
    double x = tanh(val);

    return 1 - x * x;
}