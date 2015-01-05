#ifndef CTEST_H
#define CTEST_H
#include <vector>
#include <fstream>
#include "cshape.h"
#include "ctest.h"
#include <QSettings>
#include <QtCore>

class CTest
{
public:
	CTest();
	CTest(const CTest &) = delete;
	~CTest();
	//开始新的测试，返回第一个图形
	CShape* NewTest();
	//结束测试，保存历史
	void EndTest();
	//返回当前的正确答案
	QString GetNowKey();
	void RemoveData()
	{
		remove("Test.txt");
	}

	void Save();
	bool Read();
	void LoginData(const QString &DataKey, CShape**problem, QString &answer);
	/*
	 * 如果还在测试中，获得下一个问题。
     *      如果是在看前面的题目，获得下一个题目所做的回答，如果是新的一道题，answer为""
     * 如果提交后在回看答案，获得下一个题目和测试者的回答（若没有下一题了则为NULL和""）
	 */
	void GetNext(CShape **problem, QString &answer);
	/*
     * 如果还在测试中，获得上一个问题和上一个题目所做的回答，若没有上一题了，为NULL和""
     * 如果提交后在回看答案，获得上一个题目和测试者的回答（若没有上一题了则为NULL和""）
	 */
	void GetPrev(CShape** problem, QString &answer);
	//设置当前题目的答案
	void SetAnswer(QString answer);
	bool HavePrev();
	bool HaveNext();
	//获得现在的问题
	CShape* GetNowPro()
	{
		return m_Paper[m_NowProblem - 1];
	}

	double GetGrade();
	void SetNumUnlimted(bool Unlimte);
	void SetPaperNum(int Num);

private:
	std::vector<CShape*> m_Paper;//题目
	std::vector<QString> m_Answer;//测试者的回答
	bool m_IsEnded;//是否结束
	bool m_NumUnlimited;//题目数量是否无限制
//	int m_PaperNum;//题目数量，在无限制时有用
	int m_NumProblems;//问题总数目
	int m_NowProblem;//当前问题序号（从1开始）
    QSettings * m_History;
};

#endif // CTEST_H
