#include "mainwindow.h"

#include <QDialogButtonBox>
#include <iostream>

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  modelWidget = new modelViewer(this);
  settings_ = new QSettings();
  ui->gridLayout->addWidget((QWidget *)modelWidget);
  timer_gif_ = new QTimer(this);
  connect(this, SIGNAL(SendFilepath(QString)), (QWidget *)modelWidget,
          SLOT(GetFilepath(QString)));
  connect(timer_gif_, SIGNAL(timeout()), this, SLOT(RecordSlot()));
  connect(this, SIGNAL(WidthAndSizeChanged(float, float)),
          (QWidget *)modelWidget, SLOT(GetObjWidth(float, float)));
}

MainWindow::~MainWindow() {
  SaveSettings();
  delete ui;
}

void MainWindow::on_pushButton_load_clicked() { LoadSettings(); }

void MainWindow::LoadSettings() {
  background_color_ =
      settings_->value("backgroundColor", QVector3D(1.0f, 1.0f, 0.0f))
          .value<QVector3D>();
  modelWidget->SetBackgroundColor(background_color_);

  if (file_name_.isEmpty() != true) {
    file_name_ = settings_->value("modelPath", file_name_).value<QString>();
    emit SendFilepath(file_name_);
    ui->lineEdit_filename_to_write->setText(file_name_);
  }

  model_color_ = settings_->value("modelColor", QVector3D(1.0f, 1.0f, 1.0f))
                     .value<QVector3D>();
  modelWidget->GetObjColor(model_color_);

  point_color_ = settings_->value("pointColor", QVector3D(1.0f, 1.0f, 1.0f))
                     .value<QVector3D>();
  modelWidget->GetPointColor(point_color_);

  width_ = settings_->value("modelWidth", width_).value<float>();
  size_ = settings_->value("modelSize", size_).value<float>();
  emit WidthAndSizeChanged(width_, size_);
  ui->spinBox_obj_W->setValue(width_);
  ui->spinBox_obj_P->setValue(size_);

  line_type_ = settings_->value("modelPointType", line_type_).value<QString>();
  modelWidget->GetLineType(line_type_);

  point_type_ =
      settings_->value("modelPointType", point_type_).value<QString>();
  modelWidget->GetPointType(point_type_);

  x_ = settings_->value("modelX", x_).value<int>();
  if (x_ >= -20 && x_ <= 20) {
    modelWidget->ChangeXCoordinate(x_);
  }

  y_ = settings_->value("modelY", y_).value<int>();
  if (y_ >= -20 && y_ <= 20) {
    modelWidget->ChangeYCoordinate(y_);
  }

  z_ = settings_->value("modelZ", z_).value<int>();
  modelWidget->ChangeZCoordinate(z_);
  if (z_ >= -20 && z_ <= 20) {
    modelWidget->ChangeZCoordinate(z_);
  }
}

void MainWindow::SaveSettings() {
  settings_->setValue("backgroundColor", background_color_);
  settings_->setValue("modelColor", model_color_);
  settings_->setValue("pointColor", point_color_);
  settings_->setValue("modelPath", file_name_);
  settings_->setValue("modelWidth", width_);
  settings_->setValue("modelSize", size_);
  settings_->setValue("modelPointType", point_type_);
  settings_->setValue("modelLineType", line_type_);
  settings_->setValue("modelX", x_);
  settings_->setValue("modelY", y_);
  settings_->setValue("modelZ", z_);
}

void MainWindow::on_change_model_button_clicked() {
  file_name_ = QFileDialog::getOpenFileName(this, tr("Выберите модель"), "/",
                                            tr("Object Files (*.obj)"), 0,
                                            QFileDialog::DontUseNativeDialog);
  emit SendFilepath(file_name_);
  ui->lineEdit_filename_to_write->setText(file_name_);
}

