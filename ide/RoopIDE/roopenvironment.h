#ifndef ROOPENVIRONMENT_H
#define ROOPENVIRONMENT_H

#include <QMainWindow>
#include "roopsyntaxhighlighter.h"
#include <vector>
#include <QShortcut>

namespace Ui {
class RoopEnvironment;
}

class RoopEnvironment : public QMainWindow
{
    Q_OBJECT

public:
    explicit RoopEnvironment(QWidget *parent = 0);
    ~RoopEnvironment();

private slots:
    void on_roopEditor_textChanged();

    void on_roopEditor_cursorPositionChanged();

    void on_actionSave_As_triggered();

    void on_actionLoad_triggered();

    void saveCurrentFile();

private:
    Ui::RoopEnvironment *ui;
    int lastLinePosition;
    RoopSyntaxHighlighter *roopSyntaxHighlighter;
    std::vector<QString> operators;
    std::vector<QString> images;

    void filterOperatorsListBy(QString &currentCommand, QString &lastCommand);
    void loadFile(const QString& fileName);
    void operatorsAsListWithFilter(std::vector<QString> someVector, std::string beginning);

    QShortcut *saveShortCut;
};

#endif // ROOPENVIRONMENT_H
