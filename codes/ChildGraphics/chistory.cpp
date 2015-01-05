#include "chistory.h"
#include "cfactory.h"
#include <QPointF>
#include <QStringList>
using namespace std;
QSettings * CHistory::m_History = new QSettings("data.ini",QSettings::IniFormat);
bool CHistory::IsClearAuto = CHistory::m_History->value("ClearAuto", false).toBool();
bool CHistory::PaperUnlimted = CHistory::m_History->value("PaperUnlimted", true).toBool();
CHistory::CHistory()
{
}

void CHistory::CloseHisFile()
{
    delete m_History;
}

int CHistory::KeySize()
{
    return m_History->value("KeySize",0).toInt();
}

QStringList CHistory::GetDataHead()
{
    QStringList out;
    QStringList keys = m_History->childGroups();
    for (int i = 0; i < keys.size(); i++)
    {
        double Grade = m_History->value(keys.at(i)+"/Grade").toDouble();
        int NumOfPaper = m_History->value(keys.at(i) + "/NumOfPaper").toInt();
        out.append(keys.at(i)+" " + QString::fromUtf8("\xe5\x88\x86\xe6\x95\xb0:") + QString::number(Grade) + QString::fromUtf8(" \xe9\xa2\x98\xe7\x9b\xae\xe6\x95\xb0\xe9\x87\x8f:") + QString::number(NumOfPaper));
    }
    return out;
}

void CHistory::Remove(QString Key)
{
    m_History->remove(Key);
}

void CHistory::GetData(QString Key, std::vector<CShape*> &Paper, std::vector<QString> &Answer)
{
    //读取试卷=========[1]
    int size = m_History->beginReadArray(Key + "/Paper");
    for (int i = 0; i < size; i++)
    {
        m_History->setArrayIndex(i);
        QString name = m_History->value(QString::number(i)).toString();
        CShape *shape = CFactory::GetShapeFromClassName(name);
        //开始读取这个图形的属性=====[2]
        int color = m_History->value(name + "/Color").toInt();
        int size = m_History->beginReadArray(name + "/Points");
        vector<QPointF> Points;
        for (int j = 0; j < size; j++)
        {
            m_History->setArrayIndex(j);
            QPointF temp = m_History->value(QString::number(j)).toPointF();
            Points.push_back(temp);
        }
        m_History->endArray();
        //================[2]
        shape->SetShape(Points, (Qt::GlobalColor)color);
        Paper.push_back(shape);
    }
    m_History->endArray();
    //=============[1]
    //读取用户回答======[3]
    size = m_History->beginReadArray(Key + "/Answer");
    for (int i = 0; i < size; i++)
    {
        m_History->setArrayIndex(i);
        QString temp = m_History->value(QString::number(i)).toString();
        Answer.push_back(temp);
    }
    m_History->endArray();
    //===============[3]
}

void CHistory::SaveData(QString Key, const std::vector<CShape*> &Paper, const std::vector<QString> &Answer, double Grade)
{
	int NumOfTest = m_History->value("NumOfTest", 0).toInt();
	NumOfTest++;
	m_History->setValue("NumOfTest", NumOfTest);
    //记下此次的测试，历史记录
    m_History->setValue("KeySize", Key.size());
    //保存试卷=====[1]
    m_History->beginWriteArray(Key+"/Paper");
    for(int i=0;i<Paper.size();i++)
    {
        m_History->setArrayIndex(i);
        QString name = Paper[i]->GetClassName();
        m_History->setValue(QString::number(i), name);
        //保存一个图形的信息===[2]
        m_History->setValue(name+"/Color", Paper[i]->GetColor()); //int
        m_History->beginWriteArray(name+"/Points");
        //其位置点
        vector<QPointF> Ponits = Paper[i]->GetPoints();
        for (int j = 0; j < Ponits.size(); j++)
        {
            m_History->setArrayIndex(j);
            m_History->setValue(QString::number(j), Ponits[j]);
        }
        m_History->endArray();
        //=============[2]
    }
    m_History->endArray();
    //=============[1]
    //保存用户回答=====[3]
    m_History->beginWriteArray(Key+"/Answer");
    for(int i=0;i<Answer.size();i++)
    {
        m_History->setArrayIndex(i);
        m_History->setValue(QString::number(i),Answer[i]);
    }
    m_History->endArray();
    //============[3]
    m_History->setValue(Key+"/NumOfPaper", Paper.size());
	m_History->setValue(Key + "/Grade", Grade);

	CHistory::FlashData();
}

bool CHistory::GetClearAuto()
{
	return IsClearAuto;
}

void CHistory::SetClearAuto(bool Clear)
{
	IsClearAuto = Clear;
	m_History->setValue("ClearAuto", IsClearAuto);
}

int CHistory::GetMaxData()
{
	return m_History->value("MaxData", 2).toInt();
}

void CHistory::SetMaxData(int Max)
{
	if (IsClearAuto)
		m_History->setValue("MaxData", Max);
}

void CHistory::FlashData()
{
	if (IsClearAuto)
	{
		int size = m_History->value("NumOfTest", 0).toInt();
		int Max = m_History->value("MaxData", 2).toInt();
		if (size >Max)
		{
			QStringList Key = m_History->childGroups();
			QStringList PopKey;
			for (int i = 0; i < size - Max; i++)
			{
				PopKey.append(Key.at(i));
			}
			for (int i = 0; i < PopKey.size(); i++)
			{
				m_History->remove(PopKey.at(i));
			}
		}
		m_History->setValue("NumOfTest", Max);
	}
}

bool CHistory::GetPaperUnlimted()
{
	PaperUnlimted = m_History->value("PaperUnlimted", true).toBool();
	return PaperUnlimted;
}

int CHistory::GetPaperNum()
{
	return m_History->value("PaperNum",1).toInt();
}

void CHistory::SetPaperUnlimted(bool Unlimted)
{
	PaperUnlimted = Unlimted;
	m_History->setValue("PaperUnlimted", Unlimted);
}

void CHistory::SetPaperNum(int Num)
{
	if (!PaperUnlimted)
	{
		m_History->setValue("PaperNum", Num);
	}
}