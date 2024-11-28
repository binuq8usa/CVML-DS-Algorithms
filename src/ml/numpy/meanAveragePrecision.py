"""
Compute mean average precision of the class

The data are given as

test_data/mAP/
"detections"
"groundtruths" 

Read the text files in ground and detection, 
compute iOU, and set it as TP and FP based on the GT.

Then, compute AP_11 point algorihtm for each class

Compute mAP

"""

import os
from pprint import pprint
from pathlib import Path
from collections import defaultdict
from heapq import heapify, heappop, heappush, nlargest

IOU_THRESHOLD=0.5
from typing import List, Dict

def read_test_data():
    test_data_folder = Path('./test_data/mAP/')
    detections = test_data_folder.joinpath('detections')
    groundtruth = test_data_folder.joinpath('groundtruths')
    
    
    detections_per_class : Dict[str, List[float]] = defaultdict(list)
    for det_file in detections.glob('*.txt'):
        with open(det_file) as fid:
            data = fid.readlines()
            for dd in data:
                elements = dd.strip().split(sep=' ')
                class_name = elements[0]
                bbox = [float(element) for element in elements[1:]]
                if class_name not in detections_per_class:
                    detections_per_class[class_name] = []
                detections_per_class[class_name].append(bbox)
                
    gt_per_class : Dict[str, List[float]] = defaultdict(list)
    for gt_file in groundtruth.glob('*.txt'):
        with open(gt_file) as fid:
            data = fid.readlines()
            for dd in data:
                elements = dd.strip().split(sep=' ')
                class_name = elements[0]
                bbox = [int(element) for element in elements[1:]]
                if class_name not in gt_per_class:
                    gt_per_class[class_name] = []
                gt_per_class[class_name].append(bbox)

    return detections_per_class, gt_per_class       

def compute_iou(bbox_a, bbox_b):
    """
    x_min, y_min, width, height

    """
    x_min_a, y_min_a, width_a, height_a = bbox_a
    x_min_b, y_min_b, width_b, height_b = bbox_b

    x_max_a = x_min_a + width_a
    y_max_a = y_min_a + height_a
    
    x_max_b = x_min_b + width_b
    y_max_b = y_min_b + height_b

    max_area_b = (x_max_b - x_min_b) * (y_max_b - y_min_b)
    max_area_a = (x_max_a - x_min_a) * (y_max_a - y_min_a)

    """
    amin        amax
                       bmin      bmax
    
    
    """

    inter_ab = min( min(x_max_a, x_max_b) - max(x_min_a, x_min_b) ,0)
    inter_ab *= min( min(y_max_a, y_max_b) - max(y_min_a, y_min_b) ,0)
    
    union_ab = max_area_a + max_area_b - inter_ab
    
    return inter_ab/union_ab

def compute_prec_recall(list_of_tps, list_of_fps, num_gt):
    # compute avg_tp and fp
    c_val_t = 0
    c_val_f = 0
    avg_tp = []
    avg_fp = []
    for val_t, val_p in zip(list_of_tps,list_of_fps): 
        c_val_t += val_t
        avg_tp.append(c_val_t)
        c_val_f += val_p
        avg_fp.append(c_val_f)
    
    prec = [ av_t/ (av_t + av_p) for av_t, av_p in zip(avg_tp, avg_fp)]
    recall = [ av_t/ num_gt for av_t in avg_tp ]
    
    return prec, recall 

def compute_11_pt_ap(prec, recall):
    """
    AP 11 pt metric
    

    Args:
        prec (_type_): _description_
        recall (_type_): _description_

    """
    
    # 0 to 0.1
    max_ap = 0
    
    for rr in range(0, 11, 1):
        # find index in recall where its just greater than r=0.1
        max_val = 0
        r_indices = [ idx for idx, rec in enumerate(recall) if rec >= 0.1*rr]
        for idx in r_indices:
            max_val = max(max_val, prec[idx])
        max_ap += max_val
    max_ap /= 11
    return max_ap
    

def compute_ap(detections_per_class, gt_per_class): 
    # we have the bounding box, confidence - 
    # comparing a detection to a GT -> TP , assign detection as TP, and GT as Already checked. 
    # Use the highest confidence 

    for class_name, detections in detections_per_class.items():
        if class_name not in gt_per_class:
            continue
        # sorted the detections
        tp : List[int] = []
        fp : List[int] = []
        
        # get the sorted indices
        sorted_detections = sorted(detections, reverse=True, key=lambda x : x[0])
        gt_detections = gt_per_class[class_name]
        num_gt = len(gt_detections)
        # iterate through each detection, and set precision and recall
        for idx, detection in enumerate(sorted_detections):
            conf = detection[0]
            det_bbox = detection[1:]
            if idx > 0:
                assert (conf <= sorted_detections[idx-1][0])
        
            # compute ious
            ious = [ (compute_iou(det_bbox, gt), g_idx) for g_idx, gt in enumerate(gt_detections) ]
            
            # max iou
            max_iou,max_gt_idx = nlargest(1, ious, key=lambda x:x[0])[0]     
            
            if max_iou >= 0.5:
                tp.append(1)
                fp.append(0)
                
                # removes from the list of gt
                gt_detections.pop(max_gt_idx)
            else: 
                tp.append(0)
                fp.append(1)
            
        prec,recall = compute_prec_recall(tp, fp, num_gt=num_gt)
        print(f'Prec : {prec}')
        print(f'Recall : {recall}')
        ap = compute_11_pt_ap(prec, recall)
        print(f'AP : {ap}')
        
        
                
    
detections_per_class, gt_per_class = read_test_data()
pprint(detections_per_class)
pprint(gt_per_class)
compute_ap(detections_per_class=detections_per_class, gt_per_class=gt_per_class)

