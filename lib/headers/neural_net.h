/** @file neural_net.h
 *  @brief Function prototypes for the neural net library.
 * 
 *  This contains the prototypes, type definitions,
 *  constants, and globals for the nueral net library.
 *
 *  DEPENDENCIES: matrix, doubly_ll
 *  
 *  @author Jonh Alexis Buot (LaplaceXD)
 *  @bug No known bugs.
 */

#pragma once   

#include "matrix.h"
#include "doubly_ll.h"

/** @brief The different weight initialization strategies that can be utilized for the neural net.
 * https://towardsdatascience.com/weight-initialization-techniques-in-neural-networks-26c649eb3b78
 */
typedef enum { RANDOM, ZERO, HE, XAVIER, HE_XAVIER } DistStrategy;
/** @brief The different layer types. */
typedef enum { INPUT, HIDDEN, OUTPUT } LayerType;

/** @brief Stucture for the Layer of the Neural Network. */
typedef struct Layer {
    int nodes;
    LayerType type;
    Matrix weights;
    Matrix bias;
} Layer;

/** @brief Stucture for the LayerDesign. */
typedef struct LayerDesign {
    int nodes;
    LayerType type; 
} LayerDesign;

/** @brief Stucture for the NeuralNetOptions. */
typedef struct NeuralNetOpt {
    DistStrategy distStrat;
    double distSize;
    double initialBias;
} NeuralNetOpt;

/** @brief Stucture for the NeuralNetwork. */
typedef struct NeuralNetwork {
    NeuralNetOpt options;
    DoublyLinkedList layers;
} NeuralNetwork;

/** @brief Creates a Neural Network.
 *  
 *  @param opt Configured options in creating the
 *  Neural Network.
 *  @param layers An array of layers to be initialized
 *  in the Neural Network.
 *  @param size The number of layers in the layers array.
 *  @return A Neural Network.
 */
NeuralNetwork createNeuralNet(NeuralNetOpt opt, LayerDesign *layers, int size);
/** @brief Creates the options for the Neural Network.
 *  
 *  @param dist The distribution type used to initialize
 *  the weights of the layers.
 *  @param distSize The spread of the distribution.
 *  @param initialBias The initial bias value used to
 *  intialize the biases of the layers.
 *  @return Options for a Neural Network.
 */
void addLayer(NeuralNetwork *nn, int nodes, LayerType type);
/** @brief Removes a layer from the Neural Network,
 *  based on a given position.
 * 
 *  @param nn A pointer to the Neural Network where 
 *  the layer would be attached to.
 *  @param pos The position of the layer in the
 *  Neural Network (starting at 1).
 *  @return Void. 
 */
void insertLayer(NeuralNetwork *nn, int pos, int nodes, LayerType type);
/** @brief Deletes a layer from the Neural Network,
 *  based on a given position.
 * 
 *  @param nn A pointer to the Neural Network where 
 *  the layer would be attached to.
 *  @param pos The position of the layer in the
 *  Neural Network (starting at 1).
 *  @return Void. 
 */
void deleteLayer(NeuralNetwork *nn, int pos);
/** @brief Frees the Neural Network from memory.
 * 
 *  @param nn A pointer to the Neural Network to be freed. 
 *  @return Void. 
 */
void freeNeuralNet(NeuralNetwork *nn);