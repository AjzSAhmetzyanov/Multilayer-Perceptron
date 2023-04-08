#ifndef VIEW_H
#define VIEW_H

#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>

#include "../Controller/controller.h"
//#include "render_scene.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class view;
}
QT_END_NAMESPACE

class view : public QMainWindow {
  Q_OBJECT

 public:
  view(QWidget *parent = nullptr);
  ~view();

 public:
  std::string train_file{};
  std::string test_file{};
  std::string save_file{};
  int epoch_{};
  int L{};
  double learning_rate_{};
  bool ready_weights_{};
  bool matrix_view{};
  bool graph_view{};

 private slots:

  void on_get_trainfile_clicked();

  void on_get_testfile_clicked();

  void on_get_savefile_clicked();

  void on_start_test_clicked();

  void on_start_train_clicked();

  void on_start_ready_clicked();

  void on_start_cross_clicked();

 private:
  Ui::view *ui;
  s21::Controller *controller = new s21::Controller;
};
#endif  // VIEW_H
