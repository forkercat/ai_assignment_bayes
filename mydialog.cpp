#include "mydialog.h"

#include <QtGui>
#include <string>
#include <iostream>
#include <set>
#include <vector>

#include "sample.h"
#include "jhparser.h"

// width
static const int LINE_EDIT_WIDTH = 195;
static const int TRAINING_LABEL_WIDTH = 400;
static const int PREDICT_LABEL_WIDTH = 400;

// height
static const int LINE_EDIT_HEIGHT = 30;
static const int NORMAL_BUTTON_HEIGHT = 40;
static const int TEXT_EDIT_HEIGHT = 110;
static const int TRAINING_LABEL_HEIGHT = 110;
static const int TRAINING_LABEL_INDENT = 3;
static const int PREDICT_LABEL_HEIGHT = 40;
static const int PREDICT_LABEL_INDENT = 3;
static const int LABEL_HEIGHT = 25;
static const int MAIN_LAYOUT_MARGIN = 10;
// font
static const int SMALL_LABEL_FONT_SIZE = 14;
static const int LABEL_FONT_SIZE = 16;
static const int BUTTON_FONT_SIZE = 16;
static const int BUTTON_BIG_FONT_SIZE = 18;
static const int TEXT_FONT_SIZE = 15;

MyDialog::MyDialog(QWidget *parent) : QDialog(parent)
{
    // Window
    this->setWindowTitle("俊皓的朴素贝叶斯分类器");

    // Image
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

    QLabel *sampleLabel = new QLabel("训练集 :");
    sampleLabel->setFont(*labelFont);
    sampleLabel->setFixedHeight(LABEL_HEIGHT);

    QLabel *trainingLabel = new QLabel("训练结果 :");
    trainingLabel->setFont(*labelFont);
    trainingLabel->setFixedHeight(LABEL_HEIGHT);

    QLabel *predictLabel = new QLabel("预测 / 分类 :");
    predictLabel->setFont(*labelFont);
    predictLabel->setFixedHeight(LABEL_HEIGHT);

    QLabel *endingLabel = new QLabel("ai_assignment_bayes © 2017 Junhao");
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
    trainingResultLabel->setFont(*textFont);
    trainingResultLabel->setIndent(TRAINING_LABEL_INDENT);
    trainingResultLabel->setText("<空>");
    trainingScrollArea->setWidget(trainingResultLabel);

    // PredictLineEdit
    predictLineEdit = new QLineEdit;
    predictLineEdit->setFixedWidth(LINE_EDIT_WIDTH);
    predictLineEdit->setFixedHeight(LINE_EDIT_HEIGHT);
    predictLineEdit->setFont(*textFont);
    predictLineEdit->setPlaceholderText("类别 特征1 特征2 ... 特征n");

    // PredictResultLabel
    QScrollArea *predictScrollArea = new QScrollArea;
    predictScrollArea->setFixedWidth(PREDICT_LABEL_WIDTH);
    predictScrollArea->setFixedHeight(PREDICT_LABEL_HEIGHT);
    std::cout << predictScrollArea->width() << std::endl;
    predictResultLabel = new QLabel;
    predictResultLabel->setFont(*textFont);
    predictResultLabel->setIndent(PREDICT_LABEL_INDENT);
    predictResultLabel->setText("<空>");
    predictScrollArea->setWidget(predictResultLabel);

    // All Buttons
    QFont *btnFont = new QFont;
    btnFont->setPointSize(BUTTON_FONT_SIZE);
    QFont *btnBigFont = new QFont;
    btnBigFont->setPointSize(BUTTON_BIG_FONT_SIZE);

    QPushButton *sampleImportBtn = new QPushButton("导入TXT");
    sampleImportBtn->setFont(*btnFont);
    sampleImportBtn->setFixedHeight(NORMAL_BUTTON_HEIGHT);

    QPushButton *sampleClearBtn = new QPushButton("清空数据");
    sampleClearBtn->setFont(*btnFont);
    sampleClearBtn->setFixedHeight(NORMAL_BUTTON_HEIGHT);

    QPushButton *trainingBtn = new QPushButton("训练 GO");
    trainingBtn->setFont(*btnFont);
    trainingBtn->setFixedHeight(NORMAL_BUTTON_HEIGHT);

    QPushButton *trainingClearBtn = new QPushButton("丢弃模型");
    trainingClearBtn->setFont(*btnFont);
    trainingClearBtn->setFixedHeight(NORMAL_BUTTON_HEIGHT);

    QPushButton *predictBtn = new QPushButton("预测 GO");
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

    // resize to the best fitting
    this->adjustSize();
    // not allow to change the size
    this->setMinimumSize(this->size());
    this->setMaximumSize(this->size());

    // connect & slot
    connect(sampleImportBtn, SIGNAL(clicked()), this, SLOT
    (onImportButtonClicked()));

    connect(sampleClearBtn, SIGNAL(clicked()), this, SLOT(onClearButtonClicked()));

    connect(trainingBtn, SIGNAL(clicked()), this, SLOT
    (onTrainingButtonClicked()));

    connect(trainingClearBtn, SIGNAL(clicked()), this, SLOT(onTrainingClearButtonClicked()));
}

// Button Clicked
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
        while(!file.atEnd()) {
            QByteArray line = file.readLine();
            QString sampleStr(line);
            if (sampleStr.isEmpty())
                continue;
            QString currentStr = sampleTextEdit->toPlainText();
            sampleTextEdit->setText(currentStr + sampleStr);
        }

        std::cout << sampleTextEdit->toPlainText().toStdString() << std::endl;
    }
}

void MyDialog::onClearButtonClicked()
{
    sampleTextEdit->setText("");
}

void MyDialog::onTrainingButtonClicked()
{
    std::string text = sampleTextEdit->toPlainText().toStdString();

    // JHParser
    JHParser parser(text);

    if (parser.parse() == false) {
        criticalMessage("训练失败!\n请尝试按照要求格式化输入文本.");
        return;
    }

    std::set<std::string> labels;
    labels = parser.getClassLabels();
    std::vector<Sample> samples;
    samples = parser.getSamples();

    // JHBayes
    bayes = new JHBayes(samples, labels);
    bayes->goTraining();
}

void MyDialog::onTrainingClearButtonClicked()
{
    trainingResultLabel->setText("<空>");
}

// Message
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