#include <QApplication>
#include <QTextCodec>
#include <QLayout>
#include <QLabel>
#include <QPushButton>
#include <QDialog>
#include <QLineEdit>
#include <QTextEdit>
#include <QPixmap>
#include <QFont>

// height
const int NORMAL_BUTTON_HEIGHT = 40;
const int BIG_BUTTON_HEIGHT = 50;
const int TEXT_EDIT_HEIGHT = 150;
const int LABEL_HEIGHT = 25;
const int MAIN_LAYOUT_MARGIN = 10;
// font
const int LABEL_FONT_SIZE = 16;
const int BUTTON_FONT_SIZE = 16;
const int TEXT_FONT_SIZE = 16;

void initUI();

int main(int argc, char **argv)
{
    // QApplication
    QApplication a(argc, argv);
    // Coding
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
    // UI
    initUI();

    return a.exec();
}

void initUI()
{
    // window
    QDialog *window = new QDialog;
    window->setWindowTitle("Naive Bayes Classifier by Junhao");

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
    QLabel *featureLabel = new QLabel("FEATURE SET :");
    featureLabel->setFont(*labelFont);
    featureLabel->setFixedHeight(LABEL_HEIGHT);
    QLabel *classLabel = new QLabel("CLASS SET :");
    classLabel->setFont(*labelFont);
    classLabel->setFixedHeight(LABEL_HEIGHT);

    // TextEdit
    QFont *textFont = new QFont;
    textFont->setPointSize(TEXT_FONT_SIZE);
    QTextEdit *featureTextEdit = new QTextEdit;
    featureTextEdit->setFixedHeight(TEXT_EDIT_HEIGHT);
    featureTextEdit->setFont(*textFont);
    QTextEdit *classTextEdit = new QTextEdit;
    classTextEdit->setFixedHeight(TEXT_EDIT_HEIGHT);
    classTextEdit->setFont(*textFont);

    // All Buttons
    QFont *btnFont = new QFont;
    btnFont->setPointSize(BUTTON_FONT_SIZE);
    QPushButton *featureClearBtn = new QPushButton("Clear");
    featureClearBtn->setFont(*btnFont);
    featureClearBtn->setFixedHeight(NORMAL_BUTTON_HEIGHT);
    QPushButton *classClearBtn = new QPushButton("Clear");
    classClearBtn->setFixedHeight(NORMAL_BUTTON_HEIGHT);
    classClearBtn->setFont(*btnFont);
    QPushButton *btn = new QPushButton("Training");
    btn->setFont(*btnFont);

    // Layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *subFeatureLayout = new QHBoxLayout;
    QHBoxLayout *subClassLayout = new QHBoxLayout;

    mainLayout->setMargin(MAIN_LAYOUT_MARGIN);  // spacing between widgets
    subFeatureLayout->setMargin(0);
    subClassLayout->setMargin(0);

    // sub-layout
    subFeatureLayout->addWidget(featureLabel);
    subFeatureLayout->addStretch();
    subFeatureLayout->addWidget(featureClearBtn);
    subClassLayout->addWidget(classLabel);
    subClassLayout->addStretch();
    subClassLayout->addWidget(classClearBtn);

    // main-layout
    mainLayout->addWidget(imageLabel);
    mainLayout->addLayout(subFeatureLayout);
    mainLayout->addWidget(featureTextEdit);
    mainLayout->addLayout(subClassLayout);
    mainLayout->addWidget(classTextEdit);
    mainLayout->addWidget(btn);

    window->setLayout(mainLayout);

    window->show();

    // resize to the best fitting
    window->adjustSize();
    // not allow to change the size
    window->setMinimumSize(window->size());
    window->setMaximumSize(window->size());
}

