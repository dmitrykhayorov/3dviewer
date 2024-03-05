#ifndef SIMPLEOBJECT3D_H
#define SIMPLEOBJECT3D_H

#include <QMatrix4x4>
#include <QOpenGLBuffer>
#include <QVector3D>

#include "../controller/s21_controller.h"

class QOpenGLTexture;
class QOpenGLFunctions;
class QOpenGLShaderProgram;

class SimpleObject3D {
 public:
  SimpleObject3D(S21ViewerController &controller_with_data);
  ~SimpleObject3D();
  void Draw(QOpenGLShaderProgram *program, QOpenGLFunctions *functions);
  void SetObjColor(QVector3D color);
  void SetObjWidth(float width, float size);
  void SetPointColor(QVector3D color);
  void SetLineType(QString type);
  void SetPointType(QString type);

 private:
  void InitModel_(std::vector<point> points);
  void InitIndex_(std::vector<int> polygons);

  void DrawPoints_(QOpenGLShaderProgram *program, QOpenGLFunctions *functions);
  void DrawModel_(QOpenGLShaderProgram *program, QOpenGLFunctions *functions);

  QOpenGLBuffer vertex_buffer_;
  QOpenGLBuffer index_buffer_;
  QMatrix4x4 m_model_matrix_;
  QString filepath_;

  QString line_type_;
  QString point_type_;

  float line_width_;
  float point_size_;

  QVector3D point_color_;
  QVector3D obj_color_;
};

#endif  // SIMPLEOBJECT3D_H
