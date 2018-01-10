#include "Xmlread.h"
#include <QDomDocument>  //文件
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


	//初始化treewidget

	ui.treeWidget->setColumnCount(2);//用于设置表中的列的列数目，在表头中会有对应的显示，
	ui.treeWidget->setColumnWidth(0, 300);  //设置列宽

	//QTreeWidget::setHeaderHidden();                         //隐藏表头
	//ui.treeWidget->setHeaderHidden("hide");         //隐藏表头

	//QTreeWidgetItem::setSortingEnabled(bool)          //可以用来设置是否可以排序，当为true时候，点击表头，会自动排序
	
	
	//zhu
	ui.treeWidget->setSortingEnabled(true);

	
	QStringList lists;
	lists << "NO" << "name";
	ui.treeWidget->setHeaderLabels(lists);

	for (int i = 0; i < 10; i++)
	{
		QStringList contentList;
		contentList << QString("00%1").arg(i) << "boy";
		QTreeWidgetItem *pNewItem = new QTreeWidgetItem(ui.treeWidget, contentList);  //增加
		pNewItem->setBackgroundColor(0, QColor(150, 150, 0));
		pNewItem->setFont(10, QFont());
		
	}
	//pNewItemRoot->setExpanded(true);  //展开子项

	setWindowFlags(Qt::Dialog | Qt::WindowMaximizeButtonHint | Qt::WindowMinimizeButtonHint);
	//showMaximized();


}


void Xmlread::openXML(QString fileName)
{
	QFile file(fileName);
	if (file.open(QIODevice::ReadOnly))
	{
		QDomDocument dom("WCM");
		if (dom.setContent(&file))  //如果内容成功解析
		{
			ui.treeWidget->clear();
			QDomElement docElem = dom.documentElement();//获取文档的根元素
			listDom(docElem, NULL);   ///
		}
	}
	file.close();
}

