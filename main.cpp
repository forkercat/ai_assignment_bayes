#include <QApplication>
#include <QTextCodec>
#include <QLayout>
#include <QLabel>
#include <QPushButton>
#include <QDialog>
#include <QLineEdit>
#include <QTextEdit>
#include <QPixmap>

int main(int argc, char **argv)
{
    // QApplication
    QApplication a(argc, argv);
    // Q_INIT_RESOURCE(images);
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());

    // window
    QDialog window;
    window.setWindowTitle("王俊皓贝叶斯分类器");

    // Image
    QPixmap introImage;
    introImage.load(":/images/bayes.jpg");

    QLabel imageLabel;
    imageLabel.setPixmap(introImage);
    imageLabel.setScaledContents(true);
    double scaleFactor = 0.7;
    imageLabel.resize(imageLabel.pixmap()->size() * scaleFactor);

    // All Labels
    QLabel featureLabel("Feature Set:");
    featureLabel.setFixedHeight(30);
    QLabel classLabel("Class Set:");
    classLabel.setFixedHeight(30);

    // TextEdit
    QTextEdit featureTextEdit;
    featureTextEdit.setFixedHeight(150);
    QTextEdit classTextEdit;
    classTextEdit.setFixedHeight(150);

    // All Buttons
    QPushButton btn("Training");

    // Layout
    QVBoxLayout layout;
    layout.addWidget(&imageLabel);
    layout.addWidget(&featureLabel);
    layout.addWidget(&featureTextEdit);
    layout.addWidget(&classLabel);
    layout.addWidget(&classTextEdit);
    layout.addWidget(&btn);

    window.setLayout(&layout);

    window.show();

    // resize to the best fitting
    window.adjustSize();
    // not allow to change the size
    window.setMinimumSize(window.size());
    window.setMaximumSize(window.size());

    return a.exec();
}


