#ifndef MODELVIEWER_H
#define MODELVIEWER_H

#include <QMatrix4x4>
#include <QMessageBox>
#include <QMouseEvent>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLWidget>
#include <QTimer>
#include <QVector3D>
#include <QWidget>

#include "../controller/s21_controller.h"
#include "simpleobject3d.h"

class modelViewer : public QOpenGLWidget, protected QOpenGLFunctions {
  Q_OBJECT

 public:
  explicit modelViewer(QWidget *parent = nullptr);
  ~modelViewer();
  void GetObjColor(QVector3D color);
  void SetBackgroundColor(QVector3D color);
  void GetPointColor(QVector3D color);
  void GetLineType(QString type);
  void GetPointType(QString type);
  void ChangeXCoordinate(int value);
  void ChangeYCoordinate(int value);
  void ChangeZCoordinate(int value);
  void ChangeProjection(int statue);

 public slots:
  void GetFilepath(QString filename);
  void GetObjWidth(float width, float size);

 signals:
  void rotate(int rotationAngle);
  void SendLineWidth(float width, float size);
  void SendNumOfPoints(size_t points_num);

 protected:
  void initializeGL() override;
  void paintGL() override;
  void resizeGL(int w, int h) override;
  void InitShaders();
  void InitModel();

 private:
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void wheelEvent(QWheelEvent *event) override;
  void closeEvent(QCloseEvent *event) override;

  void Clear3DObject_();

  SimpleObject3D *object_;
  float aspect_;
  int condition_;
  float position_x_;
  float position_y_;
  float position_z_;

  // Square position and size
  QMatrix4x4 m_projection_matrix_;
  QOpenGLShaderProgram m_program_;
  QMatrix4x4 view_matrix_;
  int rotation_angle_;
  QVector2D mouse_position_;
  QQuaternion m_rotation_;
  QString filepath_;

  QVector3D background_color_;

 private slots:
  void RotateModel();
};

#endif  // MODELVIEWER_H
