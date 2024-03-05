#include "modelviewer.h"

#include <iostream>

modelViewer::modelViewer(QWidget *parent)
    : QOpenGLWidget(
          parent)  // indexBuffer(QOpenGLBuffer::IndexBuffer), rotationAngle(0)
{
  background_color_ = QVector3D(0.5, 0.5, 0.5);
  position_x_ = 0;
  position_y_ = 0;
  position_z_ = 0;
  object_ = nullptr;

  connect(this, SIGNAL(SendNumOfPoints(size_t)), parent,
          SLOT(GetNumOfPoints(size_t)));
}

modelViewer::~modelViewer() { this->Clear3DObject_(); }

void modelViewer::Clear3DObject_() { delete object_; }

void modelViewer::initializeGL() {
  initializeOpenGLFunctions();
  view_matrix_.setToIdentity();
  view_matrix_.translate(0, -0.2, -1);

  glEnable(GL_DEPTH_BUFFER_BIT);
  InitShaders();
}

void modelViewer::resizeGL(int w, int h) {
  aspect_ = w / (float)h;
  //  aspect = 0;
  //  m_projectionMatrix.setToIdentity();  // делаем матрицу единичной
  // перспектива видимая область = 45, соотношение сторон, потом видимая область
  // от 0.1 до 100
  ChangeProjection(0);
}

void modelViewer::paintGL() {
  glClearColor(background_color_[0], background_color_[1], background_color_[2],
               1.0);  // чистим окно и делаем его чёрным
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  QMatrix4x4 modelMatrix;
  modelMatrix.setToIdentity();

  m_program_.bind();
  m_program_.setUniformValue("u_projectionMatrix", m_projection_matrix_);
  m_program_.setUniformValue("u_viewMatrix", view_matrix_);
  if (filepath_.isEmpty() == 0) {
    object_->Draw(&m_program_, context()->functions());
  }
}

void modelViewer::InitShaders() {
  if (!m_program_.addShaderFromSourceFile(QOpenGLShader::Vertex,
                                          "://vshader.vsh")) {
    qDebug() << "Vertex shader didn't compile";
  }

  if (!m_program_.addShaderFromSourceFile(QOpenGLShader::Fragment,
                                          "://fshader.fsh")) {
    qDebug() << "Fragment shader didn't compile";
  }
  if (!m_program_.link()) {
    qDebug() << "Shader linking has failed";
  }
}

void modelViewer::InitModel() {
  if (filepath_.isEmpty() != true) {
    this->Clear3DObject_();
    S21ViewerController new_data;
    try {
      new_data.ReadFileController(filepath_.toStdString());
      object_ = new SimpleObject3D(new_data);
      emit SendNumOfPoints(new_data.GetVertexesNumController());
    } catch (...) {
      QMessageBox::warning(this, "Error", "Invalid filepath");
    }
  }
}
//------------------------------------------------------
// Функции с мышкой
//------------------------------------------------------

void modelViewer::mousePressEvent(QMouseEvent *event) {
  if (event->buttons() == Qt::LeftButton) {
    mouse_position_ = QVector2D(event->pos());
  }
  event->accept();
}

void modelViewer::mouseMoveEvent(QMouseEvent *event) {
  if (event->buttons() != Qt::LeftButton) {
    return;
  }
  QVector2D diff = QVector2D(event->pos()) - mouse_position_;
  mouse_position_ = QVector2D(event->pos());

  float angle = diff.length() / 2;

  QVector3D axis = QVector3D(diff.y(), diff.x(), 0);

  m_rotation_ = QQuaternion::fromAxisAndAngle(axis, angle);

  RotateModel();
  update();
}

void modelViewer::wheelEvent(QWheelEvent *event) {
  QPoint numDegrees = event->angleDelta() / 5;

  if (numDegrees.y() > 0) {
    view_matrix_.scale(1.05, 1.05, 1.05);  // fix
  } else if (numDegrees.y() < 0) {
    view_matrix_.scale(0.95, 0.95, 0.95);  // fix
  }
  update();
}

void modelViewer::closeEvent(QCloseEvent *event) {
  delete event;
  exit(0);
}

void modelViewer::RotateModel() {
  view_matrix_.rotate(m_rotation_);
  update();
}

void modelViewer::GetFilepath(QString file) {
  filepath_ = file;
  InitModel();
  update();
}

void modelViewer::GetObjColor(QVector3D color) {
  if (filepath_.isEmpty() != true) {
    object_->SetObjColor(color);
    update();
  }
}

void modelViewer::SetBackgroundColor(QVector3D color) {
  background_color_ = color;
  update();
}

void modelViewer::GetPointColor(QVector3D color) {
  if (filepath_.isEmpty() != true) {
    object_->SetPointColor(color);
    update();
  }
}

void modelViewer::GetLineType(QString type) {
  if (filepath_.isEmpty() != true) {
    object_->SetLineType(type);
    update();
  }
}

void modelViewer::GetPointType(QString type) {
  if (filepath_.isEmpty() != true) {
    object_->SetPointType(type);
    update();
  }
}

void modelViewer::GetObjWidth(float width, float size) {
  if (filepath_.isEmpty() != true) {
    object_->SetObjWidth(width, size);
    update();
  }
}

void modelViewer::ChangeXCoordinate(int value) {
  view_matrix_.translate(-position_x_, 0, 0);
  position_x_ = (float)value / 100;
  view_matrix_.translate(position_x_, 0, 0);
  update();
}

void modelViewer::ChangeYCoordinate(int value) {
  view_matrix_.translate(0, -position_y_, 0);
  position_y_ = (float)value / 100;
  view_matrix_.translate(0, position_y_, 0);
  update();
}

void modelViewer::ChangeZCoordinate(int value) {
  view_matrix_.translate(0, 0, -position_z_);
  position_z_ = (float)value / 100;
  view_matrix_.translate(0, 0, position_z_);
  update();
}

void modelViewer::ChangeProjection(int condition) {
  m_projection_matrix_.setToIdentity();
  if (condition == 0) {
    m_projection_matrix_.perspective(45, aspect_, 0.1f, 100.0f);

  } else {
    m_projection_matrix_.ortho(-1.0f * aspect_, 1.0 * aspect_, -1.0f, 1.0f,
                               0.1f, 10.0f);
  }
  update();
}
