#ifndef ATTRIBUTEWIDGET_H
#define ATTRIBUTEWIDGET_H

#include <QWidget>

namespace Ui {
class AttributeWidget;
}

class AttributeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AttributeWidget(QWidget *parent = nullptr);
    ~AttributeWidget();

private:
    Ui::AttributeWidget *ui;
};

#endif // ATTRIBUTEWIDGET_H
