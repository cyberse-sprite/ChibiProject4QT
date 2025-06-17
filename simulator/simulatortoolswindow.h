#ifndef SIMULATORTOOLSWINDOW_H
#define SIMULATORTOOLSWINDOW_H

#include "simulator/simulator.h"
#include <QMainWindow>

namespace Ui {
class SimulatorToolsWindow;
}

class SimulatorToolsWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SimulatorToolsWindow(QWidget *parent = nullptr);
    ~SimulatorToolsWindow();
private slots:
    void on_actionLeft_triggered();

    void on_actionMiddle_triggered();

    void on_actionRight_triggered();

private:
    Ui::SimulatorToolsWindow *ui;
    Simulator s;
};

#endif // SIMULATORTOOLSWINDOW_H
