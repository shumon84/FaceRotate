#ifndef FACEPOSE_H
#define FACEPOSE_H

struct Rotate {
  float x; // 右が正
  float y; // 上が正
  float z; // 奥が正
};

//extern Rotate rotate; // 顔の回転角

bool LoadModel();
void GetFeature();
Rotate ReadRotate();

#endif
