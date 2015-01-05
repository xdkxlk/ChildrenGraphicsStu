#ifndef CSTUDY_H
#define CSTUDY_H
#include "cshape.h"
#include <QString>

class CStudy
{
public:
    CStudy();
    ~CStudy();
    CShape *GetShape(QString NameOfShapeName);
    CShape *GetShapeAgain();
private:
    QString m_ShapeClassName;
    CShape * m_Shape;
};

#endif // CSTUDY_H
