#ifndef CMOON_H
#define CMOON_H

#include "cmoon_global.h"
#include "cshape.h"
#include <qmetatype.h>

class CMOONSHARED_EXPORT CMoon : public CShape
{
public:
    CMoon();
	CMoon(const CMoon &);
    CMoon(std::vector<QPointF>,Qt::GlobalColor);
	virtual QString GetClassName()
	{
		return QString("CMoon");
	}
	virtual std::vector<QPointF> GetPoints();
	virtual void SetShape(std::vector<QPointF>, Qt::GlobalColor);
protected:
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    QPointF p1,p2;
    QPointF c1,c2;
};
Q_DECLARE_METATYPE(CMoon)

#endif // CMOON_H
