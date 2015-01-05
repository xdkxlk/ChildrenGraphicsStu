#include "cshape.h"
#include <cmath>

CShape::CShape() : QGraphicsItem()
{
    m_height = 70;
    m_wide = 200;
    m_color = m_GetColor();
}

QRectF CShape::boundingRect() const
{
    return QRectF(-1*m_wide,-1*m_height,2*m_wide,2*m_height);
}

Qt::GlobalColor CShape::m_GetColor()
{
    int Value;
    do{
        Value = (qrand()%17+2);
    }while(Value==3);
    return (Qt::GlobalColor)Value;
}

double CShape::m_Distance(QPointF p1,QPointF p2)
{
    double result=pow((p1.x()-p2.x()),2)+pow(p1.y()-p2.y(),2);
    result = sqrt(result);
    return result;
}

double CShape::m_DisPointToLine(QPointF p1, QPointF L1, QPointF L2)
{
    double K = m_K(L1,L2);
    return (abs(K*p1.x()-p1.y()-K*L1.x()+L1.y()))/(1.0*sqrt(K*K+1));
}

double CShape::m_K(QPointF p1, QPointF p2)
{
    return (p1.y()-p2.y())/(1.0*(p1.x()-p2.x()));
}

bool CShape::IsInTheRange(QPointF p)
{
    if(p.y()>-1*m_height && p.y()<m_height && p.x()>-1*m_wide && p.x()<m_wide)
        return true;
    else
        return false;
}
