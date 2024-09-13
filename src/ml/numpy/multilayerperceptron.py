"""
Reference : https://github.com/rcalix1/MachineLearningFoundations/blob/main/NeuralNets/multiLayerPerceptron.py

"""

import numpy as np
import math
from collections import defaultdict
from typing import Dict, List

from sklearn import datasets
from sklearn.model_selection import train_test_split

class Sigmoid:
    def __call__(self, x):
        return 1 / (1 + np.exp(-x))
    
    def gradient(self, x):
        return self.__call__(x) * (1 - self.__call__(x))

class Softmax:
    def __call__(self,x):
        norm_factor = np.max(x, axis=1, keepdims=True)
        shifted_x = x - norm_factor
        return np.exp(shifted_x) / np.sum(np.exp(shifted_x), axis=1, keepdims=True)
    
    def gradient(self, x):
        prob_val = self.__call__(x)
        # actual gradient is Si ( delta_ij - S_j)
        # won't this be in matrix terms - S * (I - S)
        return prob_val * ( 1- prob_val)

class AdamOptimizer:
    def __init__(self,beta_1 = 0.9, beta_2 = 0.99, learning_rate = 0.01) -> None:
        self.beta_1 = beta_1
        self.beta_2 = beta_2
        self.learning_rate = learning_rate

    def initialize(self,parameters : Dict[str,List]):
        self.Vd = defaultdict(list).fromkeys(parameters.keys(), np.array([]))
        self.Sd = defaultdict(list).fromkeys(parameters.keys(), np.array([]))

    def optimize(self,parameters, grad_parameters):
        assert (list(parameters.keys()) == list(grad_parameters.keys()))
        for key in parameters.keys():
            # update Vd and Sd
            self.Vd[key] = grad_parameters[key] if self.Vd[key].size == 0  \
                else self.beta_1 * self.Vd[key] + (1 - self.beta_1) * grad_parameters[key]
            temp = grad_parameters[key] * grad_parameters[key]
            self.Sd[key] = temp if self.Sd[key].size == 0 else self.beta_2 * self.Sd[key] + (1 - self.beta_2) * temp
            parameters[key] -= self.learning_rate * self.Vd[key] / np.sqrt(self.Sd[key] + 1e-10)         
        return parameters

    
# its one hot encoding - not a single value taking multiple values
class CrossEntropyLoss:
    def __init__(self):
        pass

    def loss(self, Y_true, Y_pred):
        Y_pred = np.clip(Y_pred, 1e-15 , 1 - 1e-15) # clipping so thats its not zero
        value = np.sum( -Y_true * np.log(Y_pred) - (1-Y_true) * np.log(1-Y_pred) , axis=1, keepdims=True)
        return 1 / Y_pred.shape[0] * np.sum(value, axis=0, keepdims=True)
    
    def acc(self, Y_true, Y_pred):
        pass

    def gradient(self, Y_true, Y_pred):
        Y_pred = np.clip(Y_pred, 1e-15, 1 - 1e-15)
        value = - Y_true/Y_pred + (1 - Y_true) / (1-Y_pred)
        return value
    
def one_hot_encoding(y_labels): # M labels
    list_labels = list(set(y_labels))
    label_dict = { label : idx for idx,label in enumerate(list_labels) }
    num_labels = len(list_labels)
    N = len(y_labels)
    encoded_matrix = np.zeros((N,num_labels))
    for idx,label in enumerate(y_labels):
        encoded_matrix[idx][label_dict[label]] = 1
    
    return encoded_matrix

