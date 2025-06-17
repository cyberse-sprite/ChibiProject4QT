#include "fileswidget.h"
#include "ui_fileswidget.h"

FilesWidget::FilesWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FilesWidget)
{
    ui->setupUi(this);
}

FilesWidget::~FilesWidget()
{
    delete ui;
}
