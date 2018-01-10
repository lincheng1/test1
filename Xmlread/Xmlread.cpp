#include "Xmlread.h"
#include <QDomDocument>  //�ļ�
#include <QFile>
#include <QTreeWidgetItem>
#include <QFileDialog>
#include "ui_Xmlread.h"
#include <QMessageBox>


#include <QDomText>


Xmlread::Xmlread(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	connect(ui.openButton, SIGNAL(clicked()), this, SLOT(openFile()));
	connect(ui.saveButton, SIGNAL(clicked()), this, SLOT(writeFile()));
	connect(ui.exitButton, SIGNAL(clicked()), this, SLOT(close()));
	connect(ui.SaveButton, SIGNAL(clicked()), this, SLOT(saveFile()));

	connect(ui.btn_newgroup, SIGNAL(clicked()), this, SLOT(newGroup()));
	connect(ui.btn_delgroup, SIGNAL(clicked()), this, SLOT(delGroup()));
	connect(ui.clearButton, SIGNAL(clicked()), this, SLOT(cleartree()));

	//writeFile("./demo1.xml");


	//��ʼ��treewidget

	ui.treeWidget->setColumnCount(2);//�������ñ��е��е�����Ŀ���ڱ�ͷ�л��ж�Ӧ����ʾ��
	ui.treeWidget->setColumnWidth(0, 300);  //�����п�

	//QTreeWidget::setHeaderHidden();                         //���ر�ͷ
	//ui.treeWidget->setHeaderHidden("hide");         //���ر�ͷ

	//QTreeWidgetItem::setSortingEnabled(bool)          //�������������Ƿ�������򣬵�Ϊtrueʱ�򣬵����ͷ�����Զ�����
	
	
	//zhu
	ui.treeWidget->setSortingEnabled(true);

	
	QStringList lists;
	lists << "NO" << "name";
	ui.treeWidget->setHeaderLabels(lists);

	for (int i = 0; i < 10; i++)
	{
		QStringList contentList;
		contentList << QString("00%1").arg(i) << "boy";
		QTreeWidgetItem *pNewItem = new QTreeWidgetItem(ui.treeWidget, contentList);  //����
		pNewItem->setBackgroundColor(0, QColor(150, 150, 0));
		pNewItem->setFont(10, QFont());
		
	}
	//pNewItemRoot->setExpanded(true);  //չ������

	setWindowFlags(Qt::Dialog | Qt::WindowMaximizeButtonHint | Qt::WindowMinimizeButtonHint);
	//showMaximized();


}


void Xmlread::openXML(QString fileName)
{
	QFile file(fileName);
	if (file.open(QIODevice::ReadOnly))
	{
		QDomDocument dom("WCM");
		if (dom.setContent(&file))  //������ݳɹ�����
		{
			ui.treeWidget->clear();
			QDomElement docElem = dom.documentElement();//��ȡ�ĵ��ĸ�Ԫ��
			listDom(docElem, NULL);   ///
		}
	}
	file.close();
}

void Xmlread::listDom(QDomElement& docElem, QTreeWidgetItem * pItem)
{
	//QDomElement docElem;
	

	QDomNode node = docElem.firstChild();//��ȡ��һ������
	//QTreeWidgetItem* pItem = new QTreeWidgetItem;
	if (node.toElement().isNull())
	{
		pItem->setText(1, docElem.text());
	}
	while (!node.isNull())
	{
		QDomElement element = node.toElement(); // try to convert the node to an element.  
		if (!element.isNull())
		{
			QTreeWidgetItem *item;
			if (pItem)              //����ʲô��˼
			{
				item = new QTreeWidgetItem(pItem);//����һ����С���������丽�ӵ������ĸ��ڵ㡣
			}
			else
			{
				item = new QTreeWidgetItem(ui.treeWidget);//����һ��ָ�����͵����ؼ��������ӵ��ڸ����ĸ���
			}
			item->setText(0, element.tagName());
			listDom(element, item);    ///gaiguo??
			if (pItem)         //???
			{
				pItem->addChild(item); //��ָ����..�������Ŀ
			}
			else
			{
				ui.treeWidget->addTopLevelItem(item); //����Ŀ��Ϊһ��������Ŀ�еĿؼ���
			}
		}

		node = node.nextSibling();
	}
	return;
}

void Xmlread::openFile()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open XML File"), "./", tr("XML Files (*.xml)"));
	if (!fileName.isEmpty())
	{
		openXML(fileName);
	}
}


Xmlread::~Xmlread()
{

}

