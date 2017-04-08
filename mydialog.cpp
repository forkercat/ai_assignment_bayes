#include "mydialog.h"

#include <QtGui>

// height
static const int NORMAL_BUTTON_HEIGHT = 40;
static const int PRIMARY_BUTTON_HEIGHT = 80;
static const int TEXT_EDIT_HEIGHT = 200;
static const int LABEL_HEIGHT = 25;
static const int MAIN_LAYOUT_MARGIN = 10;
// font
static const int LABEL_FONT_SIZE = 16;
static const int BUTTON_FONT_SIZE = 16;
static const int TEXT_FONT_SIZE = 16;

MyDialog::MyDialog(QWidget *parent) : QDialog(parent)
{
    // Window
        this->setWindowTitle("Naive Bayes Classifier by Junhao");

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

        QLabel *sampleLabel = new QLabel("Your training set :");
        sampleLabel->setFont(*labelFont);
        sampleLabel->setFixedHeight(LABEL_HEIGHT);

        // TextEdit
        QFont *textFont = new QFont;
        textFont->setPointSize(TEXT_FONT_SIZE);

        sampleTextEdit = new QTextEdit;
        sampleTextEdit->setFixedHeight(TEXT_EDIT_HEIGHT);
        sampleTextEdit->setFont(*textFont);
        sampleTextEdit->setText("Remove me, and use MATRIX form.");
        // sampleTextEdit->setPlaceholderText("Input training set like a matrix.\nEach of elements should be seperated by blank.");

        // All Buttons
        QFont *btnFont = new QFont;
        btnFont->setPointSize(BUTTON_FONT_SIZE);

        QPushButton *sampleImportBtn = new QPushButton("Import TXT");
        sampleImportBtn->setFont(*btnFont);
        sampleImportBtn->setFixedHeight(NORMAL_BUTTON_HEIGHT);

        QPushButton *sampleClearBtn = new QPushButton("Clear");
        sampleClearBtn->setFont(*btnFont);
        sampleClearBtn->setFixedHeight(NORMAL_BUTTON_HEIGHT);

        QPushButton *btn = new QPushButton("Training");
        btn->setFont(*btnFont);

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
        mainLayout->addWidget(btn);

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
}

void MyDialog::onImportButtonClicked()
{
    QStringList fileList = QFileDialog::getOpenFileNames(this, "Select your matrix TXT file", ":/", "*.txt");
    QString fileName = fileList[0];

    if (fileList.isEmpty())
    {
        // cancel
        return;
    }
    else
    {
        // parse txt
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            criticalMessage("Failed to open the file!");
        }
        // clear before
        sampleTextEdit->setText("");
        while(!file.atEnd())
        {
            QByteArray line = file.readLine();
            QString sampleStr(line);
            if (sampleStr.isEmpty())
                continue;
            QString currentStr = sampleTextEdit->toPlainText();
            sampleTextEdit->setText(currentStr + sampleStr);
        }
    }
}

void MyDialog::onClearButtonClicked()
{
    sampleTextEdit->setText("");
}

// Message
void MyDialog::criticalMessage(QString msg)
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::critical(this, "Error",
                                    msg,
                                    QMessageBox::Ok);
}

void MyDialog::warningMessage(QString msg)
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::warning(this, "Waring",
                                    msg,
                                    QMessageBox::Ok);
}