#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFileDialog>
#include <QMainWindow>
#include <QSettings>
#include <QTimer>
#include <QtOpenGLWidgets>

#include "../gifLib/src/gifimage/qgifimage.h"
#include "modelviewer.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

 public slots:
  void GetNumOfPoints(size_t points_num);

 signals:
  void SendFilepath(QString filepath);
  void WidthAndSizeChanged(float width, float size);

 private slots:
  void on_change_model_button_clicked();
  void on_pushButton_apply_color_clicked();
  void on_pushButton_apply_width_clicked();

  void on_btnScreenShot_clicked();

  void on_btnRecordGif_clicked();
  void RecordSlot();
  void LoadSettings();
  void SaveSettings();

  void on_comboBox_line_currentTextChanged(QString arg1);
  void on_comboBox_point_currentTextChanged(QString arg1);

  void on_horizontalSlider_X_valueChanged(int value);
  void on_horizontalSlider_Y_valueChanged(int value);
  void on_horizontalSlider_Z_valueChanged(int value);

  void on_pushButton_load_clicked();

  void on_checkBox_change_view_stateChanged(int arg1);

 private:
  modelViewer* modelWidget;
  QTimer* timer;
  Ui::MainWindow* ui;
  QGifImage* gifka;
  QTimer* timer_gif_;
  QString gif_file_path_;
  QSettings* settings_;

  QVector3D model_color_;
  QVector3D background_color_;
  QVector3D point_color_;

  QString file_name_;

  QString point_type_;
  QString line_type_;

  float red_;
  float green_;
  float blue_;

  float width_;
  float size_;

  int x_;
  int y_;
  int z_;
};
#endif  // MAINWINDOW_H
