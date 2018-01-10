#include "Xmlread.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Xmlread w;        //创建窗口对象

	w.setWindowTitle("XML");
    w.show();        // 显示
    return a.exec();
}
