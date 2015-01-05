#ifndef CLADDER_H
#define CLADDER_H

#include "cladder_global.h"
#include "cshape.h"
#include <qmetatype.h>

class CLADDERSHARED_EXPORT CLadder : public CShape
{
public:
    CLadder();
	CLadder(const CLadder &);
    CLadder(std::vector<QPointF>, Qt::GlobalColor);
	virtual QString GetClassName()
	{
		return QString("CLadder");
	}
	virtual std::vector<QPointF> GetPoints();
	virtual void SetShape(std::vector<QPointF>, Qt::GlobalColor);
protected:
	void paint(QPainter *painter,
		const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
	QPointF p1, p2, d1, d2;
};
Q_DECLARE_METATYPE(CLadder)

#endif // CLADDER_H
