#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QRadioButton>
#include <qpushbutton.h>
#include <vector>
#include <string>
#include <map>
#include "cshape.h"
#include "ctest.h"
#include "cstudy.h"

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();
protected:
	void closeEvent(QCloseEvent * e);

	private slots:

	void on_StuRadio_clicked();

	void on_StuButtonAgain_clicked();

	void on_TestStart_clicked();

	void on_TestButtonNext_clicked();

	void on_TestButtonPrev_clicked();

	void on_TestRadio_clicked();

	void on_TestSubmit_clicked();

	void on_TestKeys_clicked();

    void on_action_triggered();

    void on_action_2_triggered();

private:
	MainWindow(const MainWindow &);
	MainWindow & operator = (const MainWindow &);
	Ui::MainWindow *ui;

	void RemoveData();
	void Save();
	void Read();

    CStudy m_Stu;
	std::vector<QRadioButton*> m_StuRadioButton;
    CShape *StuShape;
    QString StuModel;
	QGraphicsScene *StuScene;
	QString m_StuNowChoice();
	void m_StuInitRadio();

	std::vector<QRadioButton*> m_TestRadioButton;
	QPushButton* TestButtonPrev;
	QPushButton* TestButtonNext;
	CShape *TestShape;
	QGraphicsScene *TestScene;
	QGraphicsTextItem *TestShowKey;
	void m_TestInitAnswerBox();

	CTest m_Test;
	QString m_TestChoose;
	bool m_IsLookingKeys;
	bool m_IsTesting;

	void m_TDrawShape(CShape* shape);//在测试模式中绘制形状
	QString m_TGetAnswer();//获得测试模式中的radio所选项
	void m_TSetAnswer(QString shape);//设置测试模式中radio的选择，若没有过去的选择就选择TestRadioNone
	void m_TClearAnswer();//测试模式中清空选项（选上不可见的TestRadioNone）
	void m_TWriteKey(QString Key, QString Answer);//测试模式回看答案中显示对答案正误的判定，若错误则显示正确答案
};

#endif // MAINWINDOW_H
