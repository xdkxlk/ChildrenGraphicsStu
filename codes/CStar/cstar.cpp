#include "cstar.h"
CStar::CStar() : CShape()
{
    const double Angle = 2*3.1415926/5;
    QPointF center;
    double R;
    double Rotate = (qrand()%((int)Angle*100))/100.0;
    do
    {
        center=m_GetPoint();
        R = qrand()%((int)(m_height-30))+30;
    }while(center.x()+R>m_wide || center.x()-R<-1*m_wide ||
           center.y()+R>m_height || center.y()-R<-1*m_height);

    p1 = QPointF(center.x()+R*cos(Rotate),center.y()+R*sin(Rotate));
    p2 = QPointF(center.x()+R*cos(Angle+Rotate),center.y()+R*sin(Angle+Rotate));
    p3 = QPointF(center.x()+R*cos(Angle*2+Rotate),center.y()+R*sin(Angle*2+Rotate));
    p4 = QPointF(center.x()+R*cos(Angle*3+Rotate),center.y()+R*sin(Angle*3+Rotate));
    p5 = QPointF(center.x()+R*cos(Angle*4+Rotate),center.y()+R*sin(Angle*4+Rotate));

}

CStar::CStar(const CStar& star)
{
	std::vector<QPointF> Points;
	Points.push_back(star.p1);
	Points.push_back(star.p2);
	Points.push_back(star.p3);
	Points.push_back(star.p4);
	Points.push_back(star.p5);
	CStar(Points, star.m_color);
}

CStar::CStar(std::vector<QPointF> Points, Qt::GlobalColor color) : CShape()
{
    m_color=color;
    p1=Points[0];
    p2=Points[1];
    p3=Points[2];
    p4=Points[3];
    p5=Points[4];
}

void CStar::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPainterPath path;
    path.moveTo(p1);
    path.lineTo(p3);
    path.lineTo(p5);
    path.lineTo(p2);
    path.lineTo(p4);
    path.closeSubpath();
    path.setFillRule(Qt::WindingFill);

    painter->fillPath(path,QBrush(m_color));
}

void CStar::SetShape(std::vector<QPointF> Points, Qt::GlobalColor color)
{
	m_color = color;
	p1 = Points[0];
	p2 = Points[1];
	p3 = Points[2];
	p4 = Points[3];
	p5 = Points[4];
}

std::vector<QPointF> CStar::GetPoints()
{
	std::vector<QPointF> Points;
	Points.push_back(p1);
	Points.push_back(p2);
	Points.push_back(p3);
	Points.push_back(p4);
	Points.push_back(p5);
	return Points;
}