class MultiLayerPerceptron:
    def __init__(self, num_inputs, num_hidden_nodes, num_outputs, \
                 learning_rate = 0.01, beta_1 = 0.9, beta_2 = 0.99, num_epochs = 100, \
                    batch_size=16) -> None:
        self.num_inputs = num_inputs
        self.num_hidden_nodes = num_hidden_nodes
        self.num_outputs = num_outputs
        self.learning_rate = learning_rate
        self.beta_1 = beta_1
        self.beta_2 = beta_2
        self.hidden_activation = Sigmoid()
        self.output_activation = Softmax()
        self.loss = CrossEntropyLoss()
        self.hidden_input = np.array([])
        self.hidden_output = np.array([])
        self.output_layer_input = np.array([])
        self.num_epochs = num_epochs
        self.batch_size = batch_size
        self.optimizer = AdamOptimizer(beta_1=beta_1, beta_2=beta_2, learning_rate=learning_rate)

    def initialize_weights(self):
        limit = 1/ math.sqrt(self.num_inputs)
        W1 = np.random.uniform(-limit, limit, (self.num_inputs, self.num_hidden_nodes))
        b1 = np.random.uniform(-limit, limit, (1,self.num_hidden_nodes))
        grad_W1 = np.zeros((self.num_inputs, self.num_hidden_nodes)) 
        grad_b1 = np.zeros((1,self.num_hidden_nodes))

        limit = 1/ math.sqrt(self.num_hidden_nodes)
        W2 = np.random.uniform(-limit, limit, (self.num_hidden_nodes, self.num_outputs))
        b2 = np.random.uniform(-limit, limit, (1,self.num_outputs))
        grad_W2 = np.zeros((self.num_hidden_nodes, self.num_outputs)) 
        grad_b2 = np.zeros((1,self.num_outputs))

        # initialize the AdamOptimizer
        self.parameters = {'W1' : W1, 'W2' : W2, 'b1' : b1, 'b2' : b2}
        self.grad_parameters = {'W1' : grad_W1, 'W2': grad_W2, 'b1' : grad_b1, 'b2' : grad_b2}
        self.optimizer.initialize(self.parameters)

    def forward(self, X):
        # X - N x D
        X = X @ self.parameters['W1'] + self.parameters['b1']
        self.hidden_input = np.copy(X)
        
        X = self.hidden_activation(X)
        self.hidden_output = np.copy(X)
        # store these batch inputs for gradient computation later

        X = X @ self.parameters['W2'] + self.parameters['b2']
        self.output_layer_input = np.copy(X)
        Y = self.output_activation(X)

        return Y # N x num_of_classes/outputs

    # to backpropagate and compute gradients
    def backward(self, X, Y_pred, Y_true):
        # backprogate and compute gradients
        grad_w_output_layer_input = self.loss.gradient(Y_pred=Y_pred, Y_true=Y_true) * \
            self.output_activation.gradient(self.output_layer_input)
        self.grad_parameters['W2']  = self.hidden_output.T @ grad_w_output_layer_input
        self.grad_parameters['b2'] = np.sum(grad_w_output_layer_input, axis=0, keepdims=True)
        
        # hidden layer
        grad_w_hidden_layer_input = grad_w_output_layer_input @ self.parameters['W2'].T
        grad_w_hidden_layer_input *= self.hidden_activation.gradient(self.hidden_input)
        self.grad_parameters['W1'] = X.T @ grad_w_hidden_layer_input
        self.grad_parameters['b1'] = np.sum(grad_w_hidden_layer_input, axis=0, keepdims=True)

        # update the weights - 
        self.parameters = self.optimizer.optimize(self.parameters, self.grad_parameters)

    def train_loop(self, X,Y):
        for batch_start in range(0, len(X), self.batch_size):
            batch_end = min(batch_start + self.batch_size, len(X))

            X_batch = X[batch_start:batch_end, : ]
            Y_batch = Y[batch_start:batch_end, : ]

            # forward the 
            Y_pred_batch = self.forward(X_batch)

            # compute loss
            error = self.loss.loss(Y_true = Y_batch, Y_pred = Y_pred_batch)

            # backward and update gradients
            self.backward(X_batch, Y_true=Y_batch, Y_pred=Y_pred_batch)
        # compute the error
        Y_pred = self.forward(X)
        error = self.loss.loss(Y_true=Y, Y_pred=Y_pred)
        return error
            
    def fit(self,X,Y):
        self.initialize_weights()
        # create one-hot encoding
        for epoch in range(0, self.num_epochs):
            indices = np.random.permutation(len(X))
            loss = self.train_loop(X[indices], Y[indices])
            print(f'Epoch {epoch} Loss : {loss})')

def test_digits():
    print(f'Entering test function and loading data')
    data = datasets.load_digits()
    X = data.data
    N,D = X.shape
    print(f'Shape of X : {X.shape}')
    labels = data.target
    print(f'Shape of labels : {labels}')
    Y = one_hot_encoding(labels)
    N1, K = Y.shape
    print(f'Shape of Y : {Y.shape}')


    assert N == N1

    model : MultiLayerPerceptron = MultiLayerPerceptron(num_inputs=D, 
                                                        num_hidden_nodes=16, num_outputs=K)
    
    X_train, X_test, Y_train, Y_test = train_test_split(X,Y,test_size = 0.2, random_state = 123)
    
    model.fit(X_train,Y_train)

test_digits()



