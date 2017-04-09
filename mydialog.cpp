#include "mydialog.h"

#include <QtGui>
#include <string>
#include <iostream>
#include <set>
#include <vector>

#include "sample.h"
#include "jhparser.h"

using namespace std;

// 定义些常量

// 宽度
static const int LINE_EDIT_WIDTH = 195;
static const int TRAINING_LABEL_WIDTH = 400;
static const int PREDICT_LABEL_WIDTH = 400;
// 高度
static const int LINE_EDIT_HEIGHT = 30;
static const int NORMAL_BUTTON_HEIGHT = 40;
static const int TEXT_EDIT_HEIGHT = 140;
static const int TRAINING_LABEL_HEIGHT = 140;
static const int TRAINING_LABEL_INDENT = 3;
static const int PREDICT_LABEL_HEIGHT = 57;
static const int PREDICT_LABEL_INDENT = 3;
static const int LABEL_HEIGHT = 25;
static const int MAIN_LAYOUT_MARGIN = 10;
// 字体
static const int SMALL_LABEL_FONT_SIZE = 14;
static const int LABEL_FONT_SIZE = 16;
static const int BUTTON_FONT_SIZE = 16;
static const int BUTTON_BIG_FONT_SIZE = 18;
static const int TEXT_FONT_SIZE = 14;

