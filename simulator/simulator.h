#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <QWidget>

class Simulator : public QWidget
{
    Q_OBJECT
    void paintEvent(QPaintEvent *event);
    void keyReleaseEvent(QKeyEvent* event);
public:
    explicit Simulator(QWidget *parent = nullptr);
    int ratio;
    void ButtonA();
    void ButtonB();
    void ButtonC();
    void Screenshot();
    void Fresh();
    void Save();

signals:
};

#endif // SIMULATOR_H
