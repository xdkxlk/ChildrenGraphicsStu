#ifndef CSQUARE_H
#define CSQUARE_H

#include "csquare_global.h"
#include "cshape.h"
#include <qmetatype.h>

class CSQUARESHARED_EXPORT CSquare : public CShape
{
public:
    CSquare();
	CSquare(const CSquare&);
    CSquare(std::vector<QPointF>,Qt::GlobalColor);
	virtual QString GetClassName()
	{
		return QString("CSquare");
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
Q_DECLARE_METATYPE(CSquare)

#endif // CSQUARE_H
