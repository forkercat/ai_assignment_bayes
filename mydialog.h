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
    QTextEdit *sampleTextEdit; // 样本输入框
    QLabel *trainingResultLabel; // 训练结果标签
    QLabel *predictResultLabel; // 预测结果便签
    QLineEdit *predictLineEdit; // 预测输入框
    JHBayes *bayes;

private slots:
    // 按钮事件
    void onImportButtonClicked();
    void onClearButtonClicked();
    void onTrainingButtonClicked();
    void onTrainingClearButtonClicked();
    void onPredictButtonClicked();
    // 提醒框
    void criticalMessage(QString msg);
    void warningMessage(QString msg);
};

#endif // MYDIALOG_H
