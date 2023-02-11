#ifndef PAINTSCENE_H
#define PAINTSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QTimer>
#include <QDebug>
#include <QImage>
#include <QColor>
#include <vector>
#include <QPainter>
#include <QPaintEvent>
#include <QBuffer>

class paintscene : public QGraphicsScene
{

    Q_OBJECT

public:
    explicit paintscene(QObject *parent = 0);
    ~paintscene();

public:
    auto VectorFromImage() -> const std::vector<double>&;

private:
    QPointF  previousPoint;      // Координаты предыдущей точки
    QImage image_ {};
    QImage image;
    QImage resized_image_ {};
    QPoint points {};
    std::vector<double> v_pixels {};

private:
    // Для рисования используем события мыши
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    static constexpr double lineWidth = 40;
    static constexpr int    pixelSize = 28;

};
#endif // PAINTSCENE_H
