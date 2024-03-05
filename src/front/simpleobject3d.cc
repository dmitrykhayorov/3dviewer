#include "simpleobject3d.h"

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <iostream>

SimpleObject3D::SimpleObject3D(S21ViewerController &controller_with_data)
    : index_buffer_(QOpenGLBuffer::IndexBuffer) {
  point_type_ = "NONE";
  line_type_ = "SOLID";
  point_color_ = QVector3D(1, 1, 1);
  obj_color_ = QVector3D(0, 0, 0);
  point_size_ = 1;
  line_width_ = 1;
  InitModel_(controller_with_data.GetVectorWithVertexesController());
  InitIndex_(controller_with_data.GetVectorWithPolygonsController());
};

void SimpleObject3D::InitModel_(std::vector<point> points) {
  vertex_buffer_.create();
  vertex_buffer_.bind();
  vertex_buffer_.allocate(points.data(), points.size() * sizeof(point));
  vertex_buffer_.release();

  m_model_matrix_.setToIdentity();
}

void SimpleObject3D::InitIndex_(std::vector<int> polygons) {
  index_buffer_.create();
  index_buffer_.bind();
  index_buffer_.allocate(polygons.data(), polygons.size() * sizeof(int));
  index_buffer_.release();
}

SimpleObject3D::~SimpleObject3D() {
  if (vertex_buffer_.isCreated()) {
    vertex_buffer_.destroy();
  }
  if (index_buffer_.isCreated()) {
    index_buffer_.destroy();
  }
}

void SimpleObject3D::Draw(QOpenGLShaderProgram *program,
                          QOpenGLFunctions *functions) {
  program->setUniformValue("u_modelMatrix", m_model_matrix_);

  vertex_buffer_.bind();

  int vertLoc = program->attributeLocation("a_position");
  program->enableAttributeArray(vertLoc);
  program->setAttributeBuffer(vertLoc, GL_FLOAT, 0, 3, sizeof(point));
  index_buffer_.bind();
  DrawModel_(program, functions);
  if (point_type_ != "NONE") {
    DrawPoints_(program, functions);
  }
  vertex_buffer_.release();
  index_buffer_.release();
}

void SimpleObject3D::DrawPoints_(QOpenGLShaderProgram *program,
                                 QOpenGLFunctions *functions) {
  if (point_type_ == "CIRCLE") {
    glEnable(GL_POINT_SMOOTH);
  }
  glPointSize(point_size_);
  QVector4D f_color(point_color_, 1.0f);
  program->setUniformValue("color", f_color);
  functions->glDrawElements(GL_POINTS, index_buffer_.size(), GL_UNSIGNED_INT,
                            0);
  if (point_type_ == "CIRCLE") {
    glDisable(GL_POINT_SMOOTH);
  }
}

void SimpleObject3D::DrawModel_(QOpenGLShaderProgram *program,
                                QOpenGLFunctions *functions) {
  if (line_type_ == "DASHED") {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(3, 0x00ff);
  }
  glLineWidth(line_width_);
  QVector4D f_color(obj_color_, 1.0f);
  program->setUniformValue("color", f_color);
  functions->glDrawElements(GL_LINES, index_buffer_.size(), GL_UNSIGNED_INT, 0);
  if (line_type_ == "DASHED") {
    glDisable(GL_LINE_STIPPLE);
  }
}

void SimpleObject3D::SetObjColor(QVector3D color) { obj_color_ = color; }

void SimpleObject3D::SetObjWidth(float width, float size) {
  line_width_ = width;
  point_size_ = size;
}

void SimpleObject3D::SetPointColor(QVector3D color) { point_color_ = color; }

void SimpleObject3D::SetLineType(QString type) { line_type_ = type; }

void SimpleObject3D::SetPointType(QString type) { point_type_ = type; }
