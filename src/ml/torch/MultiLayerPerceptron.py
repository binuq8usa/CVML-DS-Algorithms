import torch
import torch.nn as nn
import torch.nn.functional as F
import torch.optim as optim
from torch.utils.data import DataLoader, TensorDataset

from sklearn.datasets import load_digits
from sklearn.model_selection import train_test_split
import numpy as np
import math

# define a neural network
class SimpleNN(nn.Module):
    def __init__(self, input_size, hidden_size, output_size):
        super(SimpleNN, self).__init__()
        self.input_size = input_size
        self.hidden_size = hidden_size
        self.output_size = output_size
        self.fc1 = nn.Linear(self.input_size, self.hidden_size)
        self.activation = nn.Sigmoid()
        self.fc2 = nn.Linear(self.hidden_size, self.output_size)
        self.softmax = nn.Softmax()

        self.apply(self._init_weights)

    def _init_weights(self, module):
        if isinstance(module, nn.Linear):
            dim = module.weight.shape[1]
            limit = 1/ math.sqrt(dim)
            module.weight.data.uniform_(-limit, limit)
            if module.bias is not None:
                module.bias.data.uniform_(-limit, limit)

    def forward(self, x):
        x = self.fc1(x)
        x = self.activation(x)
        x = self.fc2(x)
        x = self.softmax(x)
        return x

def load_digits_dataset():
    data = load_digits()
    X = data.data
    target = data.target

    X_train, X_test, target_train, target_test = train_test_split(X,target, test_size = 0.2, random_state=123)
    X_train = np.float32(X_train)
    X_train = torch.tensor(X_train, requires_grad=True)
    #X_train = torch.from_numpy(np.float32(X_train))
    target_train = torch.from_numpy(target_train)

    X_test = torch.from_numpy(np.float32(X_test))
    target_test = torch.from_numpy(target_test)

    train_dataset = TensorDataset(X_train, target_train)
    test_dataset = TensorDataset(X_test, target_test)

    return train_dataset, test_dataset

def run_experiment():
    batch_size = 32
    learning_rate = 0.005
    num_epochs = 1000
    hidden_size = 16

    train_dataset, test_dataset = load_digits_dataset()

    train_loader = DataLoader(dataset=train_dataset, batch_size=batch_size, shuffle=True)
    test_loader = DataLoader(dataset=test_dataset, batch_size=1, shuffle=False)
    input_size = train_dataset[0][0].shape[0]
    set_of_labels = set()
    for idx, entry in enumerate(train_dataset):
        set_of_labels.add(entry[1].item())
    num_classes = len(set_of_labels)
    print(f'Number of classes : {num_classes}')
    output_size = num_classes

    model = SimpleNN(input_size=input_size, hidden_size=hidden_size, output_size=output_size)

    criterion = nn.CrossEntropyLoss()
    optimizer = optim.Adam(model.parameters(), lr=learning_rate)

    for epoch in range(0, num_epochs):
        for batch_id, (data, targets) in enumerate(train_loader):
            # forward pass
            outputs = model(data)
            loss = criterion(outputs, targets)

            # backward 
            optimizer.zero_grad() 
            loss.backward() # compute gradients
            optimizer.step()  # update wieghts\
            #optimizer.zero_grad()
        loss_test = 0.0
        num_test_samples = 0
        for id, (test_data,test_targets) in enumerate(test_loader):
            test_outputs = model(test_data)
            loss_test += criterion(test_outputs, test_targets).item()
            num_test_samples += 1
        loss_test /= num_test_samples
            
        print(f' Epoch {epoch} Loss : {loss_test:.4f}')


if __name__=="__main__":
    run_experiment()




# loss = nn.CrossEntropyLoss()
# input = torch.randn(3, 5, requires_grad=True)
# target = torch.empty(3, dtype=torch.long).random_(5)
# print(target)


