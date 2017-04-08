#ifndef MYDIALOG_H
#define MYDIALOG_H

#include <QDialog>

class QTextEdit;

class MyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MyDialog(QWidget *parent = 0);
    virtual ~MyDialog() {};

private:
    QTextEdit *sampleTextEdit;

private slots:
    void onImportButtonClicked();
    void onClearButtonClicked();
    void onTrainingButtonClicked();
    void criticalMessage(QString msg);
    void warningMessage(QString msg);
};

#endif // MYDIALOG_H
