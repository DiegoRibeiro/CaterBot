#include "catermodule.h"

CaterModule::CaterModule(QString name)
{
    this->name = name;
    this->length = GetFullPathNameA(name.toStdString().c_str(), MAX_PATH, this->path, nullptr);
}

char* CaterModule::getPath() {
    return this->path;
}

SIZE_T CaterModule::getLength() {
    return this->length;
}


