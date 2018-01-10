#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Xmlread.h"

#include <QtXml>                    //ԭ������ȱ�����ͷ�ļ�
#include <QDialog>
#include <QtWidgets/QWidget>
#include "ui_Xmlread.h"
#include <QDomText>


class QTreeWidgetItem;
class Xmlread : public QMainWindow
{
    Q_OBJECT

public:
	explicit Xmlread(QWidget *parent = 0);
   

	void listDom(QDomElement& docElem, QTreeWidgetItem * pItem);
	void openXML(QString fileName);
	void saveXML(QString fileName);



	~Xmlread();
private:
    Ui::XmlreadClass ui;

private slots:
	void openFile();

	void writeFile();

	void saveFile();

	void newGroup();
	void delGroup();

	void cleartree();

};


