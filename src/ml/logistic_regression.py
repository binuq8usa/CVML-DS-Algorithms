
import numpy as np
import math

# helper fuunctions
def sigmoid(z):
    return 1 / (1 + np.exp(-z))

class LogisticRegression:
    def __init__(self, learning_rate = 0.01, num_epochs=10, batch_size = 8, num_input_dims = 4):
        self.learning_rate = learning_rate
        self.num_epochs = num_epochs
        self.batch_size = batch_size
        self.weights = np.random.random((num_input_dims,1))
        self.bias = np.random.random((1,1))
        self.grad_weights = np.ndarray
        self.grad_bias = np.ndarray

    def forward(self,x : np.ndarray): # X array of size M x D 
        # w * X + b 
        #print(f'X shape : {x.shape}')
        #print(f'weights shape : {self.weights.shape}')
         
        return sigmoid(x @ self.weights + self.bias) 

    def compute_loss(self,y_true, y_pred):
        m, n = y_true.shape
        return -(1/m) * np.sum(y_true * np.log(y_pred) + (1-y_true) * np.log(1-y_pred))

    # compute the gradients
    def backward(self, y_pred, y_true, x):
        diff = y_pred - y_true
        m,n = diff.shape
        self.grad_weights = (x.T @ diff)/m 
        self.grad_bias = np.mean(diff)

        # update the weights
        self.weights -= self.learning_rate * self.grad_weights
        self.bias -= self.learning_rate * self.grad_bias
        
    def train_loop(self, X, y):
        # divide into batches
        M = len(X)
        for batch_start in range(0,M,self.batch_size):
            batch_end = min(batch_start + self.batch_size, M)

            X_batch = X[batch_start:batch_end]
            y_batch = y[batch_start:batch_end]

            # forward the data
            y_pred_batch = self.forward(X_batch)

            # get the loss
            loss = self.compute_loss(y_true = y_batch, y_pred = y_pred_batch)
            #print(f'Batch loss : {loss}')

            # compute gradients and update wieghts
            self.backward(y_pred = y_pred_batch, y_true =y_batch, x = X_batch)          
        # compute the loss
        y_pred = self.forward(X)
        loss = self.compute_loss(y_true = y, y_pred = y_pred)
        return loss  
            

    def train(self, X,y):
        M = len(X)
        for epoch in range(0,self.num_epochs):
            indices = np.random.permutation(M)
            loss = self.train_loop(X[indices], y[indices])
            print(f'Loss : {loss}')


def test_case():
    M = 100
    D = 5
    num_epochs = 30
    learning_rate = 0.05
    batch_size = 16

    X = np.random.randn(M,D)
    y = np.random.randint(0,2,size=(M,1))

    model : LogisticRegression = LogisticRegression(num_epochs=num_epochs, batch_size=batch_size, learning_rate=learning_rate, num_input_dims=D)

    model.train(X,y)

test_case()