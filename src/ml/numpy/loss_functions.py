import numpy as np
from meanAveragePrecision import read_test_data   

def compute_giou_loss(bbox_a: np.ndarray, bbox_b: np.ndarray):
    """
    Args:
        bbox_a (_type_): left, top, width, height
        bbox_b (_type_): _description_
    """
    
    # get coords 
    x_min_a, y_min_a, width_a, height_a = bbox_a
    x_min_b, y_min_b, width_b, height_b = bbox_b
    x_max_a = x_min_a + width_a
    x_max_b = x_min_b + width_b 
    y_max_a = y_min_a + height_a
    y_max_b = y_min_b + height_b 
    
    # compute union
    area_a = (x_max_a - x_min_a) * (y_max_a - y_min_a)
    area_b = (x_max_b - x_min_b) * (y_max_b - y_min_b)
    union_ab = area_a + area_b
    assert(area_a >= 0 and area_b >= 0)    

    # compute intersection
    # a     b
    #           c     d
    x_hat_max = min(x_max_a, x_max_b)
    x_hat_min = max(x_min_a, x_min_b )
    y_hat_max = min(y_max_a, y_max_b)
    y_hat_min = max(y_min_a, y_min_b )
    inter_ab =  (min(x_hat_max, 0) - min(x_hat_min, 0)) * (min(y_hat_max,0) - min(y_hat_min,0))
    assert (inter_ab >= 0)
    
    # compute iou
    iOU = inter_ab / (union_ab - inter_ab)
    assert 0 <= iOU <= 1
    
    # compute min convex hull  
    x_convex_min = min(x_min_a, x_min_b)
    x_convex_max = max(x_max_a, x_max_b)
    y_convex_min = min(y_min_a, y_min_b)
    y_convex_max = max(y_max_a, y_max_b)
    c_area = (y_convex_max - y_convex_min) * (x_convex_max - x_convex_min)
    assert (c_area >= 0)
    
    gIOU = iOU - (c_area - union_ab)/c_area
    
    assert -1 <= gIOU <= 1
    
    return 1 - gIOU

def compute_generalized_iou_loss():
    detections_per_class, gt_per_class = read_test_data()
    
    for class_name, detections in detections_per_class.items():
        if class_name not in gt_per_class:
            continue
        
        # gt_detections
        gt_detections = gt_per_class[class_name]
        
        sorted_detections = sorted(detections, reverse=True, key=lambda x : x[0])
        for idx, detection in enumerate(sorted_detections):
            conf = detection[0]
            det_bbox = detection[1:]
            if idx > 0:
                assert (conf <= sorted_detections[idx-1][0])
        
            # compute ious
            g_ious_losses = [ compute_giou_loss(np.array(det_bbox), np.array(gt)) for g_idx, gt in enumerate(gt_detections) ]
            
            # print the losses
            print(f'Losses for {idx} : {g_ious_losses}')

compute_generalized_iou_loss()