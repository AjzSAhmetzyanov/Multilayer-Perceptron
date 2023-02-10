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

class paintscene : public QGraphicsScene
{

    Q_OBJECT

public:
    explicit paintscene(QObject *parent = 0);
    ~paintscene();

private:
    QPointF  previousPoint;      // Координаты предыдущей точки
    QImage image_points {};
    QPoint points {};
private:
    // Для рисования используем события мыши
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

};
#endif // PAINTSCENE_H
