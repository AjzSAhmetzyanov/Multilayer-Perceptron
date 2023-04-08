#include "view.h"

#include "ui_view.h"

view::view(QWidget *parent) : QMainWindow(parent), ui(new Ui::view) {
  ui->setupUi(this);
  ui->scene->setmainwindow(this);
}

view::~view() {
  delete ui;
  delete controller;
}

void view::on_get_trainfile_clicked() {
  QString fileName = QFileDialog::getOpenFileName(
      this, tr("Выбрать файл"), "",
      tr("Все файлы (*.*);;Изображения (*.png *.xpm *.jpg)"));
  train_file = fileName.toStdString();
}

void view::on_get_testfile_clicked() {
  QString fileName = QFileDialog::getOpenFileName(
      this, tr("Выбрать файл"), "",
      tr("Все файлы (*.*);;Изображения (*.png *.xpm *.jpg)"));
  test_file = fileName.toStdString();
}

void view::on_get_savefile_clicked() {
  QString fileName = QFileDialog::getOpenFileName(
      this, tr("Выбрать файл"), "",
      tr("Все файлы (*.*);;Изображения (*.png *.xpm *.jpg)"));
  save_file = fileName.toStdString();
}

void view::on_start_test_clicked() {
  if (ui->start_test->isChecked() && !test_file.empty() && !save_file.empty()) {
    std::pair<double, double> res = controller->start_testing(
        test_file, save_file, ui->layer_count->value());
    ui->accuracy->setText(QString::number(res.first));
    ui->test_time->setText(QString::number(res.second));
  }
  QMessageBox::critical(this, "", "Choose to test and save file");
}

void view::on_start_train_clicked() {
  if (ui->start_train->isChecked() && !train_file.empty() &&
      !save_file.empty()) {
    std::pair<double, double> res = controller->start_training(
        train_file, save_file, ui->learning_rate->value(),
        ui->epoch_count->value(), ui->layer_count->value());
    ui->train_mse->setText(QString::number(res.first));
    ui->train_time->setText(QString::number(res.second));
  } else {
    QMessageBox::critical(this, "", "Choose to train and save file");
  }
}

void view::on_start_ready_clicked() {
  //    QString fileName = QFileDialog::getOpenFileName(this, tr("Выбрать
  //    файл"), "", tr("Все файлы (*.*);;Изображения (*.png *.xpm *.jpg)"));
  //    qDebug() << "Выбранный файл: " << fileName;
  ready_weights_ = true;
  if (!ui->scene->get_pixels().empty()) {
    QString text;
    for (double d : ui->scene->get_pixels()) {
      text += QString::number(d) + " ";
    }
    int predict_ = controller->ready_weigth(ui->scene->get_pixels());
    ui->predict->setText(QString(static_cast<char>('A' + predict_)));
  } else {
    QMessageBox::critical(this, "", "Draw a word");
  }
}

void view::on_start_cross_clicked() {
  if (ui->start_cross->isChecked() && !train_file.empty()) {
    std::pair<double, double> res = controller->cross_val(
        ui->layer_count->value(), train_file, ui->count_cross->value(),
        ui->epoch_count->value(), ui->learning_rate->value());
    ui->cross_accur->setText(QString::number(res.first));
    ui->cross_accur->setText(QString::number(res.second));
  } else {
    QMessageBox::critical(this, "", "Choose to train and save file");
  }
}
