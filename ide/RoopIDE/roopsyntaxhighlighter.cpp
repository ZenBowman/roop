#include "roopsyntaxhighlighter.h"
#include "syntaxkeywords.h"

RoopSyntaxHighlighter::RoopSyntaxHighlighter(QObject *parent) :
    QSyntaxHighlighter(parent)
{
}

RoopSyntaxHighlighter::RoopSyntaxHighlighter(QTextDocument *parent) :
    QSyntaxHighlighter(parent)
{
}

void RoopSyntaxHighlighter::highlightBlock(const QString &text){
    QTextCharFormat myClassFormat;
    myClassFormat.setFontWeight(QFont::Bold);
    myClassFormat.setForeground(Qt::darkMagenta);
    QString pattern = SYNTAX_KEYWORDS;

    QRegExp expression(pattern);
    int index = text.indexOf(expression);
    qDebug(text.toStdString().c_str());
    while (index >= 0) {
        int length = expression.matchedLength();
        setFormat(index, length, myClassFormat);
        index = text.indexOf(expression, index + length);
    }
}
