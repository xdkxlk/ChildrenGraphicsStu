#ifndef CSHAPE_H
#define CSHAPE_H

#include "cshape_global.h"
#include <vector>
#include <QGraphicsItem>
#include <QPainter>
#include <QPainterPath>
#include <QLineF>
#include <QString>
/*
 * 所有图形的基类
 * 定义QGraphicsItem的boundingRect()
 * 提供一些数学上的点线关系的计算函数
 */
class CSHAPESHARED_EXPORT CShape : public QGraphicsItem
{
public:
    CShape();
    virtual QString GetClassName()=0;
    int GetColor()
    {
        return (int)m_color;
    }
    virtual void SetShape(std::vector<QPointF>, Qt::GlobalColor)=0;
    virtual std::vector<QPointF> GetPoints()=0;
    virtual ~CShape() = default;
protected:
    Qt::GlobalColor m_color;
    int m_height,m_wide;  //图形存在的最大范围

    double m_Distance(QPointF p1,QPointF p2); //计算两个点的距离
    double m_DisPointToLine(QPointF p1, QPointF L1,QPointF L2); //计算点到直线（L1到L2的直线）的距离
    double m_K(QPointF p1,QPointF p2); //计算斜率
    QPointF m_GetPoint() //在一定的范围随机获取一个点（这个范围是由 m_height,m_wide 确定的）
    {
        return QPointF((int)pow(-1,qrand()%2)*qrand()%m_wide,(int)pow(-1,qrand()%2)*qrand()%m_height);
    }

    Qt::GlobalColor m_GetColor(); //随机获得一个颜色，以填充当前图形

    bool IsInTheRange(QPointF p);

    //从 QGraphicsItem 继承过来的虚函数
    QRectF boundingRect() const;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option, QWidget *widget){}
};

#endif // CSHAPE_H
