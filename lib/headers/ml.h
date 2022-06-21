/** @file ml.h
 *  @brief Function prototypes for the machine learning 
 *  library.
 *
 *  This contains the prototypes, type definitions,
 *  constants, and globals for the machine learning 
 *  library.
 * 
 *  DEPENDENCIES: matrix, stats, neural_net 
 * 
 *  @author Jonh Alexis Buot (LaplaceXD)
 *  @bug No known bugs.
 */
#pragma once

#include "stats.h"
#include "matrix.h"
#include "neural_net.h"

/** @brief A simple data structure. */
typedef struct Data {
    // Expected Value based on input
    int expVal;
    // Input values that are fed to a neural net
    // that should result into the expected value
    Matrix inputValues; 
} Data;

/** @brief The function called to activate the nodes of the layers of the Neural Network. */
typedef MapFunc ActivationFunc;

/** @brief Formats the data into a much understandable format 
 *  by the Neural Network to maximize learning.
 * 
 *  The input values of the data is flattened based on an 
 *  axis, and then formatted based on a transform function.
 * 
 *  @param data A pointer to the data to be prepared.
 *  @param axis The matrix axis that the input values should 
 *  be flattened to. This should be the same as the node orientation 
 *  of the Neural Network to be able to feed it properly.
 *  @param transform The transforming function to map the values 
 *  of the Data into a much suitable format for the Neural Network.
 *  @return Void.
 */
void prepData(Data *data, MatrixAxis axis, TransformFunc transform);
/** @brief Formats an entire dataset into a much understandable format 
 *  by the Neural Network to maximize learning.
 * 
 *  The input values of the data is flattened based on an 
 *  axis, and then formatted based on a transform function.
 * 
 *  @param data The dataset to be prepared.
 *  @param axis The matrix axis that the input values should 
 *  be flattened to. This should be the same as the node orientation 
 *  of the Neural Network to be able to feed it properly.
 *  @param transform The transforming function to map the values 
 *  of the Data in the dataset into a much suitable format for 
 *  the Neural Network.
 *  @return Void.
 */
void prepDataset(Data dataset[], int size, MatrixAxis axis, TransformFunc transform);
/** @brief Forward propagates the data through the layers of the 
 *  Network. After propagation it returns the resulting matrix 
 *  from the output layer.
 * 
 *  @param data The data to be propagated through the Neural Network.
 *  @param nn The Neural Network which the data would be 
 *  propagated through.
 *  @param activate The activation function to activate the neurons 
 *  in the Neural Network (sigmoid, reLU, tanh).
 *  @return The resulting matrix from the output layer after 
 *  propagation.
 */
Matrix forwardPropagate(Data data, NeuralNetwork nn, ActivationFunc activate);
/** @brief Trains a Neural Network based on a given dataset.
 *  
 *  @param dataset The dataset that the Neural Network has to learn.
 *  @param size The size of the dataset.
 *  @param nn The Neural Network to be trained.
 *  @param activate The activation function to activate the neurons 
 *  in the Neural Network (sigmoid, reLU, tanh).
 *  @return Void. 
 */
void networkTrain(Data dataset[], int size, NeuralNetwork nn, ActivationFunc activate);
/** @brief Tests a Neural Network based on a given dataset.
 *  
 *  @param dataset The dataset that the Neural Network has to test against.
 *  @param size The size of the dataset.
 *  @param nn The Neural Network to be tested.
 *  @param activate The activation function to activate the neurons 
 *  in the Neural Network (sigmoid, reLU, tanh).
 *  @return The accuracy of the neural network's prediction 
 *  in decimal.
 */
double networkTest(Data dataset[], int size, NeuralNetwork nn, ActivationFunc activate);
/** @brief Evaluates the resulting matrix and returns the predicted value 
 *  by the Neural Network as an integer.
 * 
 *  @param m The resulting matrix given by the output layer, as a result of 
 *  forward propagation.
 *  @return The integer representation of the resulting matrix.
 */
int evalResult(Matrix m);

/** @brief A function used in activation.
 *  
 *  @param val The value that the sigmoid function takes in.
 *  @return The result from applying the sigmoid function.
 */
double sigmoid(double val);
/** @brief A function used in activation.
 *  
 *  @param val The value that the reLu function takes in.
 *  @return The result from applying the reLu function.
 */
double reLU(double val);
// tanh function is in math.h

/** @brief The derivative of sigmoid.
 *  
 *  @param val The value that the derivative of the 
 *  sigmoid function takes in.
 *  @return The result from the function.
 */
double sigmoidPrime(double val);
/** @brief The derivative of reLu.
 *  
 *  @param val The value that the derivative of the 
 *  reLu function takes in.
 *  @return The result from the function.
 */
double reLUPrime(double val);
/** @brief The derivative of tanh.
 *  
 *  @param val The value that the derivative of the 
 *  tanh function takes in.
 *  @return The result from the function.
 */
double tanhPrime(double val);