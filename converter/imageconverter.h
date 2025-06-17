#ifndef IMAGECONVERTER_H
#define IMAGECONVERTER_H

#include <qcontainerfwd.h>
#include <core/data/image.h>
#include <Qimage>
class ImageConverter
{
public:
    static Image LoadImage565(QImage);
    static Image LoadBin(QString path);
    static void SaveBin(Image image,QString target);
    static QRect clip_alpha(QImage image);
    static void convert(QString,QString);
    static QList<QImage> clip(QImage,int,int);
};

#endif // IMAGECONVERTER_H
