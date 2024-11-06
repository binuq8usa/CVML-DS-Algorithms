/*

Given two sparse matrices mat1 of size m x k and mat2 of size k x n, return the result of mat1 x mat2. You may assume that multiplication is always possible.


sparse matrix - 

Compressed Sparse Row representation
Compressed Sparse Col representation

K = numver of non zero values
V = {non zero values}  => 1 X K
Col Index = {which cols contain those non-zero} => 1 X K
Row index = 1 x m (rows) => end col location of a non-zero value along the row index

14 0 12 0
 0 0 1 0
 0 0 0 43
 
 # extract column wise rows => sparse representation of vector
 rowIndex = [0, 2, 3, 4]
 V = 14, 12,1,43
 Col = 0,2,2,3
 
 
 => Extract column-wise vectors => sparse representation of vector
 colIndex = [0,1,3,4]
V = 14,12,1,43
Row = 0,0,1,2

*/

#include <iostream>
#include <ostream>
#include <vector>
#include <utility>
#include <cassert>

using namespace std;

template <typename T>
ostream& operator<<(ostream& oss, const vector<T>& vec) {
    oss << "[";
    for(auto& v : vec) {
        oss << v << " ";
    }
    oss << "]\n";
    return oss;
}

template <typename T>
class SparseVector{
    private: 
        vector<pair<T, int>> entries; // store value and indices
        int mSize; 
        
    public:
        SparseVector(const vector<T>& elements) {
            for(int i = 0 ; i < elements.size(); i++) {
                if (elements[i] != 0) {
                    entries.push_back(make_pair(elements[i],i));
                }
            }
            mSize = elements.size();
        }
        
        SparseVector(const vector<T>& values, const vector<int>& indices, int totalSize) {
            assert (values.size() == indices.size());
            for(int i = 0; i < values.size(); i++) {
                entries.push_back(make_pair(values[i], indices[i]));
            }
            mSize = totalSize;
        }
        
        ~SparseVector() {
            entries.clear();
        }
        
        int getNumNonZeroValues() {
            return entries.size();
        }
        
        pair<T,int> getElement(int index) {
            return entries[index];
        }
        
        int getTotalSize() {
            return mSize;
        }
                
        T operator*(SparseVector& firstVec) {
            T val= 0;
            if (this->getTotalSize() != firstVec.getTotalSize()) {
                return -1;
            }
            int prevJ = 0;
            for(int i = 0 ; i < this->getNumNonZeroValues(); i++) {
                auto refEntry = this->getElement(i); // 0
                for(int j = prevJ; j < firstVec.getNumNonZeroValues(); j++) {
                    auto entry = firstVec.getElement(j); // 1
                    if (refEntry.second == entry.second) {
                        val += (refEntry.first * entry.first);
                        prevJ = j+1;
                        break;
                    } else if (refEntry.second > entry.second) { // 
                        continue;
                    } else {
                        break;
                    }
                }
            }
            return val;
        }
    friend ostream& operator<<(ostream& oss, const SparseVector<T>&  vect) {
        oss << "[";
        int index = 0;
        int lastIndex = -1;
        for(auto& valP : vect.entries) {
            lastIndex = valP.second;
            for(int i = index ; i < lastIndex; i++) {
                oss << 0 << " ";
            }
            oss << valP.first << " ";
            index = lastIndex+1;
        }
        for(int i = lastIndex+1; i < vect.mSize; i ++) {
            oss << 0 << " ";
        }
        oss << "]"; 
        return oss;
    }
}; 

template <typename T>
class SparseMatrix{
    private:
        // FOr CSR format
        vector<int> mRowIndex;
        vector<T> mRValues;
        vector<int> mCol;
        
        int rows;
        int cols;
    
        // For CSC Format
        vector<int> mRow;
        vector<T> mCValues;
        vector<int> mColIndex;
        
    public:
        SparseMatrix(const vector<vector<T>>& matrix) {
            rows = matrix.size();
            cols = matrix[0].size();
            mRowIndex.push_back(0); // 
            
            // Create CSR format
            for(int row = 0; row < this->rows; row++) {
                for(int col = 0 ; col < this->cols; col++) {
                    if (matrix[row][col] != 0) {
                        mCol.push_back(col);
                        mRValues.push_back(matrix[row][col]);
                    }
                }
                mRowIndex.push_back(mRValues.size());
            }
            
            // Create CSC Format
            mColIndex.push_back(0);
            for(int col = 0;  col < this->cols; col++) {
                for(int row = 0; row < this->rows; row++) {
                if (matrix[row][col] != 0) {
                        mRow.push_back(row);
                        mCValues.push_back(matrix[row][col]);
                    }
                }
                mColIndex.push_back(mCValues.size());
            }
        }
        
