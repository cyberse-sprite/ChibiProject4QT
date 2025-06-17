#include "attributewidget.h"
#include "ui_attributewidget.h"

AttributeWidget::AttributeWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AttributeWidget)
{
    ui->setupUi(this);
}

AttributeWidget::~AttributeWidget()
{
    delete ui;
}
