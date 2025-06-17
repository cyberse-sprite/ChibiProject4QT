#include "simulatortoolswindow.h"
#include "ui_simulatortoolswindow.h"

SimulatorToolsWindow::SimulatorToolsWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SimulatorToolsWindow)
{
    ui->setupUi(this);
}

SimulatorToolsWindow::~SimulatorToolsWindow()
{
    delete ui;
}

void SimulatorToolsWindow::on_actionLeft_triggered()
{
    s.ButtonA();
}


void SimulatorToolsWindow::on_actionMiddle_triggered()
{
    s.ButtonB();
}


void SimulatorToolsWindow::on_actionRight_triggered()
{
    s.ButtonC();
}

