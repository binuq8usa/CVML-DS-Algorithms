"""
Implement a plane fitting algorithm based on RANSAC

https://math.stackexchange.com/questions/99299/best-fitting-plane-given-a-set-of-points
https://math.stackexchange.com/questions/3869/what-is-the-intuitive-relationship-between-svd-and-pca/3871#3871
https://arxiv.org/pdf/1404.1100


"""
import numpy as np

"""
Algorithm
Initialize J* <- infinity
1. Take m sample points from N points
2. Estimate model or parameters from m sample points (plane equation or )
    w1 * x1 + w2 *x2 + w3 * x3 + w4 = 0; 
3. Compute the cost function from all the points from the estimated model
    J = sum_allpoints (F(x,theta)) ; F(x,theta) = 0 if dist(x, theta) <= threshold, 1 otherwise
    J = # outliers, outlier ratio =
4. if J < J*: J <- J*, theta* <- theta
5. repeat until convergence, F(X, J*) <= eta (confidence measure)
6. With theta*, get all the inliers => 
    


"""

class RANSACPlaneFitter:
    def __init__(self, distance_threshold = 0.01, ransac_n = 3, num_iterations = 100, 
                 probability = 0.99):
        self.distance_threshold = distance_threshold
        self.ransac_n = ransac_n # minimum number of inlier points to be considered as a valid plane
        self.num_iterations = num_iterations
        self.probability = probability
    
    def fit(X : np.ndarray):
        plane_params = np.zeros((4,1))    
        
        
        
        return plane_params
                
