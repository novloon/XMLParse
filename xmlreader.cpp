/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtWidgets>

#include "xmlreader.h"

/************************************************************************
  函数名称：XmlReader::XmlReader
  功能描述：XmlReader类的构造函数。初始化QTreeWidget相关风格。
  输入描述：treeWidget  QTreeWidget类型指针，将读取的XML信息载入到QTreeWidget类
  输出描述：无
  返回值：无
  其它：
************************************************************************/
XmlReader::XmlReader(QTreeWidget *treeWidget)
    : treeWidget(treeWidget)
{
    QStyle *style = treeWidget->style();

    folderIcon.addPixmap(style->standardPixmap(QStyle::SP_DirClosedIcon),
                         QIcon::Normal, QIcon::Off);
    folderIcon.addPixmap(style->standardPixmap(QStyle::SP_DirOpenIcon),
                         QIcon::Normal, QIcon::On);
    attributeIcon.addPixmap(style->standardPixmap(QStyle::SP_FileIcon));
}
/************************************************************************
  函数名称：XmlReader::XmlReader
  功能描述：XmlReader类的构造函数。
  输入描述：无
  输出描述：无
  返回值：无
  其它：
************************************************************************/
XmlReader::XmlReader()
{

}



/************************************************************************
  函数名称：XmlReader::Read
  功能描述：读取XML文件，对XML文件头的合法性进行判断，并调用ReadXML函数对内容进行解析。
  输入描述：device  要读取的XML文件名称。
  输出描述：无
  返回值：无
  其它：
************************************************************************/
bool XmlReader::Read(QIODevice *device)
{
    xml.setDevice(device);

    if (xml.readNextStartElement()) {
        if (xml.name() == "xwin" && xml.attributes().value("version") == "1.0")
            ReadXML();
        else
            xml.raiseError(QObject::tr("The file is not an XWIN version 1.0 file."));
    }

    return !xml.error();
}
/************************************************************************
  函数名称：XmlReader::ErrorString
  功能描述：读取XML文件报错信息。
  输入描述：无
  输出描述：无
  返回值：无
  其它：
************************************************************************/
QString XmlReader::ErrorString() const
{
    return QObject::tr("%1\nLine %2, column %3")
            .arg(xml.errorString())
            .arg(xml.lineNumber())
            .arg(xml.columnNumber());
}
/************************************************************************
  函数名称：XmlReader::ReadXML
  功能描述：读取XML文件,对XML文件内容进行解析。
  输入描述：无
  输出描述：无
  返回值：无
  其它：
************************************************************************/
void XmlReader::ReadXML()
{
    Q_ASSERT(xml.isStartElement() && xml.name() == "xwin");

    while (xml.readNextStartElement()) {
        if (xml.name() == "folder")
            ReadFolder(0);
        else if (xml.name() == "attribute")
            ReadAttribute(0);
        else if (xml.name() == "separator")
            ReadSeparator(0);
        else
            xml.skipCurrentElement();
    }
}
/************************************************************************
  函数名称：XmlReader::ReadTitle
  功能描述：读取XML文件的Title内容，并存入QTreeWidgetItem中。
  输入描述：item  QTreeWidget的每一项QTreeWidgetItem
  输出描述：无
  返回值：无
  其它：
************************************************************************/
void XmlReader::ReadTitle(QTreeWidgetItem *item)
{
    Q_ASSERT(xml.isStartElement() && xml.name() == "title");

    QString title = xml.readElementText();
    item->setText(0, title);
}
/************************************************************************
  函数名称：XmlReader::ReadSeparator
  功能描述：读取XML文件的Separator，并存入QTreeWidgetItem中。
  输入描述：item  QTreeWidget的每一项QTreeWidgetItem
  输出描述：无
  返回值：无
  其它：
************************************************************************/
void XmlReader::ReadSeparator(QTreeWidgetItem *item)
{
    Q_ASSERT(xml.isStartElement() && xml.name() == "separator");

    QTreeWidgetItem *separator = CreateChildItem(item);
    separator->setFlags(item->flags() & ~Qt::ItemIsSelectable);
    separator->setText(0, QString(30, 0xB7));
    xml.skipCurrentElement();
}
/************************************************************************
  函数名称：XmlReader::ReadFolder
  功能描述：读取XML文件的Folder，并存入QTreeWidgetItem中。
  输入描述：item  QTreeWidget的每一项QTreeWidgetItem
  输出描述：无
  返回值：无
  其它：
************************************************************************/
void XmlReader::ReadFolder(QTreeWidgetItem *item)
{
    Q_ASSERT(xml.isStartElement() && xml.name() == "folder");

    QTreeWidgetItem *folder = CreateChildItem(item);
    bool folded = (xml.attributes().value("folded") != "no");
    treeWidget->setItemExpanded(folder, !folded);

    while (xml.readNextStartElement()) {
        if (xml.name() == "title")
            ReadTitle(folder);
        else if (xml.name() == "folder")
            ReadFolder(folder);
        else if (xml.name() == "attribute")
            ReadAttribute(folder);
        else if (xml.name() == "separator")
            ReadSeparator(folder);
        else
            xml.skipCurrentElement();
    }
}
/************************************************************************
  函数名称：XmlReader::ReadAttribute
  功能描述：读取XML文件的Attribute，并存入QTreeWidgetItem中。
  输入描述：item  QTreeWidget的每一项QTreeWidgetItem
  输出描述：无
  返回值：无
  其它：
************************************************************************/
void XmlReader::ReadAttribute(QTreeWidgetItem *item)
{
    Q_ASSERT(xml.isStartElement() && xml.name() == "attribute");

    QTreeWidgetItem *attribute = CreateChildItem(item);
    attribute->setFlags(attribute->flags() | Qt::ItemIsEditable);
    attribute->setIcon(0, attributeIcon);
    attribute->setText(0, QObject::tr("Unknown title"));
    attribute->setText(1, xml.attributes().value("value").toString());

    while (xml.readNextStartElement()) {
        if (xml.name() == "title")
            ReadTitle(attribute);
        else
            xml.skipCurrentElement();
    }
}
/************************************************************************
  函数名称：XmlReader::CreateChildItem
  功能描述：创建QTreeWidget的QTreeWidgetItem，并存入QTreeWidget中。
  输入描述：item  QTreeWidget的每一项QTreeWidgetItem
  输出描述：无
  返回值：无
  其它：
************************************************************************/
QTreeWidgetItem *XmlReader::CreateChildItem(QTreeWidgetItem *item)
{
    QTreeWidgetItem *childItem;
    if (item) {
        childItem = new QTreeWidgetItem(item);
    } else {
        childItem = new QTreeWidgetItem(treeWidget);
    }
    childItem->setData(0, Qt::UserRole, xml.name().toString());
    return childItem;
}
/************************************************************************
  函数名称：XmlReader::ReadWinAttribute
  功能描述：读取XML文件中每一个元素对应的值
  输入描述：name  元素名称
  输出描述：无
  返回值：无
  其它：
************************************************************************/
QString XmlReader::ReadWinAttribute(QString name)
{
    Q_ASSERT(xml.isStartElement() && xml.name() == "attribute");

    QString str = xml.attributes().value("value").toString();

    while (xml.readNextStartElement())
    {
        if (xml.name() == "title")
        {

            if(ReadWinTitle(name))
            {
                return str;
            }
            else
                return "";
        }
        else
            xml.skipCurrentElement();
    }
    return "";
}
/************************************************************************
  函数名称：XmlReader::ReadWinTitle
  功能描述：读取XML文件中Title的内容是否成功
  输入描述：name  元素名称
  输出描述：无
  返回值：无
  其它：
************************************************************************/
bool XmlReader::ReadWinTitle(QString name)
{
    Q_ASSERT(xml.isStartElement() && xml.name() == "title");

    QString title = xml.readElementText();

    if(title == name)
        return true;
    else
        return false;
}

