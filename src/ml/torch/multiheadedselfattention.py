"""
Implement a vision transformer 
    - embeddings
    - multilayer-perceptron
    - multi-headed self attention
    - class labels

-- Impplement the forward pass
"""

"""
Vision transformer - 
- input image ->  (H,W,C) -> P^2 x C 
-  L - P^2 , C =1 
- P^2 x C => P^2 X d_model
- learnable class token - of size 1 x d_model 
- ( P^2 + 1 ) x d_model 
- position embeddings - learning  -> P^2 x d_model      

- transformer block 

    -> LayerNorm + MHSA + LayerNorm + MLP 

"""

import torch.nn as nn
import torch.nn.functional as F
import math 

class MultiHeadedSelfAttension(nn.Module):
    def __init__(self, p_dropout = 0.1, d_model = 512, num_heads = 8, d_k = None, d_v = None):
        super(MultiHeadedSelfAttension, self).__init__()
        self.p_dropout = p_dropout
        self.d_model = d_model
        self.num_heads = num_heads
        
        self.d_k = self.d_model // self.num_heads  if self.d_k is None else self.d_k
        self.d_v = self.d_k if self.d_v is None else self.d_v

        # adding the layer norms, and p_dropout
        self.layernorm = nn.LayerNorm(self.d_model)
        self.dropout = self.dropout(p_dropout)
        
        # add the weight matrices - Query, Key and Value matrices
        self.q_weights = nn.Linear(self.d_model, self.num_heads * self.d_k)
        self.k_weights = nn.Linear(self.d_model, self.num_heads * self.d_k)
        self.v_weights = nn.Linear(self.d_model, self.num_heads * self.d_v)

        # projection matrix
        self.proj_weights = nn.Linear(self.d_v * self.num_heads, self.d_model)
        self.softmax = nn.Softmax(dim=-1)

    def forward(self, x):

        B,L,d_model = x.shape
        assert d_model == self.d_model
        
        # split into query, key Value
        # query_x, key_x, value_x = self.weights(x).split(self.d_model, dim=2) # along the last dimension
        query_x = self.q_weights(x)
        key_x = self.k_weights(x)
        value_x = self.v_weights(x)

        # divide into multiple num_heads -> B X L X num_heads X d_k  => B x num_heads x L x d_k
        query_x = query_x.view(B, L, self.num_heads, self.d_k).transpose(1,2)
        key_x = key_x.view(B, L, self.num_heads, self.d_k).transpose(1,2)
        value_x = value_x.view(B, L, self.num_heads, self.d_v).transpose(1,2)

        # compute attention - softmax(Q @ K^T / sqrt(d_k)) V 
        att = query_x @ key_x.transpose(-2,-1)
        att /= math.sqrt(self.d_k)

        # compute self attentions # B X num_heads X L X L
        s_att = self.softmax(att) 

        # B x num_heads x L x d_v
        outputs = s_att @ value_x

        # B x L x num_heads x dv
        outputs = outputs.transpose(1,2).contiguous().view(B,L, self.num_heads * self.d_v)
        outputs = self.dropout(self.outputs)

        y = self.dropout(self.proj_weights(outputs))
        return y
        

class VisionTransformer(nn.Module):
    def __init__(self, num_blocks = 6, num_classes = 10, patch_size = 16):
        super(VisionTransformer, self).__init__()
        self.num_blocks = num_blocks
        self.num_classes = num_classes
        self.patch_size = patch_size

    def forward(self, x):
        pass

    
