#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

#define WOODEN_SCALE_FACTOR 1.0
#define STEEL_SCALE_FACTOR 2.0
#define SUSPENDED_SCALE_FACTOR 0.5

vector<vector<string>> input = {
  {"Wooden", "4", "2", "Chain"},         // Expected: 2.0
  {"Steel", "20", "0", "Cable"},         // Expected: 10.0
  {"Suspended", "2", "0.5", "Cable"},    // Expected: 1.5
  {"Suspended", "2", "0.5", "Chain"},    // Expected: 1.0
  {"Suspended", "2", "0.5", "Launched"}, // Expected: 1.1
};

enum class LiftType{
  CABLE,
  CHAIN,
  LAUNCHED,
  INVALID
};

enum class RollerCoasterType{
  WOODEN,
  STEEL,
  SUSPENDED,
  INVALID
};

LiftType getEnumLiftType(std::string& str) {
  if (str == "Cable") return LiftType::CABLE;
  if (str == "Chain") return LiftType::CHAIN;
  if (str == "Launched") return LiftType::LAUNCHED;
  return LiftType::INVALID;
}

RollerCoasterType getEnumCoasterType(std::string& str) {
  if (str == "Wooden") return RollerCoasterType::WOODEN;
  if (str == "Steel") return RollerCoasterType::STEEL;
  if (str == "Suspended") return RollerCoasterType::SUSPENDED;
  return RollerCoasterType::INVALID;
}

class BaseRollerCoaster{
  protected:
    int mMaxSpeed;
    float mBumpsPerSecond;
    LiftType mLiftType; 

  public:
    BaseRollerCoaster() {}

    BaseRollerCoaster(int maxSpeed, float bumpsPerSpeed, std::string liftType) : mMaxSpeed(maxSpeed), mBumpsPerSecond(bumpsPerSpeed) {
      mLiftType = getEnumLiftType(liftType);
    }

    void setMaxSpeed(int value) {
      mMaxSpeed = value;
    }

    void setBumpsPerSecond(float value) {
      mBumpsPerSecond = value;
    }

    void setLiftType(std::string str) {
      mLiftType = getEnumLiftType(str);
    }

    virtual ~BaseRollerCoaster() {}

    virtual float comfortScore() {
      return min(1.0, 1.0 / mBumpsPerSecond);
    }

    virtual float overallScore() = 0;
};

class WoodenRollerCoaster : public BaseRollerCoaster {
  protected:
    float mScaleFactor = WOODEN_SCALE_FACTOR;

  public:

    WoodenRollerCoaster() {}
    WoodenRollerCoaster(int maxSpeed, float bumpsPerSpeed, std::string liftType) {
      this->setMaxSpeed(maxSpeed);
      this->setBumpsPerSecond(bumpsPerSpeed);
      this->setLiftType(liftType);
    }    

    ~WoodenRollerCoaster() {}

    float overallScore() override {
      return mScaleFactor * mMaxSpeed * this->comfortScore();
    }
};


class SteelRollerCoaster : public BaseRollerCoaster {
  protected:
    float mScaleFactor = STEEL_SCALE_FACTOR;

  public:

    SteelRollerCoaster() {}
    SteelRollerCoaster(int maxSpeed, float bumpsPerSpeed, std::string liftType) {
      this->setMaxSpeed(maxSpeed);
      this->setBumpsPerSecond(bumpsPerSpeed);
      this->setLiftType(liftType);
    }   

    float comfortScore() override {
      return min(1.0, 5.0/mMaxSpeed);
    } 

    ~SteelRollerCoaster() {}

    float overallScore() override {
      return mScaleFactor * mMaxSpeed * this->comfortScore();
    }
};


class SuspendedRollerCoaster : public BaseRollerCoaster {
  protected:
    float mScaleFactor = SUSPENDED_SCALE_FACTOR;

  public:

    SuspendedRollerCoaster() {}
    SuspendedRollerCoaster(int maxSpeed, float bumpsPerSpeed, std::string liftType) {
      this->setMaxSpeed(maxSpeed);
      this->setBumpsPerSecond(bumpsPerSpeed);
      this->setLiftType(liftType);
    }    

    ~SuspendedRollerCoaster() {}

    float comfortScore() override {
      float score = BaseRollerCoaster::comfortScore();
      if (mLiftType == LiftType::CABLE) {
        score += 0.5;
      } else if (mLiftType == LiftType::LAUNCHED) {
        score += 0.1;
      }
      return score;
    }

    float overallScore() override {
      return mScaleFactor * mMaxSpeed * this->comfortScore();
    }
};


/*


vector<vector<string>> input = {
  {"Wooden", "4", "2", "Chain"},         // Expected: 2.0
  {"Steel", "20", "0", "Cable"},         // Expected: 10.0
  {"Suspended", "2", "0.5", "Cable"},    // Expected: 1.5
  {"Suspended", "2", "0.5", "Chain"},    // Expected: 1.0
  {"Suspended", "2", "0.5", "Launched"}, // Expected: 1.1
};

*/

int main() {
  BaseRollerCoaster* coasterType;
  for(auto& entry : input) {
    int maxSpeed = atoi(entry[1].c_str());
    float bumpsPerSpeed = atof(entry[2].c_str());
    std::string liftType = entry[3]; 
    if (getEnumCoasterType(entry[0]) == RollerCoasterType::WOODEN) {
      coasterType = new WoodenRollerCoaster(maxSpeed, bumpsPerSpeed, liftType);
    } else if (getEnumCoasterType(entry[0]) == RollerCoasterType::STEEL) {
      coasterType = new SteelRollerCoaster(maxSpeed, bumpsPerSpeed, liftType);
    } else if (getEnumCoasterType(entry[0]) == RollerCoasterType::SUSPENDED) {
      coasterType = new SuspendedRollerCoaster(maxSpeed, bumpsPerSpeed, liftType);
    }
    std::cout << "Comfort score : " << coasterType->comfortScore() << std::endl;
    std::cout << "OVerall score : " << coasterType->overallScore() << std::endl;

  }
}