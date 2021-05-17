#include <cassert>
#include <stdexcept>

// TODO: Define class Pyramid
class Pyramid {
// public class members
  public:
    // constructor
    Pyramid(int length, int width, int height) {
        SetLenght(length);
        SetWidth(width);
        SetHeight(height);
    }
    
    // accessors
    int Length() { return length_; }
    int Width() { return width_; }
    int Height() { return height_; }

// mutators
    void SetLenght(int length) {
        if (length > 0) { length_ = length; }
        else  throw "Invalid length";
    }

    void SetWidth(int width) {
        if (width > 0) { width_ = width; }
        else  throw "Invalid width";
    }

    void SetHeight(int height) {
        if (height > 0) { height_ = height; }
        else  throw "Invalid height";
    }

// public Volume() function
    int Volume(){
        return (length_ * width_ * height_) / 3;
    }

// private class members
  private:
    int length_;
    int width_;
    int height_;
};

// Test
int main() {
  Pyramid pyramid(4, 5, 6);
  assert(pyramid.Length() == 4);
  assert(pyramid.Width() == 5);
  assert(pyramid.Height() == 6);
  assert(pyramid.Volume() == 40);

  bool caught{false};
  try {
    Pyramid invalid(-1, 2, 3);
  } catch (...) {
    caught = true;
  }
  assert(caught);
}
