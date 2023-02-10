#include "view.h"
#include "ui_view.h"

view::view(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::view)
{
    ui->setupUi(this);
    scene = new paintscene();       // Инициализируем графическую сцену
    ui->graphicsView->setScene(scene);  // Устанавливаем графическую сцену

    timer = new QTimer();       // Инициализируем таймер
    connect(timer, &QTimer::timeout, this, &view::slotTimer);
    timer->start(100);          // Запускаем таймер
}

view::~view()
{
    delete ui;
    delete timer;
    delete scene;
}

void view::slotTimer()
{
    /* Переопределяем размеры графической сцены в зависимости
     * от размеров окна
     * */
    timer->stop();
    scene->setSceneRect(0,0, ui->graphicsView->width() - 30, ui->graphicsView->height() - 30);
}

void view::resizeEvent(QResizeEvent *event)
{
    timer->start(100);
    QWidget::resizeEvent(event);
}
