#ifndef QUATERNION_H
#define QUATERNION_H

/**
 * @brief クォータニオンクラス
 *
 * クォータニオン(四元数)を扱う
 * Unityとの間にこのクラスは使わない
 */
class Quaternion {
private:
  // プライベートメンバ変数
  float w;
  float x;
  float y;
  float z;
public:
  // コンストラクタ、デストラクタ
  Quaternion();
  Quaternion(float w, float x, float y, float z);
  Quaternion(Quaternion &other);
  virtual ~Quaternion();

public:
  // アクセッサ
  void W(float w);
  void X(float x);
  void Y(float y);
  void Z(float z);
  float W();
  float X();
  float Y();
  float Z();
};

inline void Quaternion::W(float w) {
  this->w=w;
}
inline void Quaternion::X(float x) {
  this->x=x;
}
inline void Quaternion::Y(float y) {
  this->y=y;
}
inline void Quaternion::Z(float z) {
  this->z=z;
}
inline float Quaternion::W() {
  return w;
}
inline float Quaternion::X() {
  return x;
}
inline float Quaternion::Y() {
  return y;
}
inline float Quaternion::Z() {
  return z;
}

#endif
