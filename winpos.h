/***********************************************************************
 * Copyright (c)  2018， 上海亥伯智能科技有限公司
 * All rights reserved.
 *
 * 文件名称： winpos.h
 * 摘要：XML文件解析头文件
 *
 * 修改/版本历史（版本号、修改人、时间、修改、编写内容）：
 *
 * 1.V2.0    编写者名字     2017年10月7日内容（代码编写完成）
 *
************************************************************************/

#ifndef WINPOS_H
#define WINPOS_H

#include <QString>

/*子窗口包含的位置信息结构体*/
struct WinLocate{
    QString name;      /*子窗口名称*/
    int x;             /*子窗口x坐标*/
    int y;             /*子窗口y坐标*/
    int width;         /*子窗口宽度信息*/
    int height;        /*子窗口高度信息*/
};

#define LEFTUPPERWIN          "LeftUpper"             /*左上方无人机与地面站位置信息子窗口名称*/
#define ENGINEPAPRAMSWIN      "EngineParams"          /*无人机发动机参数子窗口名称*/
#define CURVEWIN              "curve"                 /*曲线子窗口名称*/
#define LEFTINFOWIN           "LeftInfo"              /*做下方相关信息子窗口名称*/
#define FLIGHTPARAWIN         "flightPara"            /*飞行姿态参数子窗口名称*/
#define FUNCTIONWIN           "function"              /*功能子窗口名称*/
#define ELECTWIN              "elect";                /*电气子窗口名称*/
#define TESTMAPWIN            "testMap";              /*地图子窗口名称*/



#endif // WINPOS_H