MyDialog::MyDialog(QWidget *parent) : QDialog(parent)
{
    // 窗口
    this->setWindowTitle("俊皓的朴素贝叶斯分类器");

    // 图片
    QPixmap *introImage = new QPixmap;
    introImage->load(":/images/thomas_bayes1.jpg");

    QLabel *imageLabel = new QLabel;
    imageLabel->setPixmap(*introImage);
    imageLabel->setScaledContents(true);
    imageLabel->resize(imageLabel->pixmap()->size());

    // All Labels & TextEdit
    QFont *labelFont = new QFont;
    labelFont->setPointSize(LABEL_FONT_SIZE);
    QFont *smallLabelFont = new QFont;
    smallLabelFont->setPointSize(SMALL_LABEL_FONT_SIZE);

    QLabel *sampleLabel = new QLabel("训练集 : (可粘贴)");
    sampleLabel->setFont(*labelFont);
    sampleLabel->setFixedHeight(LABEL_HEIGHT);

    QLabel *trainingLabel = new QLabel("训练结果 :");
    trainingLabel->setFont(*labelFont);
    trainingLabel->setFixedHeight(LABEL_HEIGHT);

    QLabel *predictLabel = new QLabel("预测 / 分类 :");
    predictLabel->setFont(*labelFont);
    predictLabel->setFixedHeight(LABEL_HEIGHT);

    QLabel *endingLabel = new QLabel("ai_assignment_bayes © 2017 Junhao (2014101027)");
    endingLabel->setFont(*smallLabelFont);
    endingLabel->setFixedHeight(SMALL_LABEL_FONT_SIZE);
    endingLabel->setAlignment(Qt::AlignHCenter);

    // TextEdit
    QFont *textFont = new QFont;
    textFont->setPointSize(TEXT_FONT_SIZE);

    sampleTextEdit = new QTextEdit;
    sampleTextEdit->setFixedHeight(TEXT_EDIT_HEIGHT);
    sampleTextEdit->setFont(*textFont);
    sampleTextEdit->setText("请用矩阵形式; 特征由空格隔开; 样本由换行分开; 类别在第一列.");

    // TrainingResultLabel
    QScrollArea *trainingScrollArea = new QScrollArea;
    trainingScrollArea->setFixedWidth(TRAINING_LABEL_WIDTH);
    trainingScrollArea->setFixedHeight(TRAINING_LABEL_HEIGHT);
    trainingResultLabel = new QLabel;
    trainingResultLabel->setScaledContents(true);
    trainingResultLabel->setFont(*textFont);
    trainingResultLabel->setIndent(TRAINING_LABEL_INDENT);
    trainingResultLabel->setText("<空>");
    trainingScrollArea->setWidget(trainingResultLabel);

    // PredictLineEdit
    predictLineEdit = new QLineEdit;
    predictLineEdit->setFixedWidth(LINE_EDIT_WIDTH);
    predictLineEdit->setFixedHeight(LINE_EDIT_HEIGHT);
    predictLineEdit->setFont(*textFont);
    predictLineEdit->setPlaceholderText("特征值1 特征值2 ... 特征值n");

    // PredictResultLabel
    QScrollArea *predictScrollArea = new QScrollArea;
    predictScrollArea->setFixedWidth(PREDICT_LABEL_WIDTH);
    predictScrollArea->setFixedHeight(PREDICT_LABEL_HEIGHT);
    predictResultLabel = new QLabel;
    predictResultLabel->setScaledContents(true);
    predictResultLabel->setFont(*textFont);
    predictResultLabel->setIndent(PREDICT_LABEL_INDENT);
    predictResultLabel->setText("<空>");
    predictScrollArea->setWidget(predictResultLabel);

    // All Buttons
    QFont *btnFont = new QFont;
    btnFont->setPointSize(BUTTON_FONT_SIZE);
    QFont *btnBigFont = new QFont;
    btnBigFont->setPointSize(BUTTON_BIG_FONT_SIZE);

    QPushButton *sampleImportBtn = new QPushButton("导入txt");
    sampleImportBtn->setFont(*btnFont);
    sampleImportBtn->setFixedHeight(NORMAL_BUTTON_HEIGHT);

    QPushButton *sampleClearBtn = new QPushButton("清空数据");
    sampleClearBtn->setFont(*btnFont);
    sampleClearBtn->setFixedHeight(NORMAL_BUTTON_HEIGHT);

    QPushButton *trainingBtn = new QPushButton("训练 Go");
    trainingBtn->setFont(*btnFont);
    trainingBtn->setFixedHeight(NORMAL_BUTTON_HEIGHT);

    QPushButton *trainingClearBtn = new QPushButton("丢弃模型");
    trainingClearBtn->setFont(*btnFont);
    trainingClearBtn->setFixedHeight(NORMAL_BUTTON_HEIGHT);

    QPushButton *predictBtn = new QPushButton("预测 Go");
    predictBtn->setFont(*btnFont);
    predictBtn->setFixedHeight(NORMAL_BUTTON_HEIGHT);

    // Layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *subSampleLayout = new QHBoxLayout;
    QHBoxLayout *subTrainingLayout = new QHBoxLayout;
    QHBoxLayout *subPredictLayout = new QHBoxLayout;

    mainLayout->setMargin(MAIN_LAYOUT_MARGIN);
    subSampleLayout->setMargin(0);
    subSampleLayout->setSpacing(MAIN_LAYOUT_MARGIN);
    subTrainingLayout->setMargin(0);
    subTrainingLayout->setSpacing(MAIN_LAYOUT_MARGIN);
    subPredictLayout->setMargin(0);
    subPredictLayout->setSpacing(MAIN_LAYOUT_MARGIN);

    // sub-layout
    subSampleLayout->addWidget(sampleLabel);
    subSampleLayout->addStretch();
    subSampleLayout->addWidget(sampleImportBtn);
    subSampleLayout->addWidget(sampleClearBtn);

    subTrainingLayout->addWidget(trainingLabel);
    subTrainingLayout->addStretch();
    subTrainingLayout->addWidget(trainingBtn);
    subTrainingLayout->addWidget(trainingClearBtn);

    subPredictLayout->addWidget(predictLabel);
    subPredictLayout->addWidget(predictLineEdit);
    subPredictLayout->addStretch();
    subPredictLayout->addWidget(predictBtn);

    // main-layout
    mainLayout->addWidget(imageLabel);
    mainLayout->addLayout(subSampleLayout);
    mainLayout->addWidget(sampleTextEdit);
    mainLayout->addLayout(subTrainingLayout);
    mainLayout->addWidget(trainingScrollArea);
    mainLayout->addLayout(subPredictLayout);
    mainLayout->addWidget(predictScrollArea);
    mainLayout->addWidget(endingLabel);

    this->setLayout(mainLayout);

    this->show();

    // 重新调整大小
    this->adjustSize();
    // 这样可以使得窗口大小不可以变化
    this->setMinimumSize(this->size());
    this->setMaximumSize(this->size());

    // 设置连接槽, 按钮事件
    connect(sampleImportBtn, SIGNAL(clicked()), this, SLOT(onImportButtonClicked()));

    connect(sampleClearBtn, SIGNAL(clicked()), this, SLOT(onClearButtonClicked()));

    connect(trainingBtn, SIGNAL(clicked()), this, SLOT(onTrainingButtonClicked()));

    connect(trainingClearBtn, SIGNAL(clicked()), this, SLOT(onTrainingClearButtonClicked()));

    connect(predictBtn, SIGNAL(clicked()), this, SLOT(onPredictButtonClicked()));
}

