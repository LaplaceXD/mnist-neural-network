/** @file neural_net.h
 *  @brief Function prototypes for the neural net library.
 * 
 *  This contains the prototypes, type definitions,
 *  constants, and globals for the nueral net library.
 * 
 *  @author Jonh Alexis Buot (LaplaceXD)
 *  @bug No known bugs.
 */

#pragma once   

#include "matrix.h"

/** @brief The different weight initialization strategies that can be utilized for the neural net.
 * https://towardsdatascience.com/weight-initialization-techniques-in-neural-networks-26c649eb3b78
 */
typedef enum { RANDOM, ZERO, HE, XAVIER, HE_XAVIER, NONE } WeightInitType;
/** @brief The different layer types. */
typedef enum { INPUT, HIDDEN, OUTPUT } LayerType;

/** @brief Stucture for the Layer of the Neural Network. */
typedef struct Layer {
    int nodes;
    LayerType type;
    Matrix weights;
    Matrix bias;
} Layer;

/** @brief Stucture for the LayerNode. */
typedef struct LayerNode {
    Layer layer;
    struct LayerNode *next;
} *NeuralNetwork;

/** @brief Creates a Neural Network.
 *  
 *  @return Void.
 */
NeuralNetwork createNeuralNet();
/** @brief Add a layer to a Neural Network.
 * 
 *  @param nn A pointer to the Neural Network where 
 *  the layer would be attached to.
 *  @param nodes The number of nodes in the layer.
 *  @param type The type of the layer (Input, Hidden, Output).
 *  @param initWts The initialization type for the weights
 *  (Random, Zero).  
 *  @param initBias The initialization type for the biases
 *  (Random, Zero).
 *  @return Void. 
 */
void addLayer(NeuralNetwork *nn, int nodes, LayerType type, WeightInitType initWts);
/** @brief Frees the Neural Network from memory.
 * 
 *  @param nn A pointer to the Neural Network where 
 *  the layer would be attached to.
 *  @return Void. 
 */
void freeNeuralNet(NeuralNetwork *nn);