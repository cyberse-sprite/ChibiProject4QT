#include "imageconverter.h"
#include <QImage>
#include <QFile>
#include <QDebug>
#include <cstdint>
#include <QFileInfo>

uint16_t RGB888To565(int R,int G,int B){
    uint16_t color=((R&0xf8)<<8)+((G&0xfc)<<3)+((B&0xf8)>>3);
    return color;
}

QRect ImageConverter::clip_alpha(QImage image){
    QList<QImage> images;
    // 识别有效矩形区域
    int row = image.width();
    int col = image.height();
    int roi_up = row;
    int roi_down = 0;
    int roi_left = col;
    int roi_right = 0;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            auto c=image.pixelColor(j,i);
            if (c.alpha() > 0)
            {
                if (j < roi_left)roi_left = j;
                if (j > roi_right)roi_right = j;
                if (i < roi_up)roi_up = i;
                if (i > roi_down)roi_down = i;
            }
        }
    }
    int w = roi_right - roi_left+1;
    int h = roi_down - roi_up+1;
    return QRect(roi_left,roi_up,w,h);
}

void ImageConverter::convert(QString source, QString target)
{
    // qDebug()<<source;
    QFileInfo source_file(source);
    QStringList list=source_file.baseName().split("_");
    QImage source_image=QImage(source);
    QList<QImage> images;
    if(list.at(0)=="scene"||list.at(0)=="icon"||list.at(0)=="shadow"){
        images<<clip(source_image,source_image.width()/source_image.height(),1);
    }else if(list.at(0)=="part"){
        images<<clip(source_image,3,3);
    }else{
        images.push_back(source_image);
    }
    int i=0;
    for(QImage img:images){
        QRect rect=ImageConverter::clip_alpha(img);
        QImage n_image=img.copy(rect);
        // qDebug()<<rect;
        Image b_image=ImageConverter::LoadImage565(n_image);
        b_image.x=rect.x();
        b_image.y=rect.y();
        b_image.w=img.width();
        b_image.h=img.height();
        // qDebug()<<b_image.x<<b_image.y<<b_image.w<<b_image.h<<b_image.dw<<b_image.dh;
        SaveBin(b_image,target);
        // n_image.save(target+"_"+QString::number(i)+".png");
        i++;
    }
}

QList<QImage> ImageConverter::clip(QImage image, int x, int y)
{
    QList<QImage> images;
    int w=image.width()/x;
    int h=image.height()/y;
    for(int j=0;j<y;j++){
        for(int i=0;i<x;i++){
            images.push_back(image.copy(i*w,j*h,w,h));
        }
    }
    return images;
}

Image ImageConverter::LoadImage565(QImage source)
{
    Image target=Image();
    target.dw=source.width();
    target.dh=source.height();
    int size=target.dw*target.dh;
    target.data=new uint16_t[size];
    target.alpha=new uint8_t[size];
    for(int j=0;j<target.dh;j++){
        for(int i=0;i<target.dw;i++){
            QColor color=source.pixelColor(i,j);
            uint16_t s=RGB888To565(color.red(),color.green(),color.blue());
            if(color.alpha()==0)s=0x07e0;
            int k=j*target.dw+i;
            target.data[k]=s;
            target.alpha[k]=color.alpha();
        }
    }
    target.x=0;
    target.y=0;
    target.w=target.dw;
    target.h=target.dh;
    target.type=0;
    return target;
}

Image ImageConverter::LoadBin(QString path)
{
    Image image=Image();
    QFile file=QFile(path);
    file.open(QIODevice::ReadOnly);
    QDataStream rd(&file);
    rd.setByteOrder(QDataStream::LittleEndian);
    rd>>image.x>>image.y>>image.w>>image.h>>image.dw>>image.dh>>image.type;
    int size=image.dw*image.dh;
    image.data=new uint16_t[size];
    image.alpha=new uint8_t[size];
    for(int j=0;j<image.dh;j++){
        for(int i=0;i<image.dw;i++){
            int k=j*image.dw+i;
            rd>>image.data[k];
        }
    }
    for(int j=0;j<image.dh;j++){
        for(int i=0;i<image.dw;i++){
            int k=j*image.dw+i;
            rd>>image.alpha[k];
        }
    }
    file.close();
    return image;
}

void ImageConverter::SaveBin(Image image, QString target)
{
    QFile file=QFile(target);
    file.open(QIODevice::WriteOnly|QIODevice::Append);
    QDataStream out(&file);
    out.setByteOrder(QDataStream::LittleEndian);
    out<<image.x<<image.y<<image.w<<image.h<<image.dw<<image.dh<<image.type;
    for(int j=0;j<image.dh;j++){
        for(int i=0;i<image.dw;i++){
            int k=j*image.dw+i;
            out<<image.data[k];
        }
    }
    for(int j=0;j<image.dh;j++){
        for(int i=0;i<image.dw;i++){
            int k=j*image.dw+i;
            out<<image.alpha[k];
        }
    }
    file.close();
}