// Button Clicked 按钮事件

// 导入TXT文件
void MyDialog::onImportButtonClicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "选了你的TXT文件", ":/", "*.txt");

    if (fileName.isNull()) {
        // cancel
        return;
    } else {
        // parse txt
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            criticalMessage("打开文件失败!");
        }
        // clear before
        sampleTextEdit->setText("");
        while (!file.atEnd()) {
            QByteArray line = file.readLine();
            QString sampleStr(line);
            if (sampleStr.isEmpty())
                continue;
            QString currentStr = sampleTextEdit->toPlainText();
            sampleTextEdit->setText(currentStr + sampleStr);
        }

        cout << sampleTextEdit->toPlainText().toStdString() << endl;
    }
}

// 清空样本输入框
void MyDialog::onClearButtonClicked()
{
    sampleTextEdit->setText("");
}

// 点击训练按钮
void MyDialog::onTrainingButtonClicked()
{
    string text = sampleTextEdit->toPlainText().toStdString();

    // JHParser
    JHParser parser;
    parser.setInputText(text);

    if (parser.parseSamples() == false) {
        criticalMessage("训练失败!\n请按照要求格式化输入文本.");
        return;
    }

    set<string> labels;
    labels = parser.getClassLabels();
    vector<Sample> samples;
    samples = parser.getSamples();

    // JHBayes
    bayes = new JHBayes(samples, labels);
    bayes->goTraining();

    // 显示训练结果
    unsigned int featureNum = samples[0].getFeatureNum();
    unsigned int sampleNum = samples.size();
    unsigned int classNum = labels.size();
    vector<double> all_means = bayes->get_all_means();
    vector<double> all_variances = bayes->get_all_variances();
    vector<double> all_maxVals = bayes->get_all_maxVals();
    vector<double> all_minVals = bayes->get_all_minVals();
    map< string, vector<double> > class_means = bayes->get_class_means();
    map< string, vector<double> > class_variances = bayes->get_class_variances();

    // 格式化字符串

    // 类别
    string classStr = "";
    set<string>::iterator it;
    for (it = labels.begin(); it != labels.end(); ++it) {
        classStr += (*it);
        classStr += "  ";
    }

    // 平均值
    string meanStr = "";
    for (unsigned int i = 0; i < all_means.size(); ++i) {
        char temp[10];
        sprintf(temp, "%.3lf", all_means[i]);
        meanStr += temp;
        meanStr += "  ";
    }

    // 方差值
    string varianceStr = "";
    for (unsigned int i = 0; i < all_variances.size(); ++i) {
        char temp[10];
        sprintf(temp, "%.3lf", all_variances[i]);
        varianceStr += temp;
        varianceStr += "  ";
    }

    // 最小值
    string minStr = "";
    for (unsigned int i = 0; i < all_minVals.size(); ++i) {
        char temp[10];
        sprintf(temp, "%.3lf", all_minVals[i]);
        minStr += temp;
        minStr += "  ";
    }

    // 最大值
    string maxStr = "";
    for (unsigned int i = 0; i < all_maxVals.size(); ++i) {
        char temp[10];
        sprintf(temp, "%.3lf", all_maxVals[i]);
        maxStr += temp;
        maxStr += "  ";
    }

    // 各类平均值 & 方差值
    string classMeanStr = "";
    string classVarianceStr = "";
    set<string>::iterator ite;
    for (ite = labels.begin(); ite != labels.end(); ++ite)
    {

        vector<double> classMeanV = class_means[*ite];
        vector<double> classVarianceV = class_variances[*ite];

        classMeanStr += "平均值(";
        classMeanStr += *ite;
        classMeanStr += "):   ";
        classVarianceStr += "方差值(";
        classVarianceStr += *ite;
        classVarianceStr += "):   ";

        for (unsigned int i = 0; i < featureNum; ++i)
        {
            double mean_val = classMeanV[i];
            double vari_val = classVarianceV[i];

            char mean_val_temp[10];
            char vari_val_temp[10];

            sprintf(mean_val_temp, "%.3lf", mean_val);
            sprintf(vari_val_temp, "%.3lf", vari_val);

            classMeanStr += mean_val_temp;
            classVarianceStr += vari_val_temp;
            classMeanStr += "  ";
            classVarianceStr += "  ";
        }
        classMeanStr += "\n";
        classVarianceStr += "\n";
    }

    // 组合结果字符串
    char str[4096];
    sprintf(str, "样本个数:  %d      特征个数:  %d      分类个数:  %d      类别:  %s\n最小值:  %s\n最大值:   %s\n平均值:  %s\n方差值:  %s\n%s%s", sampleNum, featureNum, classNum, classStr.c_str(), minStr.c_str(), maxStr.c_str(), meanStr.c_str(), varianceStr.c_str(), classMeanStr.c_str(), classVarianceStr.c_str());

    // 更新显示训练结果
    trainingResultLabel->setText(str);
    trainingResultLabel->adjustSize();
}

