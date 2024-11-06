/**

Class X and there is a reference to another object of X. 

Create a constructor

Discrete math
Computation algorithms


*/
#include <iostream>

using namespace std;

class X {
  
  
 public:
  	X* obj = nullptr;
  	X() {
      obj = new X();
    }  

  	// 
  	X(X* newX) {
    	this->obj = newX;  
    }
	
  	virtual void print() {
      std::cout << "Print from X" << std::endl;
    }
  
  	// O(Value of B) - 
    // f(# elements) of a certai degree 1 .. M
    // O(# max(a, b)) // O(Zerom ) // O()
  
  	// algorithm is polynomial in the size of the input
  	// This is not pseudo-polynomial time algorithm - number of bits 
  	void SimpleFunction(int n) {
      
      // 
      for(int i = 0 ; i< n; i++) {
        
      }
    }
  
  	// size of a and b is linear with the value of a or b. - polynomial time
    static X plus(const X a, const X b) {
      X retVal = a;  // new Obj 
      if (b == nullptr) return retVal;
      return X::plus(new X(&retVal), b->obj) 
      
        /*
      // iterateiv
      while (b!= nullptr) {
        retVal = new X(&retVal);  // NewVal.obj = NewVal
        b = b->obj; // iterate across b 
      }
      
      return retVal;
      */
    }
  
  	virtual ~X() {
      delete this->obj;
    }
 	
};

// class DerivedX : private X {
//   public:
//   	virtual void print() {
//       std::cout << "Print from Derived C" << std::endl;
//     }
// };

// //                                       |      |
// // Hund -> 99 -> ............  Three->  Two -> One -> Zero
// //  One + Two =>  Three
// //

// X Zero = new X(nullptr);
// X One = new X(&Zero);
// X Two = new X(&One);

// X Hund = new X(&NineTyNine)
  


