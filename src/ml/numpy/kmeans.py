import numpy as np
from sklearn.datasets import make_blobs
import matplotlib.pyplot as plt
import seaborn as sns

"""

1. Set K and initialize Mk clusters mean
2. Assign each point xp to mK clusters based on minmum euclidean distance
3. Recompute the cluster mean.
4. Check difference between Mk-1 cluster means and current clusters. If small value, convergenec and exit loop

"""

def dist_metric(x1, x2):
    return np.linalg.norm(x1-x2)

def compute_clusters(data, cluster_centers):
    #assign clusters
    N,D = data.shape
    cluster_labels = np.zeros((N,))
    # assign the clusters - E step
    for idx, xp in enumerate(data):
        dists_from_xp = np.array([ dist_metric(xp, cluster_center) for idx, cluster_center in enumerate(cluster_centers) ])
        cluster_labels[idx] = np.argmin(dists_from_xp)

    # recompute the clusters - M Step
    err = 0
    for cluster_id, cluster_center in enumerate(cluster_centers):
        xp = data[cluster_labels==cluster_id]
        if xp.size == 0:
            continue
        new_cluster_center = np.mean(xp, axis=0)
        err += dist_metric(cluster_center, new_cluster_center)
        cluster_centers[cluster_id] = new_cluster_center
    err /= (len(cluster_centers) + 1e-10)

    # compute the distortion within each cluster
    dist_coeff = 0.0
    for cluster_idx, cluster_center in enumerate(cluster_centers):
        xp = data[cluster_labels == cluster_id]
        if xp.size == 0:
            continue
        dist_from_xp_to_center = np.array([ dist_metric(x,cluster_center) for x in xp ])
        dist_coeff += np.std(dist_from_xp_to_center)
    dist_coeff /= len(cluster_centers)

    return err, dist_coeff, cluster_centers, cluster_labels
    

def kMeans(data : np.ndarray, K): # N x D points ; K - number of clusters
    # generate initialial clusters - D dimensional - K x D    
    min_val = np.min(data)
    max_val = np.max(data) 
    N, D = data.shape
    cluster_centers = (max_val - min_val) * np.random.random((K,D)) + min_val
    cluster_labels = np.zeros((N, 1)) # takes value from 0 to K-1

    err_val = float('inf')
    num_iterations = 0
    while True:
        num_iterations += 1
        err_val, dist_coeff, cluster_centers, cluster_labels = compute_clusters(data, cluster_centers)
        print(f'Cluster centers diff : {err_val:.4f}')
        if err_val < 1e-2 or num_iterations > 100:
            break
    return dist_coeff, cluster_centers, cluster_labels

def test_case():
    data, true_labels = make_blobs()
    print(data)
    print(true_labels)

    # plt.figure()
    # plt.scatter(data[:,0], data[:,1])
    
    dists = []
    max_K = 5
    for K in range(1,max_K):
        dist_coeff, cluster_centers, cluster_labels = kMeans(data, K)
        dists.append(dist_coeff)
        for cluster_idx,cluster_center in enumerate(cluster_centers):
            if len(data[cluster_labels == cluster_idx]) == 0:
                continue
        #     plt.scatter(cluster_center[0], cluster_center[1], marker='*', color='red') 
        # plt.show()

    plt.figure()
    sns.set_style("whitegrid")
    g=sns.lineplot(x=range(1,max_K), y=dists)

    g.set(xlabel ="Number of cluster (k)", 
      ylabel = "Sum Squared Error", 
      title ='Elbow Method')
    plt.show()

    #print(cluster_centers)
    #print(cluster_labels)


if __name__ == "__main__":
    test_case() 