// 训练模型清空
void MyDialog::onTrainingClearButtonClicked()
{
    bayes = NULL;
    trainingResultLabel->setText("<空>");
    trainingResultLabel->adjustSize();
}

// 点击预测按钮
void MyDialog::onPredictButtonClicked()
{
    string text = predictLineEdit->text().toStdString();

    // JHParser
    JHParser parser;
    parser.setInputText(text);

    if (bayes == NULL) {
        criticalMessage("请先训练贝叶斯模型.");
        return;
    }

    vector<double> predVec;

    if (parser.parsePrediction(predVec) == false) {
        criticalMessage("请按照要求格式化输入文本.");
        return;
    }

    // 检查特征个数是否一致
    if (predVec.size() != bayes->getFeatureNum()) {
        criticalMessage("输入的特征数与模型不一致.");
        return;
    }

    // 进行预测
    map< string, double > predResult;
    bayes->predict(predVec, predResult);

    // 比较 & 显示预测结果
    string predStr = "结果为:  ";

    map< string, double >::iterator it;
    it = predResult.begin();

    // 预设最大值为第一个
    string maxStr = it->first;
    double maxVal = it->second;

    string temp = "";
    for (it = predResult.begin(); it != predResult.end(); ++it) {
        string classStr = it->first;
        double pResult = it->second;

        // 更新最大值
        if (pResult > maxVal) {
            maxStr = classStr;
            maxVal = pResult;
        }

        char str[15];
        sprintf(str, "%.8lf", pResult);
        temp += "P(";
        temp += classStr;
        temp += " | 数据) = ";
        temp += str;
        temp += "   ";

        cout << str << endl;
    }

    // 结果
    predStr += maxStr;
    char nl[3] = "\n";
    predStr += nl;

    // 详细的Probability
    predStr += temp;

    predictResultLabel->setText(predStr.c_str());
    predictResultLabel->adjustSize();
}

// 消息框
void MyDialog::criticalMessage(QString msg)
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::critical(this, "错误",
                                  msg,
                                  QMessageBox::Ok);
}

void MyDialog::warningMessage(QString msg)
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::warning(this, "警告",
                                 msg,
                                 QMessageBox::Ok);
}