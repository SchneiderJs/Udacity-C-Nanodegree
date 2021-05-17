#include <cassert>
#include <cmath>
#include <stdexcept> 

// TODO: Define class Sphere
class Sphere {
 public:
  // Constructor
  Sphere(int radius) {
      SetRadius(radius);
  }

  void SetRadius(int radius) {
      if (radius > 0) { radius_ = radius; }
      else throw "Invalid argument: radius";
  }

  // Accessors
  int Volume() { 
      return (4.0/3.0) * M_PI * std::pow(radius_, 3); 
  }

  static int Volume(double radius){
      return (4.0/3.0) * M_PI * std::pow(radius, 3); 
  }

  int Radius() {
      return radius_;
  }

 private:
  // Private members
  int radius_;
};

// Test
int main(void) {
  Sphere sphere(5);
  assert(sphere.Radius() == 5); 
  assert(abs(sphere.Volume() - 523.6) < 1);
  assert(abs(sphere.Volume(5.0) - 523.6) < 1);
}

