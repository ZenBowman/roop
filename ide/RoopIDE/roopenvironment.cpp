#include "roopenvironment.h"
#include "ui_roopenvironment.h"

RoopEnvironment::RoopEnvironment(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RoopEnvironment)
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
}
