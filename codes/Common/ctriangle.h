#ifndef CTRIANGLE_H
#define CTRIANGLE_H

#include "ctriangle_global.h"
#include "cshape.h"
#include <qmetatype.h>

class CTRIANGLESHARED_EXPORT CTriangle : public CShape
{
public:
    CTriangle();
	CTriangle(const CTriangle&);
    CTriangle(std::vector<QPointF>,Qt::GlobalColor);
	virtual QString GetClassName()
	{
		return QString("CTriangle");
	}
	virtual void SetShape(std::vector<QPointF>, Qt::GlobalColor);
	virtual std::vector<QPointF> GetPoints();
protected:
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
        QPointF p[3];
};
Q_DECLARE_METATYPE(CTriangle)

#endif // CTRIANGLE_H
