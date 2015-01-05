#include "cstudy.h"
#include "cfactory.h"

CStudy::CStudy()
{
    m_ShapeClassName = "";
    m_Shape = NULL;
}

CShape *CStudy::GetShape(QString NameOfShapeName)
{
    m_ShapeClassName = NameOfShapeName;
    if(m_Shape!=NULL)
    {
        delete  m_Shape;
        m_Shape = NULL;
    }
    m_Shape = CFactory::GetNewShape(NameOfShapeName);
    return m_Shape;
}

CShape *CStudy::GetShapeAgain()
{
    if(m_ShapeClassName=="")
        return NULL;
    if(m_Shape!=NULL)
    {
        delete m_Shape;
        m_Shape = NULL;
    }
    m_Shape = CFactory::GetNewShape(m_ShapeClassName);
    return m_Shape;
}

CStudy::~CStudy()
{
    if(m_Shape!=NULL)
    {
        delete m_Shape;
        m_Shape = NULL;
    }
}
