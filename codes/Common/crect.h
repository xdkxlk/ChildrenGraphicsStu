#ifndef CRECT_H
#define CRECT_H

#include "crect_global.h"
#include "cshape.h"
#include <qmetatype.h>

class CRECTSHARED_EXPORT CRect : public CShape
{
public:
    CRect();
	CRect(const CRect &);
    CRect(std::vector<QPointF>,Qt::GlobalColor);
	virtual QString GetClassName()
	{
		return QString("CRect");
	}
	virtual void SetShape(std::vector<QPointF>, Qt::GlobalColor);
	virtual std::vector<QPointF> GetPoints();
protected:
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    QPointF p1,p2;
    QPointF c1,c2;
};
Q_DECLARE_METATYPE(CRect)

#endif // CRECT_H
