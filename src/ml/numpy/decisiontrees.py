"""Sample file"""
# https://www.kaggle.com/code/fareselmenshawii/decision-tree-from-scratch

import math
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns 
import plotly.express as px 
import pprint
from enum import IntEnum

from sklearn.model_selection import train_test_split
from typing import Optional

class Node:
    """
    Class representing a tree node
    
    
    """
    def __init__(self, feature_idx = None, threshold = None, left = None, right = None, gain=None, 
                 value=None, indices=None):
        self.feature_idx = feature_idx
        self.threshold = threshold
        self.left = left 
        self.right = right
        self.gain = gain # information gain
        self.value = value
        self.indices = indices # indices entering into the node
        
class DecisionTreeType(IntEnum):
    CLASSIFICATION = 0
    REGRESSION = 1
    
class DecisionTree:
    def __init__(self, min_num_samples, max_depth_tree, dataset = None, type : DecisionTreeType = DecisionTreeType.CLASSIFICATION):
        self._min_num_samples = min_num_samples
        self._max_depth_tree = max_depth_tree
        self._dataset = dataset # dataset currently in numpy form but later we can use some sort PyTorch dataset containing entries to pulled from a server 
        self._type = type
        self._root : Optional[Node] = None
    
    @property
    def dataset(self):
        return self._dataset
    
    @dataset.setter
    def dataset(self,dataset):
        self._dataset = dataset
        
    def feature(self, index):
        return self._dataset[index]
    
    @property
    def min_samples(self):
        return self._min_num_samples
    
    @property
    def max_depth_tree(self):
        return self._max_depth_tree

    @property
    def type(self):
        return self._type

    @property
    def root(self):
        return self._root
    
    @root.setter
    def root(self, node: Node):
        self._root = node
        
    def split_node(self, node : Node):
        """
        Datasets is N x (D+1) where first D columns are the features and last column is the label
        
        The split will be based on input_features[feature_idx] < threshold
        
        The 

        Args:
            data (_type_): _description_
            feature (_type_): _description_
            threshold (_type_): _description_
        """
        
        left_indices = np.array([index for index in node.indices if self.feature(index)[node.feature_idx] <= node.threshold])
        right_indices = np.array([index for index in node.indices if self.feature(index)[node.feature_idx] > node.threshold])
    
        return Node(indices=left_indices), Node(indices=right_indices)
    
    def entropy_of_node(self, node: Node):
        if self.type == DecisionTreeType.CLASSIFICATION:
            # get the labels 
            y = np.array([self.feature(index)[-1] for index in node.indices])
            labels = np.unique(y)
            
            prob_vals = np.array([ len(y[y==label])/len(y) for label in labels])
            return np.sum(-prob_vals * np.log2(prob_vals))
        else:
            return 0
    
    def information_gain(self, parent : Node, left_child : Node, right_child : Node):
        """
        
        Computes the information gain as entrory(parent) - weighted entropy of children

        Args:
            node (Node): _description_
        """
        info_gain = 0
        if self.type == DecisionTreeType.CLASSIFICATION:
            w_left = len(left_child.indices)/len(parent.indices)
            w_right = len(right_child.indices)/len(parent.indices)
            info_gain = self.entropy_of_node(parent) - w_left * self.entropy_of_node(left_child)- w_right * self.entropy_of_node(right_child)
        else:
            # for regression, need to implement the variance
            info_gain = 0
        return info_gain
    
    def get_best_split(self, node : Node):
        # find the best split for the node containing the indices
        best_split = {'gain' : None, 'feature_idx' : None, 'threshold' : None, 'left': None, 'right': None}
        num_samples = len(node.indices)
        num_features = len(self.feature(node.indices[0]))-1 # remove the last node which is the class
        
        # iterate across feature_idx
        for feature_idx in range(num_features):
            feature_values = [self.feature(index)[feature_idx] for index in node.indices]
            set_of_thresholds = np.unique(feature_values)
            
            for threshold in set_of_thresholds:
                # create a node
                node.feature_idx = feature_idx
                node.threshold = threshold
                left_node, right_node = self.split_node(node) 
                
                # compute the information gain
                info_gain = self.information_gain(parent=node, left_child=left_node, right_child = right_node)
                
                if best_split['gain'] is None or info_gain > best_split['gain']:
                    best_split['gain'] = info_gain
                    best_split['feature_idx'] = feature_idx
                    best_split['threshold'] = threshold
                    best_split['left'] = left_node
                    best_split['right'] = right_node
        
        return best_split

    def calculate_leaf_value(self, node):
        y = [self.feature(index)[-1] for index in node.indices]
        from collections import Counter
        c = Counter(y)
        return c.most_common()[0][0]
    
    # all of same class. Then entropy is zero which gives true
    def is_node_pure(self, node):
        return (self.entropy_of_node(node) == 0.0)
    
    # inorder traversal
    def build_tree(self, node: Node, current_depth = 0):
        """
        Recursively build the tree
        

        Args:
            node (Node): _description_
            current_depth (int, optional): _description_. Defaults to 0.
        """
        num_samples = len(node.indices)
        print(f'Tree at {node} in depth {current_depth}')
        
        if num_samples >= self.min_samples and current_depth <= self.max_depth_tree and not self.is_node_pure(node):
            # get the best split # visiting the parent node
            best_split = self.get_best_split(node)
            if best_split['gain']:
                # level order traversal - build left part of three
                left_node = self.build_tree(best_split['left'], current_depth=current_depth+1)
                right_node = self.build_tree(best_split['right'], current_depth=current_depth+1)
                return Node(feature_idx=best_split['feature_idx'],threshold=best_split['threshold'],left=left_node, right=right_node, gain = best_split['gain'],indices=node.indices)
        
        # compute leaf nodes
        leaf_value = self.calculate_leaf_value(node)
        return Node(value=leaf_value)
    
    def fit(self, X,y):
        dataset = np.concatenate((X,y),axis=1)
        self.dataset = dataset
        
        self.root = Node(indices=list(range(0,len(dataset))))
        print('Building tree')
        self.root = self.build_tree(node = self.root)
        
        
    def predict(self, X):
        return np.array([self.make_prediction(x,self.root) for x in X ])
    
    def make_prediction(self, x, node: Node):
        if node.value != None:
            return node.value
        elif x[node.feature_idx] <= node.threshold:
            return self.make_prediction(x, node.left)
        else:
            return self.make_prediction(x, node.right)

