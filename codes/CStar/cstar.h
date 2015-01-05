#ifndef CSTAR_H
#define CSTAR_H

#include "cstar_global.h"
#include "cshape.h"
#include <qmetatype.h>

class CSTARSHARED_EXPORT CStar : public CShape
{
public:
    CStar();
	CStar(const CStar&);
    CStar(std::vector<QPointF>,Qt::GlobalColor);
	virtual QString GetClassName()
	{
		return QString("CStar");
	}
	virtual void SetShape(std::vector<QPointF>, Qt::GlobalColor);
	virtual std::vector<QPointF> GetPoints();
protected:
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
        QPointF p1,p2,p3,p4,p5;
};
Q_DECLARE_METATYPE(CStar)

#endif // CSTAR_H
