#ifndef ROOPSYNTAXHIGHLIGHTER_H
#define ROOPSYNTAXHIGHLIGHTER_H

#include <QSyntaxHighlighter>

class RoopSyntaxHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT
public:
    explicit RoopSyntaxHighlighter(QObject *parent = 0);
    explicit RoopSyntaxHighlighter(QTextDocument *parent=0);
    void highlightBlock(const QString &text);

signals:

public slots:

};

#endif // ROOPSYNTAXHIGHLIGHTER_H
