#include "simulator.h"
#include "core/actuator.h"
#include "core/game.h"
#include "core/render.h"
#include "core/sprite/imagesprite.h"
#include "core/assets/imageassets.h"
#include <QPainter>
#include <QTimer>
#include <QKeyEvent>
#include <QFileDialog>

Game* GAME;

QColor RGB565To888(uint16_t c){
    unsigned int R = (c & 0xF800)>>8;
    unsigned int G = (c & 0x07E0)>>3;
    unsigned int B = (c & 0x001F)<<3;
    return QColor(R,G,B);
}

Simulator::Simulator(QWidget *parent)
    : QWidget{parent}
{
    ratio=2;
    // QString path="D:/project/chibi/creator/game";
    // QFileInfo info(path);
    // SimulatorAssets* a;
    // if(info.isDir()){
    //     a=new SimulatorAssets(path);
    // }else{
    //     path="./game";
    //     QFileInfo info(path);
    //     if(info.isDir()){
    //         a=new SimulatorAssets(path);
    //     }else{
    //         QFileDialog *fileDialog = new QFileDialog(this);
    //         fileDialog->setFileMode(QFileDialog::Directory);
    //         fileDialog->exec();
    //         auto selectDir = fileDialog->selectedFiles();
    //         a=new SimulatorAssets(selectDir.at(0));
    //     }
    // }
    GAME=new Game();
    // STAGE->pushChild(new ImageSprite(IMG->get("scene_astral_0"),"bg"));
    ACT->callScript("start","main");
    ACT->run();
    setFixedSize(RENDER->width*ratio,RENDER->width*ratio);
    QTimer* timer=new QTimer(this);
    connect(timer,&QTimer::timeout,this,&Simulator::Fresh);
    timer->start(100);
}

void Simulator::ButtonA()
{
    ACT->Trigger("ButtonA");
}

void Simulator::ButtonB()
{
    ACT->Trigger("ButtonB");
}

void Simulator::ButtonC()
{
    ACT->Trigger("ButtonC");
}

void Simulator::Screenshot()
{

}

void Simulator::Fresh()
{
    STAGE->Fresh();
    RENDER->fresh();
    ACT->Fresh();
    update();
}

void Simulator::Save()
{
    GAME->save();
}

void Simulator::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    for(int j=0;j<RENDER->height;j++){
        for(int i=0;i<RENDER->width;i++){
            uint16_t color=RENDER->canvas[j*RENDER->width+i];
            painter.setBrush(RGB565To888(color));
            painter.drawRect(i*ratio, j*ratio, ratio, ratio);
        }
    }
}

void Simulator::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_A){
        ButtonA();}
    else if(event->key()==Qt::Key_S){
        ButtonB();}
    else if(event->key()==Qt::Key_D){
        ButtonC();}
    else if(event->key()==Qt::Key_W){
        Screenshot();
    }else if(event->key()==Qt::Key_Q){
        Save();
    }else if(event->key()==Qt::Key_V){
        ACT->next();
    }

}
