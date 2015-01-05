#include "cfactory.h"
#include <QString>
#include <QByteArray>
#include <QTextStream>
#include <QMetaType>
using namespace std;

/*
配置文件( Config.txt )格式：
例：
[line 1] CStar(形状类的类名) 五角星(这个类代表的形状)
*/

std::map<QString, QString> CFactory::m_ShapesNtoC;
std::map<QString, QString> CFactory::m_ShapesCtoN;

CFactory::CFactory()
{
}

void CFactory::InitFactory()
{
    qRegisterMetaType<CTriangle>("CTriangle");
    qRegisterMetaType<CLadder>("CLadder");
    qRegisterMetaType<CMoon>("CMoon");
    qRegisterMetaType<CRect>("CRect");
    qRegisterMetaType<CSquare>("CSquare");
    qRegisterMetaType<CStar>("CStar");
    QFile file("Config.txt");
    file.open(QIODevice::ReadOnly);
    QTextStream stream(&file);
    QString ClassName, ClassShape;
    while (!stream.atEnd())
    {
        stream >> ClassName >> ClassShape;
        m_ShapesNtoC.insert(pair<QString, QString>(ClassShape, ClassName));
        m_ShapesCtoN.insert(pair<QString, QString>(ClassName, ClassShape));
    }
    file.close();
}

vector<QString> CFactory::GetShapeName()
{
    vector<QString> temp;
    for (map<QString, QString>::iterator index = m_ShapesNtoC.begin(); index != m_ShapesNtoC.end(); index++)
    {
        temp.push_back(index->first);
    }
    return temp;
}

CShape* CFactory::GetNewRandShape()
{
    int num = qrand() % m_ShapesNtoC.size();
    map<QString, QString>::iterator index = m_ShapesNtoC.begin();
    for (int i = 0; i < num; i++)
        index++;
    QString ClassName = index->second;
    QByteArray str = ClassName.toLatin1();
    int id = QMetaType::type(str.data());
    if(id==QMetaType::UnknownType)
        return NULL;
    return (CShape*)QMetaType::create(id);
}

CShape* CFactory::GetNewShape(QString name)
{
    QByteArray str = m_ShapesNtoC[name].toLatin1();
    int id = QMetaType::type(str.data());
    if(id==QMetaType::UnknownType)
        return NULL;
    return (CShape*)QMetaType::create(id);
}

CShape* CFactory::GetShapeFromClassName(QString name)
{
    QByteArray str = name.toLatin1();
    int id = QMetaType::type(str.data());
    if (id == QMetaType::UnknownType)
        return NULL;
    return (CShape*)QMetaType::create(id);
}

QString CFactory::TransNamToClassName(QString name)
{
    return m_ShapesNtoC[name];
}

QString CFactory::TransNamToReaName(QString name)
{
    return m_ShapesCtoN[name];
}
