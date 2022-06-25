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
typedef enum DistStrategy { RANDOM, ZERO, HE, XAVIER, HE_XAVIER } DistStrategy;
/** @brief The different layer types. */
typedef enum LayerType { INPUT, HIDDEN, OUTPUT } LayerType;
/** @brief The different possible direction of traversing a Neural Network. */
typedef enum TravDirection { FORWARD, BACKWARD } TravDirection;
/** @brief Specifies the orientation of the nodes in the Neural Network.
 *  Row nodes lets the dataset take up less space and calculations becomes more performant.
 *  Column nodes are more semantic, and in-line with visualizations in the Internet.
 */
typedef MatrixAxis NodeOrientation;

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
    // The orientation of the nodes in the neural netowrk.
    NodeOrientation nodeOrient;
    // The distribution strategy to be used for intializing
    // the weights.
    DistStrategy distStrat;
    // The size of the distribution.
    double distSize;
    // The initial value for the biases of the layers.
    double initialBias;
    // The learning rate of the neural network.
    double lr;
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
NeuralNetwork createNeuralNet(NeuralNetOpt opt, LayerDesign layers[], int size);
/** @brief Appends a layer to the Neural Network.
 *  
 *  @param nn A pointer to the Neural Network where 
 *  the layer would be attached to.
 *  @param nodes The number of nodes the layer should have.
 *  @param type The type of the layer.
 *  @return Void.
 */
void addLayer(NeuralNetwork *nn, int nodes, LayerType type);
/** @brief Removes a layer from the Neural Network,
 *  based on a given position.
 * 
 *  @param nn A pointer to the Neural Network where 
 *  the layer would be attached to.
 *  @param pos The position of the layer in the
 *  Neural Network (starting at 1).
 *  @param nodes The number of nodes the layer should have.
 *  @param type The type of the layer.
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
/** @brief Traverses a neural network in a given direction
 *  while returning the layer contained in each traversal.
 * 
 *  Only the first call of this function should the pointer to 
 *  the Neural Network be passed. Succeeding calls should have
 *  a NULL passed to nn, since it would reset the traversal back
 *  to the start. 
 * 
 *  @example
 *  travNeuralNet(&nn, FORWARD);
 *  travNeuralNet(&nn, BACKWARD); 
 *  
 *  @param nn A pointer to the Neural Network to be traversed. 
 *  @param dir The direction of traversal. 
 *  @return A pointer to the layer contained in the current 
 *  position of the traversal, else NULL is returned
 */
Layer *travNeuralNet(NeuralNetwork *nn, TravDirection dir);
/** @brief Gets the layer of a Neural Network on a given position.
 * 
 *  @param nn The Neural Network where the layer is a part of.
 *  @param pos The position of the layer in the Neural Network 
 *  (starting at 1).
 *  @return The layer. 
 */
Layer getLayer(NeuralNetwork nn, int pos);
/** @brief Frees the Neural Network from memory.
 * 
 *  @param nn A pointer to the Neural Network to be freed. 
 *  @return Void. 
 */
void freeNeuralNet(NeuralNetwork *nn);
/** @brief Checks if the passed neural net options contains
 *  valid values.
 * 
 *  @param opt The options to be checked. 
 *  @return 1 - If the options are valid.
 *  0 - If it is not. 
 */
int isValidNeuralNetOpt(NeuralNetOpt opt);