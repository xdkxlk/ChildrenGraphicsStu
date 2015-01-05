#ifndef CFACTORY_H
#define CFACTORY_H

#include "cfactory_global.h"
#include <vector>
#include <map>
#include <qfile.h>
#include "cshape.h"
#include "ctriangle.h"
#include "cladder.h"
#include "cmoon.h"
#include "crect.h"
#include "csquare.h"
#include "cstar.h"

class CFACTORYSHARED_EXPORT CFactory
{

public:
    CFactory();
    static void InitFactory();//初始化
    static std::vector<QString> GetShapeName();//返回类所代表的形状的名字
    static CShape* GetNewRandShape();//随机获得一个形状
    static CShape* GetNewShape(QString);//从类所代表的形状名获得形状
    static CShape* GetShapeFromClassName(QString);//从类名获得形状
    static QString TransNamToClassName(QString);//把类所代表的形状名转换为类名
    static QString TransNamToReaName(QString);//把类名转换为类所代表的形状名
private:
    static std::map<QString, QString> m_ShapesNtoC; //形状名字 -> 形状类名
    static std::map<QString, QString> m_ShapesCtoN; //形状类名 -> 形状名字
};

#endif // CFACTORY_H
