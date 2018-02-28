#include<opencv2/opencv.hpp>
#include"FacePose.h"

cv::VideoCapture cap;

/**
 * @brief capにWebカメラを割り当てる
 *
 * @return 割り当てできたかどうか
 */
bool startUp() {
  // すでに割り当てられている場合はfalseを返す
  //if(cap != NULL) {
  //  return false;
  //}
  cap=cv::VideoCapture(0); // メモリを割り当て
 
  // 割り当てに失敗した場合はfalseを返す
  if(!cap.isOpened()) {
    return false;
  }
  // 割り当てに成功した場合はtrueを返す
  return true;
}

/**
 * @brief capに割り当てたWebカメラを解放
 *
 * @return 解放できたかどうか
 */
bool shutDown() {
  // // まだ確保していない場合はfalseを返す
  // if(!cap.isOpened()) {
  //   return false;
  // }
  // delete cap;
  // cap = NULL; // 解放済みのアドレスにアクセスできないようにする
  // return true;
}

int main() {
  //// この2つは最初に呼ばないといけない////
  startUp();
  LoadModel();
  //////////////////////////////////////////

  while(1) {
    // この関数の戻り値が回転角
    Rotate r = ReadRotate();
    printf("%.2f %.2f %.2f\n",r.x,r.y,r.z);
  }

  //// 終了時に呼ばないといけない ////
  shutDown();
  ////////////////////////////////////
}
