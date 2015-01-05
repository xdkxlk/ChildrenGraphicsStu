#ifndef CHISTORY_H
#define CHISTORY_H
#include <QSettings>
#include <QString>
#include <vector>
#include "cshape.h"

class CHistory
{
public:
    CHistory();
	static int GetPaperNum();
	static bool GetPaperUnlimted();
	static void SetPaperUnlimted(bool Unlimted);
	static void SetPaperNum(int Num);
	static void FlashData();
	static bool GetClearAuto();
	static void SetClearAuto(bool Clear);
	static void SetMaxData(int Max);
	static int GetMaxData();
    static void CloseHisFile();
    static int KeySize();
    static QStringList GetDataHead();
    static void Remove(QString Key);
    static void GetData(QString Key, std::vector<CShape*> &Paper, std::vector<QString> &Answer);
    static void SaveData(QString Key, const std::vector<CShape*> &Paper, const std::vector<QString> &Answer, double Grade);
private:
    static QSettings * m_History;
	static bool IsClearAuto;
	static bool PaperUnlimted;
};

#endif // CHISTORY_H
