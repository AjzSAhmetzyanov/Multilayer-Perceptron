#include "render_scene.h"

render_scene::render_scene(QWidget *parent)
    : QWidget{parent},
      draw(false),
      image_(QSize(400, 400), QImage::Format_RGB16) {
  clearImage();
}

void render_scene::paintEvent(QPaintEvent *event) {
  QPainter painter(this);
  QRect rect(event->rect());
  painter.drawImage(rect, image_, rect);
}

void render_scene::mousePressEvent(QMouseEvent *event) {
  if (event->button() == Qt::LeftButton) {
    last_point = event->pos();
    draw = true;
  } else {
    clearImage();
  }
}

void render_scene::mouseMoveEvent(QMouseEvent *event) {
  if ((event->buttons() & Qt::LeftButton) && draw) {
    lineTo(event->pos());
  }
}

void render_scene::mouseReleaseEvent(QMouseEvent *event) {
  if (event->button() == Qt::LeftButton && draw) {
    lineTo(event->pos());
    draw = false;
  }
  VectorFromImage();
}

void render_scene::lineTo(const QPoint &newPoint) {
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
}

const std::vector<double> &render_scene::VectorFromImage() {
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
  return v_pixels;
}

std::vector<double> render_scene::get_pixels() {
  //    std::vector<double> rotatedVector(pixelSize * pixelSize);
  //    for (int x = 0; x < pixelSize; x++) {
  //        for (int y = 0; y < pixelSize; y++) {
  //            int index = x * pixelSize + y;
  //            int rotatedIndex = (pixelSize - 1 - x) + y * pixelSize;
  //            rotatedVector[rotatedIndex] = v_pixels[index];
  //        }
  //    }
  //    return rotatedVector;
  //    int n = v_pixels.size(); // количество элементов вектора

  //    for (int i = 0; i < n / 2; ++i) {
  //        std::swap(v_pixels[i], v_pixels[n - i - 1]); // меняем местами
  //        элементы в верхней и нижней половинах вектора
  //    }
  return v_pixels;
}

void render_scene::clearImage() {
  image_.fill(qRgb(0xFF, 0xFF, 0xFF));
  update();
}

void render_scene::setmainwindow(view *window) { mainwindow = window; }
