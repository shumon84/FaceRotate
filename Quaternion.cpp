#include"Quaternion.h"
#include<limits>

Quaternion::Quaternion() {
  w = x = y = z = 0;
}

Quaternion::Quaternion(float w, float x, float y, float z) {
  this -> w = w;
  this -> x = x;
  this -> y = y;
  this -> z = z;
}

Quaternion::Quaternion(Quaternion &other) {
  w = other.w;
  x = other.x;
  y = other.y;
  z = other.z;
}

Quaternion::~Quaternion() {
}
