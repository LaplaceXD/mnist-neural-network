/** @file neural_net.c
 *  @brief A library made for working with neural networks.
 *  This has a dependency to matrix.c library.
 * 
 *  This library contains various functions which allows
 *  users to create neural networks. It also has functions
 *  for creating, deleting, and inserting layers. 
 *  
 *  DEPENDENCIES: matrix, doubly_ll
 * 
 *  @author Jonh Alexis Buot (LaplaceXD)
 *  @bug No know bugs.
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "headers/matrix.h"
#include "headers/doubly_ll.h"
#include "headers/neural_net.h"

#define throwInvalidArgs(arg, msg) { fprintf(stderr, "Invalid %s Argument. %s", arg, msg); exit(1); }
#define throwMallocFailed() { fprintf(stderr, "Memory Allocation Failed."); exit(1); }
#define SHOULD_BE_POSITIVE "It should be a positive integer."
#define SHOULD_BE_NON_NEGATIVE "It should be a non-negative integer."
#define INVALID_NEURAL_NET_OPT "Neural Network Options contain invalid values."

NeuralNetwork createNeuralNet(NeuralNetOpt opt, LayerDesign layers[], int size)
{
    if(!isValidNeuralNetOpt(opt)) throwInvalidArgs("opt", INVALID_NEURAL_NET_OPT);
    if(size < 0) throwInvalidArgs("size", SHOULD_BE_POSITIVE);
    
    int idx;
    NeuralNetwork nn = { 
        .options = opt,
        .layers = createList()
    };
    
    if(layers != NULL) {
        for(idx = 0; idx < size; idx++) {
            addLayer(&nn, layers[idx].nodes, layers[idx].type);
        }
    }

    return nn; 
}

Matrix createEmptyWeights(int nodes, int prevNodes, NeuralNetOpt opt)
{
    if(!isValidNeuralNetOpt(opt)) throwInvalidArgs("opt", INVALID_NEURAL_NET_OPT);
    
    int row, col;

    row = opt.nodeOrient == COL ? nodes : prevNodes;
    col = opt.nodeOrient == COL ? prevNodes : prevNodes;
    return createMatrix(row, col);
}

Matrix createEmptyBias(int nodes, NeuralNetOpt opt)
{
    if(!isValidNeuralNetOpt(opt)) throwInvalidArgs("opt", INVALID_NEURAL_NET_OPT);

    int row, col;

    row = opt.nodeOrient == COL ? nodes: 1;
    col = opt.nodeOrient == COL ? 1 : nodes;
    return createMatrix(row, col);
}

void activateWeights(Matrix wts, NeuralNetOpt opt)
{
    if(!isValidNeuralNetOpt(opt)) throwInvalidArgs("opt", INVALID_NEURAL_NET_OPT);

    double mult, bounds;
    int currNodes, prevNodes;

    currNodes = opt.nodeOrient == COL ? wts.row : wts.col;
    prevNodes = opt.nodeOrient == COL ? wts.col : wts.row;

    switch(opt.distStrat) {
        case HE:
            mult = sqrt(2.0 / currNodes);
            break;
        case HE_XAVIER:
            mult = sqrt(2.0 / (currNodes + prevNodes));
            break;
        case XAVIER:
            mult = sqrt(2.0 / prevNodes);
            break;
        case RANDOM:
            mult = 1;
            break;
        case ZERO:
            fillMatrix(wts, 0);
            break;
        default:
            throwInvalidArgs("distStrat", "");
    }

    if(opt.distStrat != ZERO) {
        bounds = opt.distSize / sqrt(wts.row * wts.col);
        fillMatrixRandn(wts, -1 * bounds, bounds, mult);
    }
}

void activateLayer(Layer *layer, int prevNodes, NeuralNetOpt opt)
{
    if(!isValidNeuralNetOpt(opt)) throwInvalidArgs("opt", INVALID_NEURAL_NET_OPT);

    if(prevNodes < 0) {
        throwInvalidArgs("prevNodes", SHOULD_BE_NON_NEGATIVE);
    } else if(prevNodes == 0) {
        layer->weights = createZeroMatrix();
        layer->bias = createZeroMatrix();
    } else {
        layer->weights = createEmptyWeights(layer->nodes, prevNodes, opt);
        activateWeights(layer->weights, opt);
        
        layer->bias = createEmptyBias(layer->nodes, opt);
        fillMatrix(layer->bias, opt.initialBias); // activate bias
    }
}

void reactivateLayer(Layer *layer, int prevNodes, NeuralNetOpt opt)
{
    if(prevNodes < 0) throwInvalidArgs("prevNodes", SHOULD_BE_NON_NEGATIVE);
    if(!isValidNeuralNetOpt(opt)) throwInvalidArgs("opt", INVALID_NEURAL_NET_OPT);
    
    freeMatrix(&layer->weights);
    freeMatrix(&layer->bias);
    activateLayer(layer, prevNodes, opt);
}

Layer *createLayer(int nodes, int pos, LayerType type, NeuralNetwork nn)
{
    if(nodes <= 0) throwInvalidArgs("nodes", SHOULD_BE_POSITIVE)
    if(pos <= 0) throwInvalidArgs("pos", SHOULD_BE_NON_NEGATIVE);
    if(type != INPUT && type != HIDDEN && type != OUTPUT) throwInvalidArgs("type", ""); 

    Layer *layer; 
    int prevNodes;

    layer = (Layer *) malloc(sizeof(Layer));
    if(layer == NULL) throwMallocFailed();
    
    layer->nodes = nodes;
    layer->type = type;
    prevNodes = pos == 1 ? 0 : getLayer(nn, pos).nodes;
    activateLayer(layer, prevNodes, nn.options);

    return layer;
}

void addLayer(NeuralNetwork *nn, int nodes, LayerType type)
{
    if(nodes <= 0) throwInvalidArgs("nodes", SHOULD_BE_POSITIVE);
    if(type != INPUT && type != HIDDEN && type != OUTPUT) throwInvalidArgs("type", "");

    Layer *layer = createLayer(nodes, nn->layers.size + 1, type, *nn);
    addToList(&nn->layers, layer); 
}

void insertLayer(NeuralNetwork *nn, int pos, int nodes, LayerType type)
{
    if(nodes <= 0) throwInvalidArgs("nodes", SHOULD_BE_POSITIVE);
    if(pos <= 0) throwInvalidArgs("pos", SHOULD_BE_POSITIVE);
    if(pos > nn->layers.size + 1) throwInvalidArgs("pos", "It should be lesser than or equal to the network size plus one.");
    if(type != INPUT && type != HIDDEN && type != OUTPUT) throwInvalidArgs("type", ""); 
    
    Layer *curr, *next;

    curr = createLayer(nodes, pos, type, *nn);
    insertToList(&nn->layers, pos - 1, curr);

    // Reinitialize succeeding layer
    if(pos < nn->layers.size) {
        next = (Layer *) getItemByIndex(nn->layers, pos);
        reactivateLayer(next, curr->nodes, nn->options);
    }
}

Layer *travNeuralNet(NeuralNetwork *nn, TravDirection dir)
{
    if(dir != FORWARD && dir != BACKWARD) throwInvalidArgs("dir", "");

    NavDirection nav = dir == FORWARD ? NEXT : PREV;
    DoublyLinkedList *ll = nn == NULL ? NULL : &nn->layers;  
    return (Layer *) getItem(ll, nav);
}

Layer getLayer(NeuralNetwork nn, int pos)
{
    if(pos <= 0) throwInvalidArgs("pos", SHOULD_BE_POSITIVE);
    if(pos > nn.layers.size) throwInvalidArgs("pos", "It should not be bigger than the layer size.");

    return *(Layer *) getItemByIndex(nn.layers, pos - 1);
}

void freeLayer(void *item) 
{
    Layer *layer = (Layer *) item;

    layer->type = INPUT;
    layer->nodes = 0;
    freeMatrix(&layer->weights);
    freeMatrix(&layer->bias);
    free(layer);
}

void deleteLayer(NeuralNetwork *nn, int pos)
{
    if(pos <= 0) throwInvalidArgs("pos", SHOULD_BE_POSITIVE);
    if(pos > nn->layers.size) throwInvalidArgs("pos", "It should not be bigger than the network size.");

    int prevNodes;
    Layer *curr;

    deleteFromList(&nn->layers, pos - 1, freeLayer);
    
    // Reinitialize previously succeeding layer
    if(pos <= nn->layers.size) {
        curr = (Layer *) getItemByIndex(nn->layers, pos);
        prevNodes = pos == 1 ? 0 : getLayer(*nn, pos - 1).nodes;
        reactivateLayer(curr, prevNodes, nn->options);
    }
}

void freeNeuralNet(NeuralNetwork *nn)
{
    clearList(&nn->layers, freeLayer);
    nn->options.distSize = 0;
    nn->options.distStrat = ZERO;
    nn->options.initialBias = 0;
}

int isValidNeuralNetOpt(NeuralNetOpt opt)
{
    DistStrategy type = opt.distStrat;
    int hasValidDistStrat = type == HE 
        || type == HE_XAVIER 
        || type == ZERO 
        || type == RANDOM 
        || type == XAVIER;

    int hasValidOrientation = opt.nodeOrient == ROW
        || opt.nodeOrient == COL;

    int hasValidDistSize = opt.distSize >= 0;
    int hasValidLR = opt.lr >= 0;

    return hasValidDistSize 
        && hasValidDistStrat 
        && hasValidOrientation
        && hasValidLR ? 1 : 0;
}