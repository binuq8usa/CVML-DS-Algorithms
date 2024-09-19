import numpy as np
import math

class SoftmaxLayer:
    def __init__(self):
        pass
    
    def __call__(self,z):
        return np.exp(z) / np.sum(np.exp(z), axis=-1) 

# inverted droput
class DropoutLayer:
    def __init__(self, p):
        self.p = p
    
    def __call__(self, x):
        mask= np.random.random(x.shape[0], x.shape[1]) < 0.5
        return 1/(1-self.p) * (x * mask)

class MultiHeadedSelfAttentionLayer:
    def __init__(self, d_model = 512, num_heads = 8, d_k = None, d_v = None, p_dropout = 0.5):
        self.d_model = d_model
        self.num_heads = num_heads
        self.d_k = self.d_model // self.num_heads if d_k is None else d_k
        self.d_v = self.d_model // self.num_heads if d_v is None else d_v
        
        # create the weight matrices to get Q, K and V vector
        self.W_Q = np.random.random((self.d_model, self.num_heads * self.d_k))
        self.W_K = np.random.random((self.d_model, self.num_heads * self.d_k))
        self.W_V = np.random.random((self.d_model, self.num_heads * self.d_v))
        
        # projection weights
        self.W_O = np.random.random((self.num_heads * self.d_v, self.d_model))
        self.softmax = SoftmaxLayer()
        self.dropout = DropoutLayer(p=p_dropout)
        
    def __call__(self,x, mask = None):
        return self.forward(x, mask = None)
        
    def forward(self, x, mask = None):
        # x is num_batches x seq_length x d_model
        B, L, d_model = x.shape
        assert d_model == self.d_model
        
        # get query, key and values
        query_x = x @ self.W_Q
        key_x = x @ self.W_K
        value_x = x @ self.W_V
        
        # reshape query, key and value into num_batches x num_heads x seq_length x d_k or d_v
        query_x = np.reshape(query_x, (B, L, self.num_heads, -1)).transpose(0,2,1,3)
        key_x = np.reshape(key_x, (B, L, self.num_heads, -1)).transpose(0,2,1,3)
        value_x = np.reshape(value_x, (B, L, self.num_heads, -1)).transpose(0,2,1,3)

        # get the scores per - num_batchs x num_heads x L x L scores
        scores = query_x @ key_x.transpose(0,1,3,2) / math.sqrt(self.d_k)
        scores = self.dropout(scores)
        
        if mask is not None:
            indices = (mask == False)
            scores[indices] = float('-inf')
        
        # apply softmax
        p_scores = self.softmax(scores)
        
        # scores are B x num_heads x L x L  value if B x num_heads x L x d_v
        atten_scores = p_scores @ value_x 
        
        # transpose the attention scores
        # B x num_heads x L x d_v =? 
        atten_scores = atten_scores.transpose(0,2,1,3)
        atten_scores = atten_scores.reshape(B,L,-1)
        
        output = atten_scores @ self.W_O
        output = self.dropout(output)
        
        return output
    

    