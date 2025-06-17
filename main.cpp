// #include "mainwindow.h"
#include <QApplication>
#include <QDir>
#include <converter/imageconverter.h>
#include "converter/fontconverter.h"
#include "simulator/simulatortoolswindow.h"
#include <QDebug>

void search(){
    QString dirPath="D:/project/chibi/creator/game";
    QDir dir(dirPath);
    QFileInfoList fileInfoList = dir.entryInfoList();
    QFile file_a("D:/project/chibi/creator/game/fonts/allgb.txt");
    file_a.open(QFile::WriteOnly);
    QString s="";
    foreach (auto fileInfo, fileInfoList) {
        if(fileInfo.isFile()){
            qDebug()<<fileInfo.absoluteFilePath();
        }else if(fileInfo.isDir()&&fileInfo.fileName()!="."&&fileInfo.fileName()!=".."&&fileInfo.baseName()!="image"&&fileInfo.baseName()!="audio"&&fileInfo.baseName()!="fonts"){
            QDir c_dir(fileInfo.absoluteFilePath());
            QFileInfoList c_fileInfoList = c_dir.entryInfoList();
            foreach (auto c_fileInfo, c_fileInfoList) {
                if(c_fileInfo.isFile()){
                    QFile file(c_fileInfo.absoluteFilePath());
                    file.open(QFile::ReadOnly);
                    for(auto cha:QString(file.readAll())){
                        ushort uni = cha.unicode();
                        if(uni >= 0x4E00 && uni <= 0x9FA5){
                            s+=cha;
                        }
                    }
                    file.close();
                }
            }
        }
    }
    QString r;
    int length = s.length();
    for(int i=0;i<length;i++){
        if (!r.contains(s[i]))
        {
            r += s[i];
        }
    }
    qDebug()<<r;
    file_a.write(r.toUtf8());
    file_a.close();
}

bool clearDir(QString path)
{
    if (path.isEmpty())
    {
        return false;
    }

    QDir dir(path);
    if (!dir.exists())
    {
        return false;
    }

    dir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot); //设置过滤

    QFileInfoList fileList = dir.entryInfoList(); // 获取所有的文件信息

    //遍历文件信息
    foreach(QFileInfo file, fileList)
    {
        // 是文件，删除
        if (file.isFile())
        {
            file.dir().remove(file.fileName());
        }
        else // 递归删除
        {
            clearDir(file.absoluteFilePath());
            file.dir().rmdir(file.absoluteFilePath());
        }
    }

    return true;
}

void game(){
    QString dirPath="D:/project/chibi/creator/game/image";
    clearDir(dirPath);
    QString dirPath2="D:/project/chibi/creator/imgs";
    QDir dir(dirPath2);
    QFileInfoList fileInfoList = dir.entryInfoList(QStringList() << "*.png");
    foreach (auto fileInfo, fileInfoList) {
        QString target=fileInfo.absoluteFilePath();
        QString res=dirPath+"/"+fileInfo.fileName().mid(0,fileInfo.fileName().size()-4);
        ImageConverter::convert(target,res);
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // search();
    // FontConverter c;
    // c.Asc("D:/project/chibi/creator/game/fonts/asc");
    // c.Convert("D:/project/chibi/creator/game/fonts/allgb.txt");
    game();
    Simulator w;
    // MainWindow w;
    w.show();
    return a.exec();
}
