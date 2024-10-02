/*
Given a string s which represents an expression, evaluate this expression and return its value. 

The integer division should truncate toward zero.

You may assume that the given expression is always valid. All intermediate results will be in the range of [-231, 231 - 1].

Note: You are not allowed to use any built-in function which evaluates strings as mathematical expressions, such as eval().

*/

/*

"13*2+15/2" -> 
"1/2"
"3 * 2 / 4"

set_ops = {'*','+','-','/'}

currentNumber = 0
multiplier=1
accum = 0
curr_sign = '+'
for ch : s
  if (ch == ' ') continue;
  currentNumber = currentNumber*10 + int(ch - '0')
  if ch == '*':
    multipler *= currentNumber
  else if ch == '/':
    multiplier  /= currentNumber

*/


#include <iostream>
#include <string>
#include <set>
#include <cassert>
#include <algorithm>

using namespace std;

int operation(int num1, int num2, char op) {
  if (op == '*') return num1 * num2;
  else if (op == '-') return num1 - num2;
  else if (op == '/') return num1/num2;
  else return num1 + num2;
}

int calculator(string exp) {

  int* currNumber = nullptr;
  set<char> ops;
  ops.insert('*'); ops.insert('+'); ops.insert('-'); ops.insert('/');

  int* lastNumber = nullptr;
  char* op = nullptr;
  int result = 0;
  // a*b - c*d

  // remove trailing space from exp
  exp.erase(remove(exp.begin(), exp.end(),' '),exp.end());
  std::cout << "Sstr :: " << exp << std::endl;

  // linear time 
  for(auto it = exp.begin(); it!= exp.end(); it++) {
    char ch = (*it);
    std::cout << "ch : " << ch << std::endl;
    if (iswspace(ch)) continue;
    if (isdigit(ch)) {
      if (!currNumber) {
        currNumber = new int[1];
        currNumber[0] = ch - '0';
      } else {
        currNumber[0] = 10*currNumber[0] + int(ch - '0');
      }
    } 
    if(ops.find(ch) != ops.end() || it == exp.end()-1) { // if its an operator 
      if(!op) op = new char[1];
      
      // set the operator 
      if (!lastNumber) {
        lastNumber = new int[1];
        lastNumber[0] = currNumber[0]; // save the number
      } else {  
        // resolve the operation with the currNumber 
        if (op[0] == '*' || op[0] == '/') {
          // update last number 
          lastNumber[0] = operation(lastNumber[0], currNumber[0], op[0]);
        } else { // resolve for '+','-'
          result += lastNumber[0]; // accumuldate the result
          // reverse the sign of the current number if -
          lastNumber[0] = (op[0] =='+') ? currNumber[0] : -currNumber[0];
        }
      }
      // update the operator
      op[0] = ch; // updates the operator
      currNumber[0] = 0; // set current number as zero
    } 
  }
  std::cout << "last number " << lastNumber[0] << std::endl;
  result += lastNumber[0];
  
  // delete lastNumber;
  // delete op;
  return result;
}

// To execute C++, please define "int main()"
int main() {
  string s ="5  ";
  int val = calculator(s);
  std::cout << "Val : " << val << std::endl;
}
