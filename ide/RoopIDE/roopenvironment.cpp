#include "roopenvironment.h"
#include "ui_roopenvironment.h"
#include "stdlib.h"
#include <fstream>
#include <QTextBlock>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
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
    QSyntaxHighlighter *roopSyntaxHighlighter = new RoopSyntaxHighlighter(ui->roopEditor->document());
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

void RoopEnvironment::on_actionSave_As_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File As"), "",
                                                    tr("CVL files (*.cvl)"));
    if (fileName != "") {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
         // error message
        }
        else {
            QTextStream stream(&file);
            stream << ui->roopEditor->toPlainText();
            stream.flush();
            file.close();
        }
    }
}

void RoopEnvironment::on_actionLoad_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "",
        tr("CVL files (*.cvl)"));

    if (fileName != "") {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
            return;
        }
        QTextStream in(&file);
        ui->roopEditor->setText(in.readAll());
        file.close();
    }
}
