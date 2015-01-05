#include "ctest.h"
#include "cfactory.h"
#include <QDate>
#include <QDateTime>
#include <sstream>
#include <string>
#include "chistory.h"
using std::getline;
using std::string;
using std::stringstream;
using std::ofstream;
using std::ifstream;
using std::ios;
using std::endl;
using std::vector;

CTest::CTest()
{
	m_NowProblem = 0;
	m_NumProblems = 0;
	m_IsEnded = false;
	m_NumUnlimited = CHistory::GetPaperUnlimted();
	if (!m_NumUnlimited)
		m_NumProblems =  CHistory::GetPaperNum();
   // m_History = new QSettings("data.ini",QSettings::IniFormat);
}

CTest::~CTest()
{
	for (int i = 0; i < m_Paper.size(); i++)
	{
		if (m_Paper[i] != NULL)
			delete m_Paper[i];
		m_Paper[i] = NULL;
	}
//    delete m_History;
}

CShape *CTest::NewTest()
{
	m_NowProblem = 1;
	m_NumProblems = 1;
	m_NumUnlimited = CHistory::GetPaperUnlimted();
	if (!m_NumUnlimited)
	{
		m_NumProblems = CHistory::GetPaperNum();
	}
	m_IsEnded = false;
	for (int i = 0; i < m_Paper.size(); i++)
	{
		if (m_Paper[i]!=NULL)
			delete m_Paper[i];
		m_Paper[i] = NULL;
	}
	m_Paper.clear();
	m_Answer.clear();
	if (m_NumUnlimited)
	{
		CShape *shape = CFactory::GetNewRandShape();
		m_Paper.push_back(shape);
	}
	else
	{
		for (int i = 0; i < m_NumProblems; i++)
		{
			CShape *shape = CFactory::GetNewRandShape();
			m_Paper.push_back(shape);
		}
	}
	return m_Paper[0];
}

void CTest::EndTest()
{
	m_IsEnded = true;
    QString key = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    CHistory::SaveData(key, m_Paper, m_Answer,GetGrade());
}


void CTest::LoginData(const QString &DataKey, CShape**problem, QString &answer)
{
    for (int i = 0; i < m_Paper.size(); i++)
    {
        if (m_Paper[i] != NULL)
            delete m_Paper[i];
        m_Paper[i] = NULL;
    }
    m_Paper.clear();
    m_Answer.clear();
    CHistory::GetData(DataKey,m_Paper,m_Answer);
    m_IsEnded = true;
    m_NowProblem = 1;
    m_NumProblems = m_Paper.size();
    *problem = m_Paper[0];
    answer = m_Answer[0];
}

void CTest::SetNumUnlimted(bool Unlimte)
{
	m_NumUnlimited = Unlimte;
	CHistory::SetPaperUnlimted(Unlimte);
}

void CTest::SetPaperNum(int Num)
{
	CHistory::SetPaperNum(Num);
}

QString CTest::GetNowKey()
{
	return m_Paper[m_NowProblem - 1]->GetClassName();
}

bool CTest::HavePrev()
{
	if (m_NowProblem <= 1)
		return false;
	else
		return true;
}

bool CTest::HaveNext()
{
	if (m_IsEnded && m_NumUnlimited)
	{
		if (m_NowProblem == m_NumProblems)
			return false;
		else
			return true;
	}
	else if (!m_IsEnded && m_NumUnlimited)
		return true;
	else if (!m_NumUnlimited)
	{
		if (m_NowProblem == m_NumProblems)
		{
			m_IsEnded = true;
			return false;
		}
		else
			return true;
	}
}