void Xmlread::writeFile()
{
	//QString fileName = QFileDialog::getSaveFileName(this, "Save File", QDir::currentPath());

	//QFile*file = new QFile;



	//file->setFileName(fileName);

	//bool ok = file->open(QIODevice::WriteOnly);  //

	//if (ok)
	//{

	//	QTextStream out(file);
	//	out << ui.treeWidget->topLevelWidget();  //
	//	file->close();
	//	delete file;

	//}
	//else
	//{
	//	QMessageBox::information(this, "error message", "file open error" + file->errorString());
	//	return;
	//}
	QString filePath = QFileDialog::getSaveFileName(this, tr("Save XML File"), "./", tr("XML Files (*.xml)"));
	


	/*QString filePath;
	filePath = "./demo1.xml";*/
	//�򿪻򴴽��ļ�  
	QFile file(filePath); //���·��������·������Դ·��������  

	if (true==file.exists())
	{
		return;
	} 
	else
	{
	if (!file.open(QFile::WriteOnly | QFile::Truncate)) //������QIODevice��Truncate��ʾ���ԭ��������  
		return;

	QDomDocument doc;//����xml�ĵ���
	//д��xmlͷ��  
	QDomProcessingInstruction instruction; //��Ӵ�������  
	instruction = doc.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\"");  //����xmlͷ
	doc.appendChild(instruction);    //��ͷ��ʽ׷�ӵ�xml�ĵ�
	//��Ӹ��ڵ�Ԫ��  
	QDomElement root = doc.createElement("library"); //����һ���ڵ��Ԫ��
	doc.appendChild(root);
	//��ӵ�һ���ӽڵ㼰����Ԫ��  
	QDomElement book = doc.createElement("book");
	book.setAttribute("id", 1); //��ʽһ����������  ���м�ֵ�Ե�ֵ�����Ǹ�������  
	QDomAttr time = doc.createAttribute("time"); //��ʽ������������ ֵ�������ַ���  
	time.setValue("2013/6/13");
	book.setAttributeNode(time);
	QDomElement title = doc.createElement("title"); //������Ԫ��  
	QDomText text; //�������ű�ǩ�м��ֵ  
	text = doc.createTextNode("C++ primer");
	book.appendChild(title);
	title.appendChild(text);
	QDomElement author = doc.createElement("author"); //������Ԫ��  
	text = doc.createTextNode("Stanley Lippman");
	author.appendChild(text);
	book.appendChild(author);
	root.appendChild(book);

	//��ӵڶ����ӽڵ㼰����Ԫ�أ����ֱ���ֻ�����¸�ֵ  
	book = doc.createElement("book1");
	book.setAttribute("id", 2);
	time = doc.createAttribute("time");
	time.setValue("2007/5/25");
	book.setAttributeNode(time);
	title = doc.createElement("title");
	text = doc.createTextNode("Thinking in Java");

	book.appendChild(title);
	title.appendChild(text);
	author = doc.createElement("author");
	text = doc.createTextNode("Bruce Eckel");
	author.appendChild(text);
	book.appendChild(author);
	root.appendChild(book);

	//��ӵ������ӽڵ㼰����Ԫ�أ����ֱ���ֻ�����¸�ֵ  
	book = doc.createElement("book3");
	book.setAttribute("id", 3);
	time = doc.createAttribute("time");
	time.setValue("2007/5/15");
	book.setAttributeNode(time);
	title = doc.createElement("title");
	text = doc.createTextNode("C++");

	book.appendChild(title);
	title.appendChild(text);
	author = doc.createElement("author");
	text = doc.createTextNode("Lin Cheng");
	author.appendChild(text);
	book.appendChild(author);
	root.appendChild(book);


	//������ļ� ���� 
	QTextStream out_stream(&file); //�ı��������ļ�
	doc.save(out_stream, 4); //����4��  
	file.close();
	}

}


void Xmlread::saveFile()
{
	QString fileName = QFileDialog::getSaveFileName(this, tr("Save XML File"), "./ManagedDevice.xml", tr("XML Files (*.xml)"));
	if (!fileName.isEmpty())
	{
		saveXML(fileName);
	}
}


