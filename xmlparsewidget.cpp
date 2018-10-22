/***********************************************************************
 * Copyright (c)  2018， 上海亥伯智能科技有限公司
 * All rights reserved.
 *
 * 文件名称： xmlparsewidget.cpp
 * 摘要：XML文件解析界面窗口，用于将符合特点格式的XML文件在界面上展示出来
 *
 * 修改/版本历史（版本号、修改人、时间、修改、编写内容）：
 *
 * 1.V2.0    编写者名字     2017年10月7日内容（代码编写完成）
 *
************************************************************************/

#include "xmlparsewidget.h"
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QHeaderView>
#include "xmlreader.h"
#include "xmlwriter.h"


/************************************************************************
  函数名称： XMLParseWidget::XMLParseWidget
  功能描述：XMLParseWidget类的构造函数。初始化界面内容。
  输入描述：parent ,父窗口指针默认为0
  输出描述：无
  返回值：无
  其它：
************************************************************************/
XMLParseWidget::XMLParseWidget(QWidget *parent) :
    QWidget(parent)
{

    QStringList labels;
    labels << tr("Title") << tr("Location");

    treeWidget = new QTreeWidget;
    treeWidget->header()->setSectionResizeMode(QHeaderView::Stretch);
    treeWidget->setHeaderLabels(labels);

    menuBar = new QMenuBar(this);

    statusBar = new QStatusBar(this);
    statusBar->showMessage(tr("Ready"));

    layout = new QVBoxLayout(this);
    layout->setMargin(1);

    layout->addWidget(menuBar);
    layout->addWidget(treeWidget);
    layout->addWidget(statusBar);

    setLayout(layout);

    CreateActions();
    CreateMenus();

    resize(480, 320);

}

/************************************************************************
  函数名称： XMLParseWidget::~XMLParseWidget
  功能描述：XMLParseWidget类的析构函数。
  输入描述：无
  输出描述：无
  返回值：无
  其它：
************************************************************************/
XMLParseWidget::~XMLParseWidget()
{

}

/************************************************************************
  函数名称： XMLParseWidget::Open
  功能描述： 界面的“打开”菜单项功能。
  输入描述：无
  输出描述：无
  返回值：无
  其它：
************************************************************************/
void XMLParseWidget::Open()
{
    QString fileName =
            QFileDialog::getOpenFileName(this, tr("Open Attribute File"),
                                         QDir::currentPath(),
                                         tr("XBEL Files (*.xbel *.xml)"));
    if (fileName.isEmpty())
        return;

    treeWidget->clear();


    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("QXmlStream Attributes"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return;
    }

    XmlReader reader(treeWidget);
    if (!reader.Read(&file)) {
        QMessageBox::warning(this, tr("QXmlStream Attributes"),
                             tr("Parse error in file %1:\n\n%2")
                             .arg(fileName)
                             .arg(reader.ErrorString()));
    } else {
        statusBar->showMessage(tr("File loaded"), 2000);
    }


}
/************************************************************************
  函数名称： XMLParseWidget::SaveAs
  功能描述： 界面的“另存为”菜单项功能。
  输入描述：无
  输出描述：无
  返回值：无
  其它：
************************************************************************/
void XMLParseWidget::SaveAs()
{
    QString fileName =
            QFileDialog::getSaveFileName(this, tr("Save Attribute File"),
                                         QDir::currentPath(),
                                         tr("XBEL Files (*.xbel *.xml)"));
    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("QXmlStream Attributes"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return;
    }

    XmlWriter writer(treeWidget);
    if (writer.WriteFile(&file))
        statusBar->showMessage(tr("File saved"), 2000);
}
/************************************************************************
  函数名称： XMLParseWidget::About
  功能描述： 界面的“关于”菜单项功能。
  输入描述：无
  输出描述：无
  返回值：无
  其它：
************************************************************************/
void XMLParseWidget::About()
{
   QMessageBox::about(this, tr("About QXmlStream Attributes"),
            tr("The <b>QXmlStream Attributes</b> example demonstrates how to use Qt's "
               "QXmlStream classes to read and write XML documents."));
}
/************************************************************************
  函数名称： XMLParseWidget::CreateActions
  功能描述： 创建菜单项功能。
  输入描述：无
  输出描述：无
  返回值：无
  其它：
************************************************************************/
void XMLParseWidget::CreateActions()
{
    openAct = new QAction(tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    connect(openAct, SIGNAL(triggered()), this, SLOT(Open()));

    saveAsAct = new QAction(tr("&Save As..."), this);
    saveAsAct->setShortcuts(QKeySequence::SaveAs);
    connect(saveAsAct, SIGNAL(triggered()), this, SLOT(SaveAs()));

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    aboutAct = new QAction(tr("&About"), this);
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(About()));

}


/************************************************************************
  函数名称： XMLParseWidget::CreateMenus
  功能描述： 创建界面的菜单项。
  输入描述：无
  输出描述：无
  返回值：无
  其它：
************************************************************************/
void XMLParseWidget::CreateMenus()
{
    fileMenu = menuBar->addMenu(tr("&File"));
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAsAct);
    fileMenu->addAction(exitAct);

    menuBar->addSeparator();

    helpMenu = menuBar->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);

}

