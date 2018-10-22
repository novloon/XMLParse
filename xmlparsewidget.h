/***********************************************************************
 * Copyright (c)  2018， 上海亥伯智能科技有限公司
 * All rights reserved.
 *
 * 文件名称： xmlparsewidget.h
 * 摘要：XMLParseWidget类实现，XML文件解析界面窗口，用于将符合特点格式的XML
 * 文件在界面上展示出来
 *
 * 修改/版本历史（版本号、修改人、时间、修改、编写内容）：
 *
 * 1.V2.0    编写者名字     2017年10月7日内容（代码编写完成）
 *
************************************************************************/

#ifndef XMLPARSEWIDGET_H
#define XMLPARSEWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QMenuBar>
#include <QTreeWidget>
#include <QStatusBar>


class XMLParseWidget : public QWidget
{
    Q_OBJECT

public:
    explicit XMLParseWidget(QWidget *parent = 0);
    ~XMLParseWidget();

public slots:
    void Open();
    void SaveAs();
    void About();

private:
    void CreateActions();
    void CreateMenus();

    QTreeWidget *treeWidget;

    QMenu *fileMenu;
    QMenu *helpMenu;
    QAction *openAct;
    QAction *saveAsAct;
    QAction *exitAct;
    QAction *aboutAct;

    QStatusBar *statusBar;
    QMenuBar *menuBar;
    QVBoxLayout *layout;

};

#endif // XMLPARSEWIDGET_H
