#include "viewgl.h"

ViewerGL::ViewerGL(QWidget *parent) : QOpenGLWidget(parent) {}

ViewerGL::~ViewerGL();

void Viewer::initializeGL() {
  initializeOpenGLFunctions();
  glEnable(GL_DEPT_TEST);
}

void Viewer::resizeGL(int w, int h) { glWiewport(0, 0, w, h); }

void Viewer::paintGL() {
  // all magic will be here
}
