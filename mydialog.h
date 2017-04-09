#ifndef MYDIALOG_H
#define MYDIALOG_H

#include <QDialog>
#include "jhbayes.h"

class QTextEdit;
class QLabel;
class QLineEdit;

class MyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MyDialog(QWidget *parent = 0);
    virtual ~MyDialog() {};

private:
    QTextEdit *sampleTextEdit;
    QLabel *trainingResultLabel;
    QLabel *predictResultLabel;
    QLineEdit *predictLineEdit;
    JHBayes *bayes;

private slots:
    void onImportButtonClicked();
    void onClearButtonClicked();
    void onTrainingButtonClicked();
    void onTrainingClearButtonClicked();
    void criticalMessage(QString msg);
    void warningMessage(QString msg);
};

#endif // MYDIALOG_H