        virtual ~SparseMatrix() {
            mRowIndex.clear();
            mRValues.clear();
            mCol.clear();
            
            mRow.clear();
            mCValues.clear();
            mColIndex.clear();   
        }
        
        SparseVector<T> getRow(int index) const{
            assert (index < rows);
            int startInd = this->mRowIndex[index];
            int endInd = this->mRowIndex[index+1];
            
            vector<T> vals(this->mRValues.begin() + startInd, this->mRValues.begin() + endInd);
            vector<int> inds(this->mCol.begin() + startInd, this->mCol.begin() + endInd);
            
            return SparseVector<T>(vals, inds, cols);
        }
        
        SparseVector<T> getCol(int index) const {
            assert (index < cols);
            int startInd = this->mColIndex[index];
            int endInd = this->mColIndex[index+1];
            
            vector<T> vals(this->mCValues.begin() + startInd, this->mCValues.begin() + endInd);
            vector<int> inds(this->mRow.begin() + startInd, this->mRow.begin() + endInd);
            
            return SparseVector<T>(vals, inds, rows); 
        }
        
        int getNumRows() const {
            return this->rows;
        }
        int getNumCols() const {
            return this->cols;
        }
        
        SparseMatrix operator*(const SparseMatrix& firstMatrix) {
            assert (this->cols == firstMatrix.getNumRows());
            
            vector<vector<T>> result(this->rows, vector<T>(firstMatrix.getNumCols(),0));
            for(int row = 0; row < this->rows; row++) {
                SparseVector rowVec = this->getRow(row);
                for(int col = 0; col < firstMatrix.getNumCols() ; col++) {
                    SparseVector colVec = firstMatrix.getCol(col);
                    result[row][col] = rowVec * colVec;
                }
            }
            return SparseMatrix<T>(result);
        }
        
        void printSparse(){
            std::cout << "RValues : " << this->mRValues << std::endl;
            std::cout << "Col : " << this->mCol << std::endl;
            std::cout << "mRowIndex : " << this->mRowIndex << std::endl;
            
            std::cout << "CValues : " << this->mCValues << std::endl;
            std::cout << "Row : " << this->mRow << std::endl;
            std::cout << "mColIndex : " << this->mColIndex << std::endl;
        }
        
        friend ostream& operator<<(ostream& oss, const SparseMatrix<T>& mat1) {
            // print each row
            oss << "RowWise : \n";
            for(int i = 0 ; i < mat1.rows; i++) {
                SparseVector<T> rowVec = mat1.getRow(i);
                oss << rowVec << "\n";                
            }
            oss<< "\n";

            oss << "ColWise : \n";
            for(int i = 0 ; i < mat1.cols; i++) {
                SparseVector<T> colVec = mat1.getCol(i);
                oss << colVec << "\n";                
            }
            return oss;
            
            // print each col
        }
};

void test_dot_product(const vector<float>& vec1, const vector<float>& vec2) { 
    SparseVector<float> a(vec1); // 0,1,2,5  ->  i
    SparseVector<float> b(vec2); // 0,2,3,5. ->  j
    
    std::cout << "a " << a << std::endl;
    std::cout << "b " << b << std::endl;
    
        float val = a * b;
    
    std::cout << "Dot Product : " << val << std::endl;
}

void test_matrix_multiply(const vector<vector<float>>& mat1, const vector<vector<float>>& mat2) {
    SparseMatrix<float> a(mat1);
    SparseMatrix<float> b(mat2);
    
    std::cout << a << std::endl;
}

int main(int argc, char** argv) {
    
    //test_dot_product(vector<float>{1,2,2,0,0,4}, vector<float>{1,0,3,1,0,6});
    vector<vector<float>> mat1{
        {10, 20, 0, 0, 0, 0},
        {0, 30, 0, 40, 0, 0},
        {0, 0, 50, 60, 70, 0},
        {0, 0, 0, 0, 0, 80}
    };
    
    vector<vector<float>> mat2{
        {1,0,0,0},
        {0,10,0,0},
        {0,0,0,0},
        {0,0,1,8},
        {0,0,10,2},
        {2,0,0,0}
    };
    
    SparseMatrix<float> a(mat1);
    SparseMatrix<float> b(mat2);
    
    std::cout << "A : \n" << a << std::endl;
    std::cout << "B : \n" << b << std::endl;
    //a.printSparse();
    
    SparseMatrix result = a * b;
    std::cout << "Result : \n" << result << std::endl;

}


