/*
Implement a Singleton class - 
1. one instance
https://refactoring.guru/design-patterns/singleton/cpp/example#example-1

*/

#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>

using namespace std;

class Singleton{
  private:
    int value;
    static Singleton* singleton_;
    static std::mutex mutex_;

    Singleton(int value) : value(value) {}
    virtual ~Singleton() {}

  public:
    // not cloneable
    Singleton(Singleton& instance) = delete;

    // cannot be assigned
    void operator=(const Singleton& instance) = delete;

    // get instance
    static Singleton* getInstance(int value);

    void businessLogic() {

    }

    int getValue() const{
      return this->singleton_->value;
    }
};

Singleton* Singleton::singleton_ = nullptr;
std::mutex Singleton::mutex_;

Singleton* Singleton::getInstance(int value) {
  std::lock_guard<std::mutex> lock(mutex_);
  if (singleton_ == nullptr) {
    singleton_ = new Singleton(value);
  }
  return singleton_;
}

void ThreadFoo() {
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  Singleton* singletone = Singleton::getInstance(3);
  std::cout << "Singleton value : " << singletone->getValue() << std::endl;
}

void ThreadBar() {
  std::this_thread::sleep_for(std::chrono::milliseconds(4000));
  Singleton* singletone = Singleton::getInstance(15);
  std::cout << "Singleton value : " << singletone->getValue() << std::endl;
}

void IncFunc(int value) {
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  Singleton* singleton = Singleton::getInstance(value);
  std::cout << "Val : " << singleton->getValue() << std::endl;
}

// To execute C++, please define "int main()"
int main() {

  std::thread thread1(IncFunc, 5);
  std::thread thread2(IncFunc, 14);

  thread1.join();
  thread2.join();

  return 0;
}
