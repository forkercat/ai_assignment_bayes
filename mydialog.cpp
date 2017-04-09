#include "mydialog.h"

#include <QtGui>
#include <string>
#include <iostream>
#include <set>
#include <vector>

#include "sample.h"
#include "jhparser.h"


// height
static const int NORMAL_BUTTON_HEIGHT = 40;
static const int PRIMARY_BUTTON_HEIGHT = 60;
static const int TEXT_EDIT_HEIGHT = 180;
static const int LABEL_HEIGHT = 25;
static const int MAIN_LAYOUT_MARGIN = 10;
// font
static const int LABEL_FONT_SIZE = 16;
static const int BUTTON_FONT_SIZE = 16;
static const int BUTTON_BIG_FONT_SIZE = 28;
static const int TEXT_FONT_SIZE = 16;

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

    // All Labels
    QFont *labelFont = new QFont;
    labelFont->setPointSize(LABEL_FONT_SIZE);

    QLabel *sampleLabel = new QLabel("训练集 :");
    sampleLabel->setFont(*labelFont);
    sampleLabel->setFixedHeight(LABEL_HEIGHT);

    // TextEdit
    QFont *textFont = new QFont;
    textFont->setPointSize(TEXT_FONT_SIZE);

    sampleTextEdit = new QTextEdit;
    sampleTextEdit->setFixedHeight(TEXT_EDIT_HEIGHT);
    sampleTextEdit->setFont(*textFont);
    sampleTextEdit->setText("请用矩阵形式; 特征由空格隔开; 样本由换行分开; 类别在第一列.");
    // sampleTextEdit->setPlaceholderText("Input training set like a matrix.\nEach of elements should be seperated by blank.");

    // All Buttons
    QFont *btnFont = new QFont;
    btnFont->setPointSize(BUTTON_FONT_SIZE);
    QFont *btnBigFont = new QFont;
    btnBigFont->setPointSize(BUTTON_BIG_FONT_SIZE);

    QPushButton *sampleImportBtn = new QPushButton("导入TXT");
    sampleImportBtn->setFont(*btnFont);
    sampleImportBtn->setFixedHeight(NORMAL_BUTTON_HEIGHT);

    QPushButton *sampleClearBtn = new QPushButton("清空");
    sampleClearBtn->setFont(*btnFont);
    sampleClearBtn->setFixedHeight(NORMAL_BUTTON_HEIGHT);

    QPushButton *trainingBtn = new QPushButton("训练, GO!");
    trainingBtn->setFont(*btnBigFont);
    trainingBtn->setFixedHeight(PRIMARY_BUTTON_HEIGHT);

    // Layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *subSampleLayout = new QHBoxLayout;

    mainLayout->setMargin(MAIN_LAYOUT_MARGIN);  // spacing between widgets
    subSampleLayout->setMargin(0);
    subSampleLayout->setSpacing(MAIN_LAYOUT_MARGIN);

    // sub-layout
    subSampleLayout->addWidget(sampleLabel);
    subSampleLayout->addStretch();
    subSampleLayout->addWidget(sampleImportBtn);
    subSampleLayout->addWidget(sampleClearBtn);

    // main-layout
    mainLayout->addWidget(imageLabel);
    mainLayout->addLayout(subSampleLayout);
    mainLayout->addWidget(sampleTextEdit);
    mainLayout->addWidget(trainingBtn);

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

    connect(trainingBtn, SIGNAL(clicked()), this, SLOT(onTrainingButtonClicked()));
}

// Button Clicked
void MyDialog::onImportButtonClicked()
{
    QStringList fileList = QFileDialog::getOpenFileNames(this, "选了你的TXT文件", ":/", "*.txt");
    QString fileName = fileList[0];

    if (fileList.isEmpty()) {
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