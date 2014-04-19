#include "roopenvironment.h"
#include "ui_roopenvironment.h"
#include "stdlib.h"
#include <fstream>
#include <QTextBlock>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QDataStream>
#include <QChar>
#include <QDebug>
#include <cstdio>
#include <unistd.h>
#include <sstream>
#include <iterator>
#include "roopconstants.h"
#include "syntaxkeywords.h"
#include "roopcommon.h"
#include <boost/algorithm/string/predicate.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/replace.hpp>

using namespace Roop;

RoopEnvironment::RoopEnvironment(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RoopEnvironment),
    lastLinePosition(0)
{
    ui->setupUi(this);
    QSyntaxHighlighter *roopSyntaxHighlighter = new RoopSyntaxHighlighter(ui->roopEditor->document());


    for (std::map<std::string, std::string>::iterator it=keywordMap.begin(); it!=keywordMap.end(); ++it) {
        std::string key = it->first;
        QString newString(key.c_str());
        operators.push_back(newString);
    }

    loadFile(getLastLoadedFile());

    saveShortCut = new QShortcut(QKeySequence(tr("Ctrl+S", "File|Save")), ui->roopEditor);
    saveShortCut->activated();
    QObject::connect(saveShortCut, SIGNAL(activated()), this, SLOT(saveCurrentFile()));
}

RoopEnvironment::~RoopEnvironment()
{
    if (saveShortCut != 0) {
        delete saveShortCut;
    }
    delete ui;
}

void RoopEnvironment::saveCurrentFile() {
    qDebug() << "Saving...";
}

void RoopEnvironment::filterOperatorsListBy(QString& lastCommand) {
    std::string lastCommandString = lastCommand.toStdString();
    boost::replace_all(lastCommandString, "(", "");
    ui->operatorsList->clear();
    for(size_t i=0; i<operators.size(); i++) {
        if (boost::starts_with(operators[i].toStdString(), lastCommandString)) {
            ui->operatorsList->addItem(operators[i] + QString("| Ctrl+") + QString::number(i));
        }
    }
}

void RoopEnvironment::on_roopEditor_textChanged()
{
    QTextCursor cursor = ui->roopEditor->textCursor();
    int currentCharacterPosition = cursor.position()-1;
    const int originalBlock = ui->roopEditor->document()->findBlock(currentCharacterPosition).blockNumber();
    QString lastCommand;
    int currentBlock;

    while (true) {
        if (currentCharacterPosition < 0) {
            break;
        }

        currentBlock = ui->roopEditor->document()->findBlock(currentCharacterPosition).blockNumber();
        if (currentBlock != originalBlock) {
            break;
        }

        QChar thisChar = ui->roopEditor->document()->characterAt(currentCharacterPosition);


        if (thisChar == ' ') {
            break;       
        } else {
            lastCommand.prepend(thisChar);
        }
        currentCharacterPosition--;
    }

    filterOperatorsListBy(lastCommand);
    qDebug() << "Last word = " << lastCommand;
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
        qDebug() << "Images directory = " << IMAGES_DIR.c_str();
        qDebug() << "Roop executable = " << ROOP_EXECUTABLE.c_str();
        sprintf(result, "cd %s && %s %s", IMAGES_DIR.c_str(), ROOP_EXECUTABLE.c_str(), TEMP_FILE_NAME);
        system(result);

        QPixmap* image = new QPixmap("/tmp/roopimage.jpg");
        QPixmap scaledImage = image->scaled(ui->displayImage->size());
        ui->displayImage->setPixmap(scaledImage);
        ui->displayImage->repaint();
    }
}

void RoopEnvironment::on_actionSave_As_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File As"), SCRIPTS_DIR.c_str(),
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

void RoopEnvironment::loadFile(const QString &fileName) {
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

void RoopEnvironment::on_actionLoad_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    SCRIPTS_DIR.c_str(),
                                                    tr("CVL files (*.cvl)"));

    loadFile(fileName);
    setLastLoadedFile(fileName);
}
