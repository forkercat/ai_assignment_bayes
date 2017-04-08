#include <QApplication>
#include <QTextCodec>
#include "mydialog.h"

#include <iostream>

int main(int argc, char **argv)
{
    // QApplication
    QApplication a(argc, argv);
    // Coding
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
    // UI
    MyDialog dialog;
    dialog.show();

    std::cout << "Junhao GOOD!" << std::endl;

    return a.exec();
}

