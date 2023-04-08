#ifndef RENDER_SCENE_H
#define RENDER_SCENE_H

#include <QPaintEvent>
#include <QPainter>
#include <QPoint>
#include <QWidget>

#include "view.h"

class render_scene : public QWidget {
  Q_OBJECT

 public:
  QPoint last_point{};
  bool draw;
  QImage image_{};
  QImage resized_image_{};
  std::vector<double> v_pixels{};
  double lineWidth = 40;
  int pixelSize = 28;
  view *mainwindow{};

 public:
  explicit render_scene(QWidget *parent = nullptr);
  void setmainwindow(view *window);
  void clearImage();
  ~render_scene() override = default;
  ;

 private:
  void paintEvent(QPaintEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;
  void lineTo(const QPoint &newPoint);
  const std::vector<double> &VectorFromImage();

 public:
  std::vector<double> get_pixels();

 signals:
};

#endif  // RENDER_SCENE_H
