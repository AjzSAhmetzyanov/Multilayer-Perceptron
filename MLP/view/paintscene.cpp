#include "paintscene.h"

paintscene::paintscene(QObject *parent) : QGraphicsScene(parent)
{

}

paintscene::~paintscene()
{

}

void paintscene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    // При нажатии кнопки мыши отрисовываем эллипс
    addEllipse(event->scenePos().x() - 5,
               event->scenePos().y() - 5,
               35,
               35,
               QPen(Qt::NoPen),
               QBrush(Qt::black));
    // Сохраняем координаты точки нажатия
    previousPoint = event->scenePos();
//    v_points.push_back();

}

void paintscene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    // Отрисовываем линии с использованием предыдущей координаты
    addLine(previousPoint.x(),
            previousPoint.y(),
            event->scenePos().x(),
            event->scenePos().y(),
            QPen(Qt::black,35,Qt::SolidLine,Qt::RoundCap));
    // Обновляем данные о предыдущей координате
    previousPoint = event->scenePos();
}

auto paintscene::VectorFromImage() -> const std::vector<double>& {
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
