#include "csquare.h"
#include <QPen>

CSquare::CSquare() : CShape()
{
    while(1)
    {
        p1 = m_GetPoint();
        while(1)
        {
            p2 = m_GetPoint();
            if(m_Distance(p1,p2)>=20 && p2.x()!=p1.x() && p2.y()!=p1.y())
                break;
        }
        if(p1.x()<=0)
        {
            double tempx = p1.y() - p2.y();
            c1.rx() = p1.x() + tempx;
            c1.ry() = p1.y() - (p1.x() - p2.x());
            c2.rx() = p2.x() + tempx;
            c2.ry() = p2.y() + c1.y() - p1.y();
            if(IsInTheRange(c2) && IsInTheRange(c1))
                break;
        }
        else
        {
            double tempx = p1.y() - p2.y();
            c1.rx() = p1.x() - tempx;
            c1.ry() = p1.y() - (p2.x() - p1.x());
            c2.rx() = p2.x() - tempx;
            c2.ry() = p2.y() + c1.y() - p1.y();
            if(IsInTheRange(c2) && IsInTheRange(c1))
                break;
        }
    }

}

CSquare::CSquare(const CSquare& square)
{
	std::vector<QPointF> Points;
	Points.push_back(square.p1);
	Points.push_back(square.p2);
	Points.push_back(square.c1);
	Points.push_back(square.c2);
	CSquare(Points, square.m_color);
}

CSquare::CSquare(std::vector<QPointF> Points, Qt::GlobalColor color) : CShape()
{
    m_color=color;
    p1=Points[0];
    p2=Points[1];
    c1=Points[2];
    c2=Points[3];
}

void CSquare::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPainterPath path;
    path.moveTo(p1);
    path.lineTo(p2);
    path.lineTo(c2);
    path.lineTo(c1);

    painter->fillPath(path,m_color);

}

void CSquare::SetShape(std::vector<QPointF> Points, Qt::GlobalColor color)
{
	m_color = color;
	p1 = Points[0];
	p2 = Points[1];
	c1 = Points[2];
	c2 = Points[3];
}

std::vector<QPointF> CSquare::GetPoints()
{
	std::vector<QPointF> Points;
	Points.push_back(p1);
	Points.push_back(p2);
	Points.push_back(c1);
	Points.push_back(c2);
	return Points;
}