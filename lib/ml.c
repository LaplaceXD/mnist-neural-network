/** @file ml.c
 *  @brief A machine learning library made for working 
 *  with neural network training.
 * 
 *  This library contains various functions which allows
 *  users to clean, forward propagate, and evaluate data 
 *  in a neural network. It also allows users to train 
 *  Neural Network based on a dataset.
 *
 *  @author Jonh Alexis Buot (LaplaceXD)
 *  @bug No know bugs.
 */
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
        freeMatrix(&weighted); // free previous contents before assigning
        weighted = dot(res, layer->weights);

        // The first run of the loop res is data.inputValues
        // It should not be freed only the succeeding ones
        !isFirst ? freeMatrix(&res) : !isFirst;
        res = add(weighted, layer->bias);

        mapMatrix(res, activate);
    }

    return res;
}