/************************************************************************
  函数名称：XmlReader::ReadWinFolder
  功能描述：读取XML文件中Folder下各个元素的值
  输入描述：无
  输出描述：locate  将元素名和值存入WinLocate结构体中
  返回值：无
  其它：
************************************************************************/
void XmlReader::ReadWinFolder(struct WinLocate &locate)
{
    Q_ASSERT(xml.isStartElement() && xml.name() == "folder");

    while (xml.readNextStartElement())
    {
        if (xml.name() == "title")
        {
            if(ReadWinTitle(locate.name))
            {
                qDebug() << locate.name;
                QString x;
                while (xml.readNextStartElement()) {
                    if (xml.name() == "attribute")
                        x = ReadWinAttribute("X");
                    else
                        xml.skipCurrentElement();
                }

                QString y ;
                while (xml.readNextStartElement()) {
                    if (xml.name() == "attribute")
                        y = ReadWinAttribute("Y");
                    else
                        xml.skipCurrentElement();
                }
                QString width;
                while (xml.readNextStartElement()) {
                    if (xml.name() == "attribute")
                        width = ReadWinAttribute("Width");
                    else
                        xml.skipCurrentElement();
                }
                QString height;
                while (xml.readNextStartElement()) {
                    if (xml.name() == "attribute")
                        height = ReadWinAttribute("Height");
                    else
                        xml.skipCurrentElement();
                }
                locate.x = x.toInt();
                locate.y = y.toInt();
                locate.width = width.toInt();
                locate.height = height.toInt();
                qDebug() <<locate.name << "pos is"<< x <<" "<<y<< " "<<  width  << " " << height;

            }
//            else
//                qDebug() << " ";
        }
        else if (xml.name() == "folder")
            ReadWinFolder(locate);
        else
            xml.skipCurrentElement();
    }

}
/************************************************************************
  函数名称：XmlReader::ReadXmlWinLoate
  功能描述：读取并解析XML文件，将创子窗口信息并返回WinLocate结构体中
  输入描述：device   解析的XML文件名称
          winname  Folder的名称（子窗口的名称）
  输出描述：无
  返回值：struct WinLocate
  其它：
************************************************************************/
struct WinLocate XmlReader::ReadXmlWinLoate(QIODevice *device,QString winname)
{
    struct WinLocate winlocate = {0};
    winlocate.name = winname;

    xml.setDevice(device);

    if (xml.readNextStartElement())
    {
        if (xml.name() == "xwin" && xml.attributes().value("version") == "1.0")
        {
            Q_ASSERT(xml.isStartElement() && xml.name() == "xwin");

            while (xml.readNextStartElement()) {
                if (xml.name() == "folder")
                {
                    ReadWinFolder(winlocate);
                }
                else
                    xml.skipCurrentElement();
            }
        }
        else
            xml.raiseError(QObject::tr("The file is not an XWIN version 1.0 file."));
    }


    return winlocate;
}
