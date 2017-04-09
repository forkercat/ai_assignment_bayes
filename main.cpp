#include <QApplication>
#include <QTextCodec>
#include "mydialog.h"

#include <iostream>

int main(int argc, char **argv)
{
    // QApplication
    QApplication a(argc, argv);
    // 编码
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
    // 窗口视图
    MyDialog dialog;
    dialog.show();

    std::cout << "Junhao GOOD!" << std::endl;
    
    return a.exec();
}

