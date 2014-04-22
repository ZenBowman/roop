#ifndef ROOPCOMMON_H
#define ROOPCOMMON_H

#include <QString>

namespace Roop {

    void setLastLoadedFile(QString fileName);
    QString getLastLoadedFile();
    int saveToFile(QString fileName, QString text);
}

#endif // ROOPCOMMON_H
