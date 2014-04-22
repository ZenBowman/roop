#include "roopcommon.h"
#include "unistd.h"
#include "errno.h"
#include <sys/stat.h>
#include <fstream>

#include <QDebug>
#include <QFile>

namespace Roop {

    std::string getRoopConfigDir() {
        const char* _home = getenv("HOME");
        std::string home = std::string(_home);
        home += "/.roop";
        return home;
    }

    void createRoopDirectoryIfNotExist() {
        struct stat buffer;
        std::string roopConfigDir = getRoopConfigDir();
        int dirStat = stat(roopConfigDir.c_str(), &buffer);
        if (dirStat == -1) {
            if (mkdir(roopConfigDir.c_str(), S_IRWXU|S_IRGRP|S_IXGRP) != 0) {
                qDebug() << "Failed to create roop directory";
            }
        }
    }

    const char* getLastLoadedFileName() {
        return (getRoopConfigDir() + "/last_loaded_filename").c_str();
    }

    QString getLastLoadedFile() {
        std::ifstream reader(getLastLoadedFileName());
        std::string lastFileName;
        reader >> lastFileName;
        reader.close();
        return QString::fromStdString(lastFileName);
    }

    void setLastLoadedFile(QString fileName){
        createRoopDirectoryIfNotExist();
        const char* lastLoadedFileName = getLastLoadedFileName();
        std::ofstream writer(lastLoadedFileName);
        writer << fileName.toStdString();
        writer.close();
    }

    int saveToFile(QString fileName, QString text) {
        if (fileName != "") {
            QFile file(fileName);
            if (!file.open(QIODevice::WriteOnly)) {
                return -1;
            }
            else {
                QTextStream stream(&file);
                stream << text;
                stream.flush();
                file.close();
            }
        }
        return 0;
    }

}
