# https://mbernste.github.io/posts/gmm_em/

# Gaussian mixture models

# K number of gaussians, # D dimensions
import numpy as np
from sklearn.datasets import make_blobs

def initialize_parameters(data, D, K):
    # mu_k , covariance_k, pi_k (mixing cofficients)
    parameters = [] # tuple (pi_k, mu_k, covireance_k)
    for k in range(0,K):
        pi_k = 1/K
        sample_idx = np.random.choice(len(data),1)
        mu_k = np.squeeze(data[sample_idx])
        
        # select random 10 data points and initialize with that covariance
        sample_indices = np.random.choice(len(data),10)
        sample_pts = data[sample_indices]
        covar_k = np.cov(sample_pts.T)
        parameters.append((pi_k, mu_k, covar_k))
    return parameters

def compute_gaussian(xp, mu_k, covar_k):
    assert xp.shape[0] == mu_k.shape[0]
    D = mu_k.shape[0]
    assert covar_k.shape == (D,D)
    
    inv_covar = np.linalg.inv(covar_k)
    det_covar = np.linalg.det(covar_k)
    
    assert det_covar != 0

    val_1 = 1 / np.sqrt(2 * np.pi * det_covar)
    diff_vec = (xp - mu_k)
    val_2 = diff_vec.T @ inv_covar @ diff_vec
    val_2 = np.exp(-1 * val_2)
    return val_1 * val_2

def step_expection(data, parameters):
    
    K = len(parameters)
    N = len(data)
    weights = np.zeros((K,N))
    for idx, xp in enumerate(data):
        weights_per_xp = np.zeros((K,))
        for c_idx, (p_k, mu_k, covar_k) in enumerate(parameters):
            weights_per_xp[c_idx] = p_k * compute_gaussian(xp, mu_k, covar_k)
        weights_per_xp /= np.sum(weights_per_xp)
        weights[:, idx] = weights_per_xp.T
    
    return weights

def step_maximization(weights, data):
    parameters = []
    N = len(data)
    for idx, cluster_weights in enumerate(weights):
        sum_weights_per_cluster = np.sum(cluster_weights)
        p_k = 1/N * sum_weights_per_cluster
        mu_k = 1/(sum_weights_per_cluster)  * np.sum((np.expand_dims(cluster_weights,1) * data), axis=0)
        mu_k = np.expand_dims(mu_k,1)
        covar_k = np.zeros((len(mu_k), len(mu_k)))
        for p_idx, xp in enumerate(data):
            xp = np.expand_dims(xp,0)
            covar_k += cluster_weights[p_idx] * (xp - mu_k) @ (xp - mu_k).T
        covar_k /= sum_weights_per_cluster
        
        #covar_k = 1/sum_weights_per_cluster * np.sum( (np.expand_dims(cluster_weights,1)) * ((data - mu_k).T @ (data-mu_k)), axis=0)
        
        parameters.append((p_k, np.squeeze(mu_k), covar_k))
    return parameters    
     
def gmm(data, K):
    # initialize parameters
    parameters = initialize_parameters(data, len(data), K)
    num_iterations = 0
    while num_iterations < 20:
        weights = step_expection(data, parameters)
        parameters = step_maximization(weights, data)
        num_iterations += 1
        print(f'Parameters : {parameters}')
        
def test_case():
    data, true_labels = make_blobs()
    
    gmm(data, K=2)
    
if __name__=="__main__":
    test_case()
    