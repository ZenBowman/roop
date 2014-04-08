#ifndef ROOPENVIRONMENT_H
#define ROOPENVIRONMENT_H

#include <QMainWindow>

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

private:
    Ui::RoopEnvironment *ui;
    int lastLinePosition;
};

#endif // ROOPENVIRONMENT_H
