#include "view.h"
#include "ui_view.h"

view::view(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::view)
{
    ui->setupUi(this);
    ui->scene->setmainwindow(this);

}

view::~view()
{
    delete ui;
}

