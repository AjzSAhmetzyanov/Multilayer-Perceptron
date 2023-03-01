#include "render_scene.h"
#include <QDebug>

render_scene::render_scene(QWidget *parent)
    : QWidget{parent},
    draw(false),
    image_(QSize(400, 400), QImage::Format_RGB16) {
    clearImage();
}

void render_scene::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    QRect rect(event->rect());
    painter.drawImage(rect, image_, rect);
}

void render_scene::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
       last_point = event->pos();
       draw = true;
     } else {
        clearImage();
     }
}

void render_scene::mouseMoveEvent(QMouseEvent* event) {
    if ((event->buttons() & Qt::LeftButton) && draw) {
       lineTo(event->pos());
     }
}

void render_scene::mouseReleaseEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton && draw) {
        lineTo(event->pos());
        draw = false;
      }
    qDebug() << "this";
    VectorFromImage();
    for (auto i : v_pixels)
    qDebug() << i;
 }

void render_scene::lineTo(const QPoint& newPoint) {
    QPainter painter(&image_);
      painter.setPen(
          QPen(Qt::black, lineWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
      painter.setRenderHint(QPainter::SmoothPixmapTransform);
      painter.setRenderHint(QPainter::Antialiasing);
      painter.drawLine(last_point, newPoint);

      int rad = (lineWidth / 2) + 2;
      update(QRect(last_point, newPoint)
                 .normalized()
                 .adjusted(-rad, -rad, +rad, +rad));
      last_point = newPoint;
      qDebug() << "line_to";
}

const std::vector<double>& render_scene::VectorFromImage() {
  if (!v_pixels.empty()) {
    v_pixels.clear();
  }
  resized_image_ = image_.scaled(pixelSize, pixelSize);
  for (int i = 0; i < pixelSize; ++i) {
    for (int j = 0; j < pixelSize; ++j) {
      v_pixels.emplace_back(
          static_cast<double>(resized_image_.pixelColor(i, j).blackF()));
    }
  }
  qDebug() << "vector";
  return v_pixels;
}

void render_scene::clearImage() {
  image_.fill(qRgb(0xFF, 0xFF, 0xFF));
  update();
}

void render_scene::setmainwindow(view* window) {
  mainwindow = window;
}
