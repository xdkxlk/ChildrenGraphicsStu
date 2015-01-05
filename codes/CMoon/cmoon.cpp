#include "cmoon.h"

CMoon::CMoon() : CShape()
{
    /*
     * 利用贝塞尔曲线绘制，p类点为曲线端点，c类点为Curve点。
     * 首先生成一个矩形
     * 并且当前生成的矩形，当p1.x<=0时c类点在右边
     * 当p1.x>0时c类点在左边
     */
    int Distance  = m_wide;
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
            double tempx = qrand()%(Distance-20) + 20; //随机c类点的x坐标与p类点x坐标的距离（至少为20）
            c1.rx() = p1.x() + tempx;
            c1.ry() = p1.y() - tempx/(p1.y() - p2.y()) * (p1.x() - p2.x()); //利用相似三角形计算
            c2.rx() = p2.x() + tempx;
            c2.ry() = p2.y() + c1.y() - p1.y();
            if(IsInTheRange(c2) && IsInTheRange(c1))
                break;
        }
        else
        {
            double tempx = qrand()%(Distance-20) + 20;
            c1.rx() = p1.x() - tempx;
            c1.ry() = p1.y() - tempx/(p1.y() - p2.y()) * (p2.x() - p1.x());
            c2.rx() = p2.x() - tempx;
            c2.ry() = p2.y() + c1.y() - p1.y();
            if(IsInTheRange(c2) && IsInTheRange(c1))
                break;
        }
    }

    /*
     * 为了避免生成曲线开口方向的规律性
     * （因为生成的矩形比较特殊）
     * 利用随机数判断是否交换 p,c 类点
     */
    if(qrand()%2 == 0)
    {
        QPointF temp = p1;
        p1=c1;
        c1=temp;

        temp=p2;
        p2=c2;
        c2=temp;
    }

}

CMoon::CMoon(const CMoon & moon)
{
	std::vector<QPointF> Points;
	Points.push_back(moon.p1);
	Points.push_back(moon.p2);
	Points.push_back(moon.c1);
	Points.push_back(moon.c2);
	CMoon(Points, moon.m_color);
}

void CMoon::SetShape(std::vector<QPointF> Points, Qt::GlobalColor color)
{
	m_color = color;
	p1 = Points[0];
	p2 = Points[1];
	c1 = Points[2];
	c2 = Points[3];
}

std::vector<QPointF> CMoon::GetPoints()
{
	std::vector<QPointF> Points;
	Points.push_back(p1);
	Points.push_back(p2);
	Points.push_back(c1);
	Points.push_back(c2);
	return Points;
}

CMoon::CMoon(std::vector<QPointF> Points,Qt::GlobalColor color) : CShape()
{
    m_color =color;
    p1=Points[0];
    p2=Points[1];
    c1=Points[2];
    c2=Points[3];
}

void CMoon::paint(QPainter *painter,
           const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPainterPath path;
    path.moveTo(p1);
    path.cubicTo(c1,c2,p2);
    //内部曲线的c类点为外部c类点和p类点的中点
    path.cubicTo((c2.x()+p2.x())/2,(c2.y()+p2.y())/2,(c1.x()+p1.x())/2,(c1.y()+p1.y())/2,p1.x(),p1.y());

    painter->fillPath(path,m_color);
}
