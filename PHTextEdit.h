#include <QtGui>
#include <QDebug>

class PHTextEdit : public QTextEdit
{
    Q_PROPERTY(QString placeholderText READ placeholderText WRITE setPlaceholderText)
    
public:

PHTextEdit(QWidget *parent = 0) : QTextEdit(parent) {}

void setPlaceholderText(QString text)
{
    placeholderText = text;
    if(toPlainText().isEmpty())
    {
        setHtml(QString("<font color=\"#b4b4b4\">%1</font>").arg(placeholderText));
    }
}

protected:

void focusInEvent(QFocusEvent *e)
{
    if (!placeholderText.isNull())
    {
        QString t = toPlainText();
        if (t.isEmpty() || t == placeholderText)
        {
            clear();
        }
    }
    QTextEdit::focusInEvent(e);
}

void focusOutEvent(QFocusEvent *e)
{
    if (!placeholderText.isNull())
    {
        if (toPlainText().isEmpty())
        {
            setHtml(QString("<font color=\"#b4b4b4\">%1</font>").arg(placeholderText));
        }
    }
    QTextEdit::focusOutEvent(e);
}

private:
    QString placeholderText;
};