void Xmlread::saveXML(QString fileName)
{
	QTreeWidgetItem *rootItem = ui.treeWidget->invisibleRootItem(); //���ĸ��ڵ�
	int countGroup = rootItem->childCount();

	if (countGroup <= 0)  //�б���û����
	{
		return;
	}

	QFile db(fileName);
	if (!db.open(QIODevice::WriteOnly | QIODevice::Truncate)) return;

	//ֻд��ʽ�򿪣��������ǰ����Ϣ
	QDomDocument doc;
	QDomProcessingInstruction instruction;
	instruction = doc.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\"");
	doc.appendChild(instruction);

	QDomElement root = doc.createElement("ManagedDevice");
	doc.appendChild(root); //��Ӹ�Ԫ��

	for (int i = 0; i < countGroup; i++)
	{
		QTreeWidgetItem *groupitem = rootItem->child(i);
		QString groupname = groupitem->text(0);       //��ָ���д���
		QDomElement elementGrp = doc.createElement("Group");   //����Ԫ��
		QDomAttr elementGrpAttr = doc.createAttribute("name"); //��������
		elementGrpAttr.setValue(groupname);         //��������ֵ
		elementGrp.setAttributeNode(elementGrpAttr);  //��Ԫ�������Թ���
		root.appendChild(elementGrp);             //��Ԫ��׷�ӵ����ڵ�

		int countDev = groupitem->childCount();
		for (int j = 0; j < countDev; j++)
		{
			QTreeWidgetItem *deviceitem = groupitem->child(j);
			QDomElement elementDev = doc.createElement("Device");

			//Device������name
			QString devicename = deviceitem->text(0);
			QDomAttr elementDevNameAttr = doc.createAttribute("name");
			elementDevNameAttr.setValue(devicename);
			elementDev.setAttributeNode(elementDevNameAttr);

			//Device������ip
			QString deviceip = deviceitem->data(0, Qt::UserRole).toString();
			QDomAttr elementDevIpAttr = doc.createAttribute("ip");
			elementDevIpAttr.setValue(deviceip);
			elementDev.setAttributeNode(elementDevIpAttr);

			elementGrp.appendChild(elementDev);

			int countChn = deviceitem->childCount();
			for (int k = 0; k < countChn; k++)
			{
				QTreeWidgetItem *channelitem = deviceitem->child(k);
				QString channelname = channelitem->text(0);
				QDomElement elementChn = doc.createElement("Channel");
				QDomAttr elementChnAttr = doc.createAttribute("name");
				elementChnAttr.setValue(channelname);
				elementChn.setAttributeNode(elementChnAttr);
				elementDev.appendChild(elementChn);

				QString strRtsp = channelitem->data(0, Qt::UserRole).toString();
				QDomElement elementRtsp = doc.createElement("RtspUrl");
				elementChn.appendChild(elementRtsp);
				QDomText textnodeRtsp = doc.createTextNode(strRtsp);
				elementRtsp.appendChild(textnodeRtsp);
			}
		}
	}

	QTextStream out(&db);
	out.setCodec("UTF-8");
	doc.save(out, 4);
	db.close();

	QMessageBox tmpMsgBox(QMessageBox::Information, QStringLiteral("��ʾ"), QStringLiteral("����Xml�ļ��ɹ���"), QMessageBox::Ok);
	tmpMsgBox.exec();
}

void Xmlread::newGroup()
{

	//QStringList header;
	//header << "book" << "content";
	//ui.treeWidget->setHeaderLabels(header); //���ñ�ͷ

	QTreeWidgetItem *newgroup = new QTreeWidgetItem(ui.treeWidget); //����һ��ָ�����͵����ؼ��������ӵ��ڸ����ĸ���
	newgroup->setText(0, QStringLiteral("lincheng"));
	//newgroup->setIcon(0, QIcon(QStringLiteral(":/QtXmlTest/Resources/image/group.png")));
	//newgroup->setWhatsThis(0, "Group");
}


void Xmlread::delGroup()
{
	QTreeWidgetItem *curritem = ui.treeWidget->currentItem();  //currentItem()���ص��ǵ�ǰ��ѡ�е�item


	if (curritem != NULL)
	{
  //ȫ�����ɾ��
		QTreeWidgetItem *curritemparent = curritem->parent();//����ָ�򸸶����ָ��
		//���û�и��ڵ��ֱ��ɾ��
		if (curritemparent == NULL)
		{
			int index = ui.treeWidget->indexOfTopLevelItem(curritem); //���ظ������������������������Ҳ�����򷵻�-1
			if (index != -1)               //
			{
				ui.treeWidget->takeTopLevelItem(index);  // ɾ�����и��������еĶ����������
			
			}
		}
		//����и��ڵ��Ҫ�ж����Ǹ��ڵ�ĵڼ����ӽڵ㣬�Ӷ�����Ӧ��ɾ��
		else
		{
			int countChild = curritemparent->childCount(); //�������������
			for (int i = 0; i < countChild; i++)
			{
				if (curritemparent->child(i) == curritem)
				{
					curritemparent->takeChild(i);    //ɾ������
					break;
				}
			}
		}
  //ֻ��ɾ����
		/*QString strItemType = curritem->whatsThis(0);
		if (strItemType == QStringLiteral("Group"))
		{
			int index = ui.treeWidget->indexOfTopLevelItem(curritem);
			if (index != -1)
			{
				ui.treeWidget->takeTopLevelItem(index);
			}
		}
*/
	}

}
//���tree����
void Xmlread::cleartree()
{
	ui.treeWidget->clear();
}