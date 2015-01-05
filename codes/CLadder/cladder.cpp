#include "cladder.h"

CLadder::CLadder() : CShape()
{
    p1 = m_GetPoint();

    do
    {
        p2 = m_GetPoint();
    }while(m_Distance(p1,p2)<20 || p2.x()==p1.x());
    double K_P1P2 = m_K(p1,p2);
    double Distance_P1P2 = m_Distance(p1,p2);

    do{
        d1 = m_GetPoint();
        d2.rx() = m_GetPoint().x();
        d2.ry() = K_P1P2*d2.x() - K_P1P2*d1.x() + d1.y();
    }while (m_K(p1,d1)==K_P1P2 || m_Distance(p1,d1)<=10 || m_Distance(p2,d1)<=10 ||
            d2.y()<-1*m_height || d2.y()>m_height || abs(m_Distance(d2,d1) - Distance_P1P2)<30
            || m_Distance(d2,d1)<20 || m_DisPointToLine(d2,p1,p2)<30 );
}

CLadder::CLadder(const CLadder & ladder)
{
	std::vector<QPointF> Points;
	Points.push_back(ladder.p1);
	Points.push_back(ladder.p2);
	Points.push_back(ladder.d1);
	Points.push_back(ladder.d2);
	CLadder(Points, ladder.m_color);
}

std::vector<QPointF> CLadder::GetPoints()
{
	std::vector<QPointF> Points;
	Points.push_back(p1);
	Points.push_back(p2);
	Points.push_back(d1);
	Points.push_back(d2);
	return Points;
}

void CLadder::SetShape(std::vector<QPointF> Points, Qt::GlobalColor color)
{
	m_color = color;
	p1 = Points[0];
	p2 = Points[1];
	d1 = Points[2];
	d2 = Points[3];
}

CLadder::CLadder(std::vector<QPointF> Points,Qt::GlobalColor color) : CShape()
{
    m_color=color;
    p1=Points[0];
    p2=Points[1];
    d1=Points[2];
    d2=Points[3];
}

void CLadder::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPainterPath path;
    path.moveTo(p1);
    path.lineTo(p2);
    if(p1.x()<p2.x())
    {
        if(d1.x()<d2.x())
        {
            path.lineTo(d2);
            path.lineTo(d1);
        }
        else
        {
            path.lineTo(d1);
            path.lineTo(d2);
        }
    }
    else
    {
        if(d1.x()<d2.x())
        {
            path.lineTo(d1);
            path.lineTo(d2);
        }
        else
        {
            path.lineTo(d2);
            path.lineTo(d1);
        }
    }

    painter->fillPath(path,m_color);
}
