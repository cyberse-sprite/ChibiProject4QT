#include "nodeswidget.h"
#include "ui_nodeswidget.h"

NodesWidget::NodesWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::NodesWidget)
{
    ui->setupUi(this);
}

NodesWidget::~NodesWidget()
{
    delete ui;
}