void Xmlread::listDom(QDomElement& docElem, QTreeWidgetItem * pItem)
{
	//QDomElement docElem;
	

	QDomNode node = docElem.firstChild();//获取第一个孩子
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
			if (pItem)              //这是什么意思
			{
				item = new QTreeWidgetItem(pItem);//构建一个树小部件并将其附加到给定的父节点。
			}
			else
			{
				item = new QTreeWidgetItem(ui.treeWidget);//构造一个指定类型的树控件项并将其添加到在给定的父项
			}
			item->setText(0, element.tagName());
			listDom(element, item);    ///gaiguo??
			if (pItem)         //???
			{
				pItem->addChild(item); //对指定的..添加子项目
			}
			else
			{
				ui.treeWidget->addTopLevelItem(item); //将项目作为一个顶级项目中的控件。
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
	//打开或创建文件  
	QFile file(filePath); //相对路径、绝对路径、资源路径都可以  

	if (true==file.exists())
	{
		return;
	} 
	else
	{
	if (!file.open(QFile::WriteOnly | QFile::Truncate)) //可以用QIODevice，Truncate表示清空原来的内容  
		return;

	QDomDocument doc;//创建xml文档。
	//写入xml头部  
	QDomProcessingInstruction instruction; //添加处理命令  
	instruction = doc.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\"");  //创建xml头
	doc.appendChild(instruction);    //把头格式追加到xml文档
	//添加根节点元素  
	QDomElement root = doc.createElement("library"); //创建一根节点个元素
	doc.appendChild(root);
	//添加第一个子节点及其子元素  
	QDomElement book = doc.createElement("book");
	book.setAttribute("id", 1); //方式一：创建属性  其中键值对的值可以是各种类型  
	QDomAttr time = doc.createAttribute("time"); //方式二：创建属性 值必须是字符串  
	time.setValue("2013/6/13");
	book.setAttributeNode(time);
	QDomElement title = doc.createElement("title"); //创建子元素  
	QDomText text; //设置括号标签中间的值  
	text = doc.createTextNode("C++ primer");
	book.appendChild(title);
	title.appendChild(text);
	QDomElement author = doc.createElement("author"); //创建子元素  
	text = doc.createTextNode("Stanley Lippman");
	author.appendChild(text);
	book.appendChild(author);
	root.appendChild(book);

	//添加第二个子节点及其子元素，部分变量只需重新赋值  
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

	//添加第三个子节点及其子元素，部分变量只需重新赋值  
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


	//输出到文件 保存 
	QTextStream out_stream(&file); //文本流关联文件
	doc.save(out_stream, 4); //缩进4格  
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
	QTreeWidgetItem *rootItem = ui.treeWidget->invisibleRootItem(); //树的根节点
	int countGroup = rootItem->childCount();

	if (countGroup <= 0)  //列表树没有项
	{
		return;
	}

	QFile db(fileName);
	if (!db.open(QIODevice::WriteOnly | QIODevice::Truncate)) return;

	//只写方式打开，并清空以前的信息
	QDomDocument doc;
	QDomProcessingInstruction instruction;
	instruction = doc.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\"");
	doc.appendChild(instruction);

	QDomElement root = doc.createElement("ManagedDevice");
	doc.appendChild(root); //添加根元素

	for (int i = 0; i < countGroup; i++)
	{
		QTreeWidgetItem *groupitem = rootItem->child(i);
		QString groupname = groupitem->text(0);       //在指定列创建
		QDomElement elementGrp = doc.createElement("Group");   //创建元素
		QDomAttr elementGrpAttr = doc.createAttribute("name"); //创建属性
		elementGrpAttr.setValue(groupname);         //设置属性值
		elementGrp.setAttributeNode(elementGrpAttr);  //把元素与属性关联
		root.appendChild(elementGrp);             //把元素追加到根节点

		int countDev = groupitem->childCount();
		for (int j = 0; j < countDev; j++)
		{
			QTreeWidgetItem *deviceitem = groupitem->child(j);
			QDomElement elementDev = doc.createElement("Device");

			//Device项属性name
			QString devicename = deviceitem->text(0);
			QDomAttr elementDevNameAttr = doc.createAttribute("name");
			elementDevNameAttr.setValue(devicename);
			elementDev.setAttributeNode(elementDevNameAttr);

			//Device项属性ip
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

	QMessageBox tmpMsgBox(QMessageBox::Information, QStringLiteral("提示"), QStringLiteral("保存Xml文件成功！"), QMessageBox::Ok);
	tmpMsgBox.exec();
}

void Xmlread::newGroup()
{

	//QStringList header;
	//header << "book" << "content";
	//ui.treeWidget->setHeaderLabels(header); //设置表头

	QTreeWidgetItem *newgroup = new QTreeWidgetItem(ui.treeWidget); //构造一个指定类型的树控件项并将其添加到在给定的父项
	newgroup->setText(0, QStringLiteral("lincheng"));
	//newgroup->setIcon(0, QIcon(QStringLiteral(":/QtXmlTest/Resources/image/group.png")));
	//newgroup->setWhatsThis(0, "Group");
}


void Xmlread::delGroup()
{
	QTreeWidgetItem *curritem = ui.treeWidget->currentItem();  //currentItem()返回的是当前被选中的item


	if (curritem != NULL)
	{
  //全部项都可删除
		QTreeWidgetItem *curritemparent = curritem->parent();//返回指向父对象的指针
		//如果没有父节点就直接删除
		if (curritemparent == NULL)
		{
			int index = ui.treeWidget->indexOfTopLevelItem(curritem); //返回给定顶级项的索引，或者如果找不到项，则返回-1
			if (index != -1)               //
			{
				ui.treeWidget->takeTopLevelItem(index);  // 删除树中给定索引中的顶级项并返回它
			
			}
		}
		//如果有父节点就要判断它是父节点的第几个子节点，从而将对应项删除
		else
		{
			int countChild = curritemparent->childCount(); //返回子项的数量
			for (int i = 0; i < countChild; i++)
			{
				if (curritemparent->child(i) == curritem)
				{
					curritemparent->takeChild(i);    //删除孩子
					break;
				}
			}
		}
  //只可删除组
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
//清除tree内容
void Xmlread::cleartree()
{
	ui.treeWidget->clear();
}