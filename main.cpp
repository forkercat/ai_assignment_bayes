#include <QApplication>
#include <QTextCodec>
#include "mydialog.h"

int main(int argc, char **argv)
{
    // QApplication
    QApplication a(argc, argv);
    // Coding
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
    // UI
    MyDialog dialog;
    dialog.show();

    return a.exec();
}

