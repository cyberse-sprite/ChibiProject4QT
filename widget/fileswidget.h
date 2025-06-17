#ifndef FILESWIDGET_H
#define FILESWIDGET_H

#include <QWidget>

namespace Ui {
class FilesWidget;
}

class FilesWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FilesWidget(QWidget *parent = nullptr);
    ~FilesWidget();

private:
    Ui::FilesWidget *ui;
};

#endif // FILESWIDGET_H
