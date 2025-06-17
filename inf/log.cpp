#include "log.h"
#include <QDebug>
ChibiLog::ChibiLog()
{

}

void ChibiLog::info(std::string content)
{
    qDebug()<<content;
}
