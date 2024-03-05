#ifndef VIEWGL_H
#define VIEWER_H

#include <QOpenGLFunctions>
#include <QOpenGlWidgets>

class ViewerGL : public QOpenGlWidget, protected QOpenGlFunctions {
 public:
  Viewer(QWidget* parent = nullptr);
  ~Viewer();

 private:
  void initializeGL();
  void resizeGL(int w, int h);
  void paintGL();
}

#endif