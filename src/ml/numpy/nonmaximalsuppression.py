"""
Implement Non maxima suppression for bounding boxes

1. List of elements - N x 5 = [x_min, x_max, y_min, y_max, confidence]
2. iterattively compare between vectors - compute IoU 
3. Sort these in highest confidence order
4. Start with first vector, compare with every other element to see if there is match. If it is, reject the entry or remove from list
5. Repeat 

1. retained_indices = range()

                               xp1     xp2
              xc1        xc2

"""
import numpy as np
from typing import List

FEATURE_SIZE=4 # (x, y, w,h)
IOU_THRESHOLD=0.5

def iouOverlap(feat_p, feat_c) :
    xp1, yp1, xp2, yp2 = feat_p 
    xc1, yc1, xc2, yc2 = feat_c 

    total_area_p = (xp2 - xp1) * (yp2 - yp1)
    total_area_c = (xc2 - xc1) * (yc2 - yc1)

    total_area = total_area_p + total_area_c

    intersection_area = max(min(xp2,xc2) - max(xc1,xp1),0)
    intersection_area *= max(min(yp2,yc2) - max(yc1,yp1),0) 

    union_area = total_area - intersection_area

    return intersection_area/union_area

def nonMaxSuppression(X : np.ndarray, scores: np.ndarray):
    assert X.shape[1] == FEATURE_SIZE   
    assert X.shape[0] == len(scores)

    # get the indices of the scores
    indices = np.argsort(scores).tolist()

    keep_idx = []
    while True:
        p_idx = indices.pop()
        keep_idx.append(p_idx)
        p_feat = X[p_idx,:]
    
        # compute the overlap betweeen p_idx
        ious = [ iouOverlap(p_feat, X[c_idx,:] ) for c_idx in indices]
        
        # update the set of indices
        indices = [ idx for idx, iou in enumerate(ious) if iou <= IOU_THRESHOLD ]
        
        if not indices:
            break
    X = np.array([ X[idx] for idx in keep_idx])

    return X