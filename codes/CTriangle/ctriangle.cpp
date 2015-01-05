#include "ctriangle.h"
#include <cstdlib>

CTriangle::CTriangle() : CShape()
{
    while(1)
    {
        p[0]=m_GetPoint();
        p[1]=m_GetPoint();
        do{
            p[2]=m_GetPoint();
        }while(m_K(p[0],p[1])==m_K(p[0],p[2]));
		if (m_DisPointToLine(p[0], p[1], p[2]) <= 20)
			continue;
		if (m_DisPointToLine(p[1], p[0], p[2]) <= 20)
			continue;
		if (m_DisPointToLine(p[2], p[0], p[2]) <= 20)
			continue;
		if (abs(m_K(p[0], p[1]) - m_K(p[0], p[2])) >= 0.6 &&
			abs(m_K(p[1], p[0]) - m_K(p[1], p[2])) >= 0.6)
			break;

	}
}

CTriangle::CTriangle(const CTriangle& triangle)
{
	std::vector<QPointF> Points;
	Points.push_back(triangle.p[0]);
	Points.push_back(triangle.p[1]);
	Points.push_back(triangle.p[2]);
	CTriangle(Points, triangle.m_color);
}

CTriangle::CTriangle(std::vector<QPointF> Points, Qt::GlobalColor color) : CShape()
{
    m_color = color;
    p[0]=Points[0];
    p[1]=Points[1];
    p[2]=Points[2];
}

void CTriangle::paint(QPainter *painter,
           const QStyleOptionGraphicsItem *option, QWidget *widget)
{
   QPainterPath path;
   path.moveTo(p[0]);
   path.lineTo(p[1]);
   path.lineTo(p[2]);
   path.lineTo(p[0]);

   painter->setPen(m_color);
   painter->drawPath(path);
   painter->fillPath(path,QBrush(m_color));
}

void CTriangle::SetShape(std::vector<QPointF> Points, Qt::GlobalColor color)
{
	m_color = color;
	p[0] = Points[0];
	p[1] = Points[1];
	p[2] = Points[2];
}

std::vector<QPointF> CTriangle::GetPoints()
{
	std::vector<QPointF> Points;
	Points.push_back(p[0]);
	Points.push_back(p[1]);
	Points.push_back(p[2]);
	return Points;
}