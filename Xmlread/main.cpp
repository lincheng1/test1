#include "Xmlread.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Xmlread w;        //�������ڶ���

	w.setWindowTitle("XML");
    w.show();        // ��ʾ
    return a.exec();
}