void CTest::GetNext(CShape **problem, QString &answer)
{
	if (!m_IsEnded)
	{
		if (m_NowProblem == m_NumProblems && m_NowProblem == m_Answer.size())
		{
			m_NowProblem++;
			m_NumProblems++;
			CShape *shape = CFactory::GetNewRandShape();
			m_Paper.push_back(shape);
			*problem = shape;
			answer = "";
		}
		else
		{
			m_NowProblem++;
			if (!m_NumUnlimited)
			{
				if (m_NowProblem == m_NumProblems)
					m_IsEnded = true;
			}
			*problem = m_Paper[m_NowProblem - 1];
			if (m_NowProblem - 1 == m_Answer.size())
				answer = "";
			else
				answer = m_Answer[m_NowProblem - 1];
		}
	}
	else
	{
		m_NowProblem++;
		if (m_NowProblem <= m_NumProblems)
		{
			*problem = m_Paper[m_NowProblem - 1];
			answer = m_Answer[m_NowProblem - 1];
		}
		else
		{
			m_NowProblem--;
			*problem = NULL;
			answer = "";
		}

	}
}

void CTest::GetPrev(CShape **problem, QString &answer)
{
	if (m_NowProblem == 1)
	{
		*problem = NULL;
		answer = "";
	}
	else
	{
		m_NowProblem--;
		*problem = m_Paper[m_NowProblem - 1];
		answer = m_Answer[m_NowProblem - 1];
	}
}

void CTest::SetAnswer(QString answer)
{
	if (m_NowProblem == m_Answer.size() + 1)
	{
		m_Answer.push_back(answer);
	}
	else
		m_Answer[m_NowProblem - 1] = answer;
}

double CTest::GetGrade()
{
	int NumRight = 0;
	for (int i = 0; i < m_Answer.size(); i++)
	{
		if (m_Answer[i] == m_Paper[i]->GetClassName())
			NumRight++;
	}
	return ((int)((1.0*NumRight / m_NumProblems) * 1000)) / 10.0;
}

void CTest::Save()
{
	/*
	 * Test（测试进度保存方法，仅在正在进行测试时保存）
	 * [line 1] m_NowProblem m_NumProblems
	 * [line 2]  m_Answer[0~end]
	 * （以下行为保存m_Paper，从m_Paper[0]开始保存，一个下标一行，每行的格式如下）
	 * [line 3] (string)ClassName  color  [vector<QPointF> Points]的每一个点（Points为每种图形的组成端点）
	 */
	ofstream file("Test.txt");
	file << m_NowProblem << " " << m_NumProblems << endl;
	for (unsigned int i = 0; i < m_Answer.size(); i++)
		file << m_Answer[i].toStdString() << " ";
	file << endl;
	for (unsigned int i = 0; i < m_Paper.size(); i++)
	{
		file << m_Paper[i]->GetClassName().toStdString() << " " << m_Paper[i]->GetColor() << " ";
		vector<QPointF> Points = m_Paper[i]->GetPoints();
		for (unsigned int j = 0; j < Points.size(); j++)
			file << Points[j].x() << " " << Points[j].y() << " ";
		file << endl;
	}
	file.close();
}

bool CTest::Read()
{
	m_IsEnded = false;
	ifstream file("Test.txt");
	if (file.fail())
	{
		file.close();
		return false;
	}

	string read;
	getline(file, read);
	stringstream ReadNum(read);
	ReadNum >> m_NowProblem >> m_NumProblems;



	getline(file, read);
	stringstream StringLine(read);
	string Model;
	while (StringLine >> Model)
	{
		m_Answer.push_back(QString::fromStdString(Model));
	}

	while (getline(file, read))
	{
		stringstream ReadLine(read);
		vector<QPointF> Points;
		CShape *Problem;
		double x, y;
		int color;
		ReadLine >> Model >> color;

		while (ReadLine >> x >> y)
		{
			QPointF Point(x, y);
			Points.push_back(Point);
		}
		Problem = CFactory::GetShapeFromClassName(QString::fromStdString(Model));
		Problem->SetShape(Points, (Qt::GlobalColor)color);
		m_Paper.push_back(Problem);
	}

	file.close();
	return true;
}