def get_cancer_dataset(csv_filename):
    df = pd.read_csv(csv_filename)
    df.drop('id',axis=1, inplace=True)
    # check correlation with target
    df['diagnosis'] = (df['diagnosis'] == 'M').astype(int) # M- 1, B - 0
    # compute the correlation
    corr = df.corr()
    
    # perform feature selection based on correlation
    corr_target = abs(corr['diagnosis'])

    # select high correlated featres
    threshold = 0.5
    relevant_features = corr_target[corr_target > threshold]

    # get the names of the features
    # print(relevant_features)
    names = [name for name, value in relevant_features.iteritems()]
    names.remove('diagnosis')
    X = df[names].values
    y = df['diagnosis'].values.reshape(-1,1) # N x 1 labels
    print('Read dataset')
    
    return X,y

def test_decision_tree():
    filename = '/Users/binun/Documents/GitHub/CVML-DS-Algorithms/test_data/data.csv'
    X,y = get_cancer_dataset(filename)
    
    X_train, X_test, y_train, y_test = train_test_split(X,y)
    
    # create the decision tree
    decision_tree : DecisionTree = DecisionTree(min_num_samples=2, max_depth_tree=3)
    
    decision_tree.fit(X_train, y_train)
    
    # make predictions
    y_pred = decision_tree.predict(X_test)
    print(f'Y_predictions : {y_pred}')
    
if __name__=="__main__":
    test_decision_tree()

    
    
        
        
        
        
    
    
    
    
    