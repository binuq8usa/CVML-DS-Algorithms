import numpy as np

# https://stackoverflow.com/questions/59127007/where-is-the-source-code-of-pytorch-conv2d
# https://github.com/99991/NumPyConv2D/blob/main/conv2d.py
# https://discuss.pytorch.org/t/how-to-keep-the-shape-of-input-and-output-same-when-dilation-conv/14338

from enum import Enum
class PaddingMode(Enum):
    SAME = 0,
    VALID = 1,
    OTHER = 2

class Conv2D:
    def __init__(self, in_channels=1, out_channels=1, kernel_size=3, stride=1, 
                 padding=0, padding_mode = PaddingMode.VALID, dilation=1, use_bias = True):
        self.c_in = in_channels
        self.c_out = out_channels
        self.kernel_size = kernel_size
        self.stride = stride
        self.padding = padding
        self.dilation = dilation
        self.padding_mode = padding_mode
        self.h_in = None
        self.w_in = None
        self.h_out = None
        self.w_out = None
        
        self.W = np.random.random((self.c_out, self.c_in, self.kernel_size, self.kernel_size))           
        self.bias = np.random.random((self.c_out, )) if use_bias else None
        
    def __call__(self, X):
        return self.forward(X)

    def pad_input(self, X):
        self.h_in, self.w_in = X.shape[-2:]
        
        if self.padding_mode == PaddingMode.SAME:
            self.h_out = self.h_in
            self.w_out = self.w_in
            # formula for computing output size given pad size
            # W_out = floor( [W_in - 2*pad - kernal_size - (kernel_size - 1)*(dilation-1)]/stride + 1
            # if W_out = Win => 2*pad = (stride-1) * (W_in - 1) + (kernel_size-1) * dilation
            
            # use dilation-
            pad_H = (self.stride - 1) * (self.h_in - 1) + self.dilation * (self.kernel_size - 1)
            pad_W = (self.stride - 1) * (self.w_in - 1) + self.dilation * (self.kernel_size - 1)
            pad_width = ((0,0),(0,0),(pad_H//2, pad_H - pad_H//2),(pad_W//2,pad_W - pad_W//2) )
        else:
            pad_width = ((0,0),(0,0),(self.padding, self.padding),(self.padding, self.padding))
            self.h_out = np.floor( (self.h_in + 2 * self.padding - self.kernel_size 
                             - (self.kernel_size -1) * (self.dilation-1))/self.stride ) + 1
            self.w_out = np.floor( (self.w_in + 2 * self.padding - self.kernel_size 
                             - (self.kernel_size -1) * (self.dilation-1))/self.stride ) + 1
            
        return np.pad(X, pad_width, mode="constant")
    
    def conv2d(self, X, W):
        dilated_kernel_size = (self.kernel_size - 1) * self.dilation + 1
        stride = self.stride
        assert X.ndim == 2 and W.ndim == 2
        H, W  = X.shape
        
        result_array = np.zeros((self.h_out, self.w_out))
        res_row = 0
        for row in range(dilated_kernel_size//2, H - dilated_kernel_size//2, stride):
            res_col = 0
            for col in range(dilated_kernel_size//2, W - dilated_kernel_size//2, stride):
                # multiply the weight matrices
                for i in range(0, dilated_kernel_size, self.dilation):
                    for j in range(0, dilated_kernel_size, self.dilation):
                        result_array[res_row][res_col] += W[i,j] * X[row,col]   
                res_col += 1
            res_row += 1            
        return result_array

    def forward(self, X):
        N, C_in, H_in, W_in = X.shape
        assert C_in == self.c_in
        C_out = self.c_out
        
        # first pad the input
        X = self.pad_input(X)
        _,_,H_in_padded, W_in_padded = X.shape
       
        X_out = np.zeros((N, C_out, self.h_out, self.w_out))
            
        # for each batch dimension
        for batch_num in range(N):
            for c_out in range(C_out):
                result_array = np.zeros((self.h_out, self.w_out))
                
                # iterate over the input channels - apply the 3D W filter for a single C_out channel over a X input
                for c_in in range(C_in):
                    result_array += self.conv2d(X[batch_num,c_in, :,:], self.W[c_out, c_in,:,:])
                result_array += self.bias[c_out]
                X_out[batch_num, c_out, :,:] = result_array
        
        return X_out