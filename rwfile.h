#ifndef RWFILE_H
#define RWFILE_H
#include <QString>


class RWFile
{
public:
    RWFile();
public:
    static void readClassFile(QString classesFile, QVector<QString> &classes);
};

#endif // RWFILE_H
