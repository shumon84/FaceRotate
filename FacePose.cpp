#include <opencv2/opencv.hpp>
#include <dlib/opencv.h>
#include <opencv2/highgui/highgui.hpp>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/gui_widgets.h>
#include <vector>
#include "FacePose.h"

#define PI 3.141592

using namespace dlib;
using namespace std;

extern cv::VideoCapture cap;

// 特徴点集合
std::vector< cv::Point2d > feature(6);

// 3次元モデル
std::vector< cv::Point3d > base(6);

// 顔検出モデル
frontal_face_detector detector;

// 姿勢推定モデル
shape_predictor pose_model;

// 理想カメラモデル
double focal_length;
cv::Point2d cent=cv::Point2d(0,0);
cv::Mat camera_matrix;
cv::Mat dist_coeffs;

Rotate r={};

bool LoadModel() {
  try {
    // 顔検出モデルを読み込む
    detector = get_frontal_face_detector();

    // 姿勢推定モデルを読み込む
    // 実行ファイルと同じ場所にshumon_deep_learning.datを置いておく
    deserialize("shumon_deep_learning.dat") >> pose_model;

    // 3次元モデル
    base[0] = cv::Point3d(0.0f, 0.0f, 0.0f); // 鼻先
    base[1] = cv::Point3d(0.0f, -330.0f, -65.0f); // 顎
    base[2] = cv::Point3d(-225.0f, 170.0f, -135.0f); // 左目尻
    base[3] = cv::Point3d(225.0f, 170.0f, -135.0f); // 右目尻
    base[4] = cv::Point3d(-150.0f, -150.0f, -125.0f); // 口左端
    base[5] = cv::Point3d(150.0f, -150.0f, -125.0f); // 口右端

    return true;
  }
  catch (...) {
    return false;
  }
}

void GetFeature() {
  cv::Mat temp;
  if(!cap.read(temp)) {
    return;
  }
  // 理想カメラモデル
  focal_length = temp.cols;
  cent = cv::Point2d(temp.cols / 2, temp.rows / 2);
  camera_matrix = (cv::Mat_<double>(3,3) << focal_length,
                   0,
                   cent.x,
                   0,
                   focal_length, cent.y,
                   0,
                   0,
                   1);
  dist_coeffs = cv::Mat::zeros(4,
                               1,
                               cv::DataType<double>::type); // 歪なし

  cv_image<bgr_pixel> cimg(temp);

  // 顔検出
  std::vector<rectangle> faces = detector(cimg);
  // 姿勢推定
  std::vector<full_object_detection> shapes;
  for (unsigned long i = 0; i < faces.size(); ++i) {
    shapes.push_back(pose_model(cimg, faces[i]));
  }

  if(faces.size() != 0) {
    // 鼻先
    feature[0] = cv::Point2d(shapes[0].part(34).x(),
                             shapes[0].part(34).y());
    // 顎
    feature[1] = cv::Point2d(shapes[0].part(9).x(),
                             shapes[0].part(9).y());
    // 左目尻
    feature[2] = cv::Point2d(shapes[0].part(46).x(),
                             shapes[0].part(46).y());
    // 右目尻
    feature[3] = cv::Point2d(shapes[0].part(37).x(),
                             shapes[0].part(37).y());
    // 口左端
    feature[4] = cv::Point2d(shapes[0].part(55).x(),
                             shapes[0].part(55).y());
    // 口右端
    feature[5] = cv::Point2d(shapes[0].part(49).x(),
                             shapes[0].part(49).y());
 }
}

Rotate ReadRotate() {
  GetFeature();
  cv::Mat rotation_vector;
  cv::Mat translation_vector;
  cv::solvePnP(base, feature, camera_matrix, dist_coeffs, rotation_vector, translation_vector);
  cv::Mat rotation_matrix;
  cv::Rodrigues(rotation_vector, rotation_matrix);
  double threshold = 0.001;
  if(abs(rotation_matrix.at<double>(2, 1) - 1.0) < threshold) { // rotation_matrix(2,1) = sin(x) = 1の時
    r.x = PI / 2;
    r.y = 0;
    r.z = atan2(rotation_matrix.at<double>(1, 0), rotation_matrix.at<double>(0, 0));
  }
  else if(abs(rotation_matrix.at<double>(2, 1) + 1.0) < threshold) { // rotation_matrix(2,1) = sin(x) = -1の時
    r.x = - PI / 2;
    r.y = 0;
    r.z = atan2(rotation_matrix.at<double>(1, 0), rotation_matrix.at<double>(0, 0));
  }
  else {
    r.x = asin(rotation_matrix.at<double>(2, 1));
    r.y = atan2(-rotation_matrix.at<double>(2, 0), rotation_matrix.at<double>(2, 2));
    r.z = atan2(-rotation_matrix.at<double>(0, 1), rotation_matrix.at<double>(1, 1));
  }
return r;
}
