import numpy as np
"""
Give the following data where we want to predict the value of the house given that we have a a following set of features - 

four parameters

House square footage area
distance to nearest school
median neigbhorhood housing price sold in last 5 years
distance to closest highway

training data
Y = "House price" - $ amount Million - 0.5, 1 , 0.25 0.05, etc..

X1 = house sqare footagd (sq.metres)
X2 = distance to nearest school (miles)
X3 = Median neigbhorhood housing price $ 
X4 = Distance to closest highway (metres)


Model
"""

"""
Can start off with a linear regression Model

Y = beta_0 + beta_1 * x1 + ...beta_4 * x4

"""

class LinearRegression:
    def __init__(self, input_dims : int, output_dims: int, regularizer: float = 0.01, min_samples_for_iteration = 10, learning_rate = 0.0001, num_epochs = 10, batch_size = 4) -> None:
        self.input_dims = input_dims
        self.output_dims = output_dims
        self.model_params : np.ndarray  = np.random.random((self.input_dims,1))
        self.model_bias : np.ndarray = np.random.random((1,1))
        self.regularizer = regularizer
        self.min_samples_for_iteration = min_samples_for_iteration
        self.learning_rate = learning_rate
        self.num_epochs = num_epochs
        self.num_samples = 0
        self.batch_size = batch_size

    def transform(self, X):
        # (x - mean_x)/std(x)
        return (X - np.mean(X, axis=0))/np.std(X, axis=0)

    def forward(self, X):
        return X @ self.model_params + self.model_bias

    # compute gradient and update weights with regularization
    # since for stochastic descent - regularization for each sample - 1/2
    def backward(self, x_input, pred_output, true_output):
        # compute gradient w.r.t. to each weight
        # 2 * (y_pred - y_true) * x_j
        #print(f'x_input : {x_input} ')
        #print(f'pred_output size : {pred_output.shape} ')
        model_param_gradients = x_input.T @ (pred_output - true_output) + \
            self.regularizer * self.model_params
        model_param_gradients /= self.batch_size
        #print(f'Model params : {self.model_params}')
        #print(f'model gradients : {model_param_gradients}')
        model_bias_gradients = np.sum((pred_output - true_output)) + self.regularizer * self.model_bias
        model_bias_gradients /= self.batch_size
        
        # update weights
        self.model_params += self.learning_rate * model_param_gradients
        self.model_bias += self.learning_rate * model_bias_gradients
        #print(f'updated model parameters : {self.model_params}')
    
    def compute_loss(self, pred_output, true_output):
        loss = pred_output - true_output
        loss = (loss @ loss.T) 

        # compute regression loss 
        loss += self.regularizer * (self.model_params.T @ self.model_params + self.model_bias * self.model_bias)   

        return np.sum(loss)/2
    
    def train_loop(self, X: np.ndarray, Y: np.ndarray):
        print('Training iteratively')
        self.num_samples = X.shape[0]
        print(f'Number of samples : {self.num_samples}')
        # train sample by sample - stochastic gradient descent
        loss : float = float('inf')
        for sample_idx in range(0, self.num_samples,self.batch_size):
            x_train = X[sample_idx : sample_idx + self.batch_size,:] if sample_idx + self.batch_size < self.num_samples else X[sample_idx:]
            y_train = Y[sample_idx : sample_idx + self.batch_size,:] if sample_idx + self.batch_size < self.num_samples else Y[sample_idx:]
            #y_train = np.squeeze(y_train)
            #print(f'X train {x_train}')
            #print(f'y_train size {y_train}')

            y_pred = self.forward(x_train)
            #y_pred = np.squeeze(y_pred)
            #print(f'y_pred size : {y_pred}')
            
            # compute loss
            loss = self.compute_loss(pred_output=y_pred, true_output=y_train)

            #print(f'Loss : {loss}')
            # gradient descent
            self.backward(x_train, pred_output = y_pred, true_output = y_train)
        return loss

    def train(self, input : np.ndarray, true_output : np.ndarray):
        
        # closed form solution
        X = input 
        y = true_output
        M, N = X.shape
        self.num_samples = M
        assert N == self.input_dims
        assert y.shape[0] == X.shape[0] # number of observations are the same

        # closed form solution
        #X = self.transform(X)
        if M <= self.min_samples_for_iteration:
            self.model_params = np.linalg.inv(X.T @ X + self.regularizer) @ X.T @ y 
        else:
            # TODO: iterate through number of epochs or convergence
            for epoch in np.arange(0, self.num_epochs):
                # shuffle 
                indices = np.random.permutation(self.num_samples)
                loss = self.train_loop(X[indices], y[indices])
                print(f'Epoch Loss : {epoch} : {loss}')

def test_case():
    M = 200
    N = 4
    Y = np.random.rand(M,1)
    X = np.random.rand(M,N)
    
    model : LinearRegression = LinearRegression(input_dims=N, output_dims=1)
    model.train(input=X, true_output=Y) 

    # pred output
    #X_test = np.random.rand(M,4)
    Y_pred = model.forward(X)

    # compute losss
    # loss = model.compute_loss(pred_output=Y_pred, true_output=Y)

    # print(f'Loss : {loss}')

test_case()







    




