/*


Create a class where it can add two complext numnbers

floating point
a + bi
c + dj


*/

#include <iostream>
#include <ostream>
using namespace std;

class ComplexNumber{
  private:
    float real;
    float imag;

  public : 
    ComplexNumber() {}
    ComplexNumber(float a, float b) : real(a), imag(b) {}
    ~ComplexNumber() {}

    ComplexNumber operator+(ComplexNumber& num) {
      ComplexNumber res;
      res.real = this->real + num.real;
      res.imag = this->imag + num.imag;
      return res;
    }

    friend ostream& operator<<(ostream& os, const ComplexNumber& num);
};

ostream& operator<<(ostream& os, const ComplexNumber& num) {
  os << "(" << num.real << " + " << num.imag << "j)";
  return os;
}

// To execute C++, please define "int main()"
int main() {
  ComplexNumber c1(3,4);
  ComplexNumber c2(4,5);

  ComplexNumber c3 = c1 + c2;

  std::cout << c3 << std::endl;

}
