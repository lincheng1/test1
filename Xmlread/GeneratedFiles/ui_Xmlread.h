/********************************************************************************
** Form generated from reading UI file 'Xmlread.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XMLREAD_H
#define UI_XMLREAD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_XmlreadClass
{
public:
    QWidget *centralWidget;
    QTreeWidget *treeWidget;
    QPushButton *openButton;
    QPushButton *saveButton;
    QPushButton *exitButton;
    QPushButton *SaveButton;
    QPushButton *btn_delgroup;
    QPushButton *btn_newgroup;
    QPushButton *clearButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *XmlreadClass)
    {
        if (XmlreadClass->objectName().isEmpty())
            XmlreadClass->setObjectName(QStringLiteral("XmlreadClass"));
        XmlreadClass->resize(591, 400);
        centralWidget = new QWidget(XmlreadClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        treeWidget = new QTreeWidget(centralWidget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));
        treeWidget->setGeometry(QRect(45, 41, 501, 221));
        openButton = new QPushButton(centralWidget);
        openButton->setObjectName(QStringLiteral("openButton"));
        openButton->setGeometry(QRect(50, 280, 75, 23));
        saveButton = new QPushButton(centralWidget);
        saveButton->setObjectName(QStringLiteral("saveButton"));
        saveButton->setGeometry(QRect(140, 280, 75, 23));
        exitButton = new QPushButton(centralWidget);
        exitButton->setObjectName(QStringLiteral("exitButton"));
        exitButton->setGeometry(QRect(500, 280, 75, 23));
        SaveButton = new QPushButton(centralWidget);
        SaveButton->setObjectName(QStringLiteral("SaveButton"));
        SaveButton->setGeometry(QRect(230, 280, 75, 23));
        btn_delgroup = new QPushButton(centralWidget);
        btn_delgroup->setObjectName(QStringLiteral("btn_delgroup"));
        btn_delgroup->setGeometry(QRect(320, 280, 75, 23));
        btn_newgroup = new QPushButton(centralWidget);
        btn_newgroup->setObjectName(QStringLiteral("btn_newgroup"));
        btn_newgroup->setGeometry(QRect(410, 280, 75, 23));
        clearButton = new QPushButton(centralWidget);
        clearButton->setObjectName(QStringLiteral("clearButton"));
        clearButton->setGeometry(QRect(250, 310, 75, 23));
        XmlreadClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(XmlreadClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 591, 23));
        XmlreadClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(XmlreadClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        XmlreadClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(XmlreadClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        XmlreadClass->setStatusBar(statusBar);

        retranslateUi(XmlreadClass);

        QMetaObject::connectSlotsByName(XmlreadClass);
    } // setupUi

    void retranslateUi(QMainWindow *XmlreadClass)
    {
        XmlreadClass->setWindowTitle(QApplication::translate("XmlreadClass", "Xmlread", Q_NULLPTR));
        openButton->setText(QApplication::translate("XmlreadClass", "\346\211\223\345\274\200\346\226\207\344\273\266", Q_NULLPTR));
        saveButton->setText(QApplication::translate("XmlreadClass", "\345\206\231\346\226\207\344\273\266", Q_NULLPTR));
        exitButton->setText(QApplication::translate("XmlreadClass", "\345\205\263\351\227\255", Q_NULLPTR));
        SaveButton->setText(QApplication::translate("XmlreadClass", "\344\277\235\345\255\230Xml", Q_NULLPTR));
        btn_delgroup->setText(QApplication::translate("XmlreadClass", "\345\210\240\351\231\244\345\210\206\347\273\204", Q_NULLPTR));
        btn_newgroup->setText(QApplication::translate("XmlreadClass", "\346\226\260\345\273\272\345\210\206\347\273\204", Q_NULLPTR));
        clearButton->setText(QApplication::translate("XmlreadClass", "\345\205\250\351\203\250\346\270\205\351\231\244", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class XmlreadClass: public Ui_XmlreadClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XMLREAD_H
