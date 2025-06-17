#include "fontconverter.h"
#include <QFile>
#include <QLabel>
#include <QImage>
#include <QPainter>
#include <QFontDatabase>
#include <bitset>

FontConverter::FontConverter() {
    QString path="D:/project/font/Cubic-11-main/fonts/ttf/Cubic_11.ttf";
    // 加载自定义字体文件
    int fontId = QFontDatabase::addApplicationFont(path);
    // 获取字体族名称
    QString fontName = QFontDatabase::applicationFontFamilies(fontId).at(0);
    font=QFont(fontName);
}

QImage FontConverter::singleChar(QChar c)
{
    QImage image(12,12,QImage::Format_Mono);
    image.fill(QColor(Qt::black));
    QPainter painter(&image);
    font.setPixelSize(12);
    painter.setFont(font);
    painter.drawText(0,10,c);
    return image;
}

PixChar FontConverter::charData(QImage image)
{
    PixChar c=PixChar();
    for(int j=0;j<image.height();j++){
        for(int i=0;i<image.width();i++){
            int t=image.pixelIndex(i,j);
            c.content[i+j*image.width()]=!t;
        }
    }
    return c;
}

void FontConverter::Convert(QString path)
{
    QFile file(path);
    file.open(QIODevice::ReadOnly);
    QFile fileSave(path.sliced(0,path.size()-4));
    fileSave.open(QIODevice::WriteOnly);
    QFontMetrics fm(font);
    QString str=file.readAll();
    QDataStream s(&fileSave);
    int gg=0;
    for(auto c:str){
        //写入图素
        PixChar pix=charData(singleChar(c));
        pix.width=fm.horizontalAdvance(c);
        auto chars=pix.getString();
        for(auto c:chars){
            s<<c;
        }
        gg++;
    }
    file.close();
    fileSave.close();
}

void FontConverter::Asc(QString path)
{
    QFile fileSave(path);
    fileSave.open(QIODevice::WriteOnly);
    QFontMetrics fm(font);
    QDataStream s(&fileSave);
    for(int i=0;i<128;i++){
        //写入图素
        QChar c=QChar((char)i);
        PixChar pix=charData(singleChar(c));
        pix.width=fm.horizontalAdvance(c);
        auto chars=pix.getString();
        for(auto c:chars){
            s<<c;
        }
        s<<pix.width;
    }
    fileSave.close();
}

void FontConverter::test(QString path){
    Convert(path);
}

void FontConverter::printChar(std::string s)
{
    int n=0;
    while(n<s.size()){
        std::string news="";
        std::string sub=s.substr(n,12);
        for(auto c:sub){
            if(c=='0')news+=" ";
            else news+="1";
        }
        n+=12;
    }
}
