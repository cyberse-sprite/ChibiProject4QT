#ifndef NODESWIDGET_H
#define NODESWIDGET_H

#include <QWidget>

namespace Ui {
class NodesWidget;
}

class NodesWidget : public QWidget
{
    Q_OBJECT

public:
    explicit NodesWidget(QWidget *parent = nullptr);
    ~NodesWidget();

private:
    Ui::NodesWidget *ui;
};

#endif // NODESWIDGET_H
