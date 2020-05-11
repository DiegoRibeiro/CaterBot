#ifndef CATERMODULE_H
#define CATERMODULE_H

#include<Windows.h>
#include <QString>

class CaterModule
{
public:
    CaterModule(QString name);
    char* getPath();
    SIZE_T getLength();

private:
    char path[MAX_PATH];
    SIZE_T length;
    QString name;
};

#endif // CATERMODULE_H
