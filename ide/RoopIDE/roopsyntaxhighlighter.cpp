#include "roopsyntaxhighlighter.h"

RoopSyntaxHighlighter::RoopSyntaxHighlighter(QObject *parent) :
    QSyntaxHighlighter(parent)
{
}

RoopSyntaxHighlighter::RoopSyntaxHighlighter(QTextDocument *parent) :
    QSyntaxHighlighter(parent)
{
}

void RoopSyntaxHighlighter::highlightBlock(const QString &text){
    qDebug("called");
    QTextCharFormat myClassFormat;
    myClassFormat.setFontWeight(QFont::Bold);
    myClassFormat.setForeground(Qt::darkMagenta);
    QString pattern = "set";

    QRegExp expression(pattern);
    int index = text.indexOf(expression);
    qDebug(text.toStdString().c_str());
    while (index >= 0) {
        int length = expression.matchedLength();
        setFormat(index, length, myClassFormat);
        index = text.indexOf(expression, index + length);
    }
}
