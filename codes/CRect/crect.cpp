#include "crect.h"

CRect::CRect() : CShape()
{
    /*
     * 生成的矩形，当p1.x<=0时c类点在右边
     * 当p1.x>0时c类点在左边
     */
    while(1)
    {
        p1 = m_GetPoint();
        int Distance  = m_wide;
        while(1)
        {
            p2 = m_GetPoint();
            if(m_Distance(p1,p2)>=20 && p2.x()!=p1.x() && p2.y()!=p1.y())
                break;
        }
        if(p1.x()<=0)
        {
            double tempx = qrand()%(Distance-20) + 20;
            c1.rx() = p1.x() + tempx;
            c1.ry() = p1.y() - tempx/(p1.y() - p2.y()) * (p1.x() - p2.x());
            c2.rx() = p2.x() + tempx;
            c2.ry() = p2.y() + c1.y() - p1.y();
            if(IsInTheRange(c2) && IsInTheRange(c1) && abs(m_Distance(c1,p1) - m_Distance(p1,p2))>=15)
                break;
        }
        else
        {
            double tempx = qrand()%(Distance-20) + 20;
            c1.rx() = p1.x() - tempx;
            c1.ry() = p1.y() - tempx/(p1.y() - p2.y()) * (p2.x() - p1.x());
            c2.rx() = p2.x() - tempx;
            c2.ry() = p2.y() + c1.y() - p1.y();
            if(IsInTheRange(c2) && IsInTheRange(c1) && abs(m_Distance(c1,p1) - m_Distance(p1,p2))>=15)
                break;
        }
    }
}

CRect::CRect(const CRect &rect)
{
	std::vector<QPointF> Points;
	Points.push_back(rect.p1);
	Points.push_back(rect.p2);
	Points.push_back(rect.c1);
	Points.push_back(rect.c2);
	CRect(Points, rect.m_color);
}

CRect::CRect(std::vector<QPointF> Points, Qt::GlobalColor color) : CShape()
{
    m_color=color;
    p1=Points[0];
    p2=Points[1];
    c1=Points[2];
    c2=Points[3];
}

void CRect::paint(QPainter *painter,
           const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPainterPath path;
    path.moveTo(p1);
    path.lineTo(p2);
    path.lineTo(c2);
    path.lineTo(c1);

    painter->fillPath(path,m_color);
}

void CRect::SetShape(std::vector<QPointF> Points, Qt::GlobalColor color)
{
	m_color = color;
	p1 = Points[0];
	p2 = Points[1];
	c1 = Points[2];
	c2 = Points[3];
}

std::vector<QPointF> CRect::GetPoints()
{
	std::vector<QPointF> Points;
	Points.push_back(p1);
	Points.push_back(p2);
	Points.push_back(c1);
	Points.push_back(c2);
	return Points;
}