void MainWindow::on_pushButton_apply_color_clicked() {
  red_ = (float)ui->spinBox_obj_R->value();
  green_ = (float)ui->spinBox_obj_G->value();
  blue_ = (float)ui->spinBox_obj_B->value();

  if (ui->radioButton_obj->isChecked()) {
    model_color_ = QVector3D(red_, green_, blue_);
    modelWidget->GetObjColor(model_color_);
  } else if (ui->radioButton_back->isChecked()) {
    background_color_ = QVector3D(red_, green_, blue_);
    modelWidget->SetBackgroundColor(background_color_);
  } else {
    point_color_ = QVector3D(red_, green_, blue_);
    modelWidget->GetPointColor(point_color_);
  }
}

void MainWindow::on_pushButton_apply_width_clicked() {
  width_ = ui->spinBox_obj_W->value();
  size_ = ui->spinBox_obj_P->value();
  emit WidthAndSizeChanged(width_, size_);
}

void MainWindow::on_btnScreenShot_clicked() {
  QImage imageOfModel = modelWidget->grabFramebuffer();
  if (ui->comboBox->currentIndex() == 0) {
    QString saveLocation = QFileDialog::getSaveFileName(
        this, "Set filename and location to save", "/",
        tr("JPEG files (*.jpg)"), 0, QFileDialog::DontUseNativeDialog);
    imageOfModel.save(saveLocation, "JPEG");
  } else if (ui->comboBox->currentIndex() == 1) {
    QString saveLocation = QFileDialog::getSaveFileName(
        this, "Set filename and location to save", "/", tr("BMP files (*.bmp)"),
        0, QFileDialog::DontUseNativeDialog);
    imageOfModel.save(saveLocation, "BMP");
  }
}

void MainWindow::on_btnRecordGif_clicked() {
  gifka = new QGifImage(/*QSize(640, 480)*/);
  gif_file_path_ = QFileDialog::getSaveFileName(
      this, "Specify where to save a file", "/", tr("GIF files (*.gif)"), 0,
      QFileDialog::DontUseNativeDialog);
  timer_gif_->start(100);
}

void MainWindow::RecordSlot() {
  QImage modelImage = modelWidget->grabFramebuffer();
  //    modelImage = modelImage.scaled(640, 480);
  gifka->addFrame(modelImage);
  if (gifka->frameCount() == 50) {
    timer_gif_->stop();
    gifka->setDefaultDelay(100);
    bool saveRes = gifka->save(gif_file_path_);
    QString saveAlert;
    if (saveRes) {
      saveAlert = "File saved at" + gif_file_path_;
    } else {
      saveAlert = "Gif wasn't saved, something went wrong(";
    }
    qDebug() << saveAlert;
    delete gifka;
    gifka = NULL;
  }
  qDebug() << "recordSlot";
}

void MainWindow::on_comboBox_line_currentTextChanged(QString arg1) {
  line_type_ = arg1;
  modelWidget->GetLineType(arg1);
}

void MainWindow::on_comboBox_point_currentTextChanged(QString arg1) {
  point_type_ = arg1;
  modelWidget->GetPointType(arg1);
}

void MainWindow::on_horizontalSlider_X_valueChanged(int value) {
  x_ = value;
  modelWidget->ChangeXCoordinate(value);
}

void MainWindow::on_horizontalSlider_Y_valueChanged(int value) {
  y_ = value;
  modelWidget->ChangeYCoordinate(value);
}

void MainWindow::on_horizontalSlider_Z_valueChanged(int value) {
  z_ = value;
  modelWidget->ChangeZCoordinate(value);
}

void MainWindow::on_checkBox_change_view_stateChanged(int arg1) {
  qInfo() << arg1;
  modelWidget->ChangeProjection(arg1);
}

void MainWindow::GetNumOfPoints(size_t points_num) {
  QString str = QString::number(points_num);
  ui->lineEdit_points_num_to_write->setText(str);
}
