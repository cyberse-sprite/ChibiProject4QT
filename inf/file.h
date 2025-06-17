#ifndef FILE_H
#define FILE_H

#include <QFile>
#include <string>

class File
{
    QFile file;
public:
    bool open(std::string,std::string);
    std::string read(size_t);
    uint16_t readuint16_t();
    uint8_t readuint8_t();
    std::string readLine();
    void write(std::string);
    bool end();
    void close();
};

#endif // FILE_H
