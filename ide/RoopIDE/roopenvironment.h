#ifndef ROOPENVIRONMENT_H
#define ROOPENVIRONMENT_H

#include <QMainWindow>
#include "roopsyntaxhighlighter.h"

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

private:
    Ui::RoopEnvironment *ui;
    int lastLinePosition;
    RoopSyntaxHighlighter *roopSyntaxHighlighter;
};

#endif // ROOPENVIRONMENT_H
