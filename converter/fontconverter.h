#ifndef FONTCONVERTER_H
#define FONTCONVERTER_H
#include "core/font.h"
#include <QFont>

class FontConverter
{
    QFont font;
public:
    FontConverter();
    QImage singleChar(QChar c);
    PixChar charData(QImage image);
    void Convert(QString path);
    void Asc(QString path);
    void test(QString path);
    void printChar(std::string s);
};

#endif // FONTCONVERTER_H
