#include "roopenvironment.h"
#include "ui_roopenvironment.h"
#include "stdlib.h"
#include <fstream>
#include <QTextBlock>
#include <cstdio>
#include <unistd.h>


const std::string ROOP_EXECUTABLE = "/home/psamtani/development/roop/release/Roop";
const char* IMAGES_DIR = "/home/psamtani/development/roop/images";
const char* TEMP_FILE_NAME = "/tmp/roopedit-current.cvl";

RoopEnvironment::RoopEnvironment(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RoopEnvironment),
    lastLinePosition(0)
{
    ui->setupUi(this);
}

RoopEnvironment::~RoopEnvironment()
{
    delete ui;
}

void RoopEnvironment::on_roopEditor_textChanged()
{
}

void RoopEnvironment::on_roopEditor_cursorPositionChanged()
{
    const int lineNumber = ui->roopEditor->textCursor().blockNumber();
    if (lineNumber != lastLinePosition) {
        std::ofstream tempFileWriter(TEMP_FILE_NAME);
        lastLinePosition = lineNumber;
        for (int i=0; i<lineNumber; i++) {
            QTextBlock thisBlock = ui->roopEditor->document()->findBlockByLineNumber(i);
            qDebug(thisBlock.text().toStdString().c_str());
            tempFileWriter << thisBlock.text().toStdString() << std::endl;
        }
        tempFileWriter  << "(persist /tmp/roopimage.jpg)" << std::endl
                        << "(exit)" << std::endl;

        qDebug("Current working directory = %s", get_current_dir_name());

        tempFileWriter.close();
        char result[256];
        sprintf(result, "cd %s && %s %s", IMAGES_DIR, ROOP_EXECUTABLE.c_str(), TEMP_FILE_NAME);
        system(result);

        QPixmap* image = new QPixmap("/tmp/roopimage.jpg");
        QPixmap scaledImage = image->scaled(ui->displayImage->size());
        ui->displayImage->setPixmap(scaledImage);
        ui->displayImage->repaint();
    }
}
