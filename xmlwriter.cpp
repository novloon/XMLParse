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

#include "xmlwriter.h"

/************************************************************************
  函数名称：XmlWriter::XmlWriter
  功能描述：XmlWriter类的构造函数。初始化QTreeWidget相关风格。
  输入描述：treeWidget  QTreeWidget类型指针
  输出描述：无
  返回值：无
  其它：
************************************************************************/
XmlWriter::XmlWriter(QTreeWidget *treeWidget)
    : treeWidget(treeWidget)
{
    xml.setAutoFormatting(true);
}
/************************************************************************
  函数名称：WriteFile::WriteFile
  功能描述：XML文件内容写入
  输入描述：device  XML文件
  输出描述：无
  返回值：无
  其它：
************************************************************************/
bool XmlWriter::WriteFile(QIODevice *device)
{
    xml.setDevice(device);

    xml.writeStartDocument();
//    xml.writeDTD("<!DOCTYPE xbel>");
    xml.writeStartElement("xwin");
    xml.writeAttribute("version", "1.0");
    for (int i = 0; i < treeWidget->topLevelItemCount(); ++i)
    {
        WriteItem(treeWidget->topLevelItem(i));

    }
    qDebug()<<treeWidget->topLevelItemCount();
    xml.writeEndDocument();
    return true;
}
/************************************************************************
  函数名称：WriteFile::WriteItem
  功能描述：将QTreeWidget中的每一个QTreeWidgetItem写入到XML文件中去
  输入描述：item  载入QTreeWidgetItem
  输出描述：无
  返回值：无
  其它：
************************************************************************/
void XmlWriter::WriteItem(QTreeWidgetItem *item)
{
    QString tagName = item->data(0, Qt::UserRole).toString();
    if (tagName == "folder") {
        bool folded = !treeWidget->isItemExpanded(item);
        xml.writeStartElement(tagName);
        xml.writeAttribute("folded", folded ? "yes" : "no");
        xml.writeTextElement("title", item->text(0));
        for (int i = 0; i < item->childCount(); ++i)
            WriteItem(item->child(i));
        xml.writeEndElement();
    } else if (tagName == "attribute") {
        xml.writeStartElement(tagName);
        if (!item->text(1).isEmpty())
            xml.writeAttribute("value", item->text(1));
        xml.writeTextElement("title", item->text(0));
        xml.writeEndElement();
    } else if (tagName == "separator") {
        xml.writeEmptyElement(tagName);
    }
}

