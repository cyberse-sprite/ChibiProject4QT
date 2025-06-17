#include "file.h"
#include <QDebug>
#include <QtEndian>

QString this_path_file="D:/project/chibi/creator/game/";

bool File::open(std::string name, std::string mode)
{
    file.setFileName(this_path_file+QString::fromStdString(name));
    if(!file.exists())return false;
    if(mode=="w"){
        file.open(QFile::WriteOnly);
    }else{
        file.open(QFile::ReadOnly);
    }
    return true;
}

std::string File::read(size_t size)
{
    return file.read(size).toStdString();
}

uint16_t File::readuint16_t()
{
    auto some=file.read(2);
    return qFromLittleEndian<qint16_le>(some);
}

uint8_t File::readuint8_t()
{
    auto some=file.read(1);
    return qFromLittleEndian<qint16_le>(some);
}

std::string File::readLine()
{
    return QString(file.readLine()).trimmed().toStdString();
}

void File::write(std::string str)
{
    file.write(str.c_str());
}

bool File::end()
{
    return file.atEnd();
}

void File::close()
{
    file.close();
}
