#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cfactory.h"
#include "chistory.h"
#include "historydialog.h"
#include "settingdialog.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QCloseEvent>
#include <QFontDatabase>
#include <QFont>
#include <QTextStream>
#include <QFile>
using std::vector;
using std::string;

MainWindow::MainWindow(QWidget *parent) :
QMainWindow(parent),
ui(new Ui::MainWindow)
{
	CHistory::FlashData();
	ui->setupUi(this);
	//上一题
	TestButtonPrev = new QPushButton(QString::fromUtf8("\xE4\xB8\x8A\xE4\xB8\x80\xE9\xA2\x98"), this);
	//下一题
	TestButtonNext = new QPushButton(QString::fromUtf8("\xE4\xB8\x8B\xE4\xB8\x80\xE9\xA2\x98"), this);
	TestButtonPrev->setEnabled(false);
	TestButtonNext->setEnabled(false);
	connect(TestButtonPrev, SIGNAL(clicked()), this, SLOT(on_TestButtonPrev_clicked()));
	connect(TestButtonNext, SIGNAL(clicked()), this, SLOT(on_TestButtonNext_clicked()));
	StuScene = new QGraphicsScene(this);
	TestScene = new QGraphicsScene(this);
	ui->graphicsViewStu->setScene(StuScene);
	ui->graphicsViewTest->setScene(TestScene);

	m_StuInitRadio();
	m_TestInitAnswerBox();

	ui->TestRadioNone->hide();//用于需要把所有的选项清空时，就选择这个None选项

	for (int i = 0; i < m_TestRadioButton.size(); i++)
		m_TestRadioButton[i]->setEnabled(false);

	TestShape = NULL;
	StuShape = NULL;
	TestShowKey = NULL;
	m_IsLookingKeys = false;
	m_IsTesting = false;

	QFile file("ui.txt");
	if (file.exists())
	{
		file.close();
		QMessageBox Box(QMessageBox::Question, QString::fromUtf8("\xE8\xAF\xA2\xE9\x97\xAE") /*询问*/
			, QString::fromUtf8("\xe5\x8f\x91\xe7\x8e\xb0\xe6\x9c\x89\xe6\xb2\xa1\xe6\x9c\x89\xe5\x81\x9a\xe5\xae\x8c\xe7\x9a\x84\xe6\xb5\x8b\xe8\xaf\x95 , \xe6\x98\xaf\xe5\x90\xa6\xe7\xbb\xa7\xe7\xbb\xad\xe6\xb5\x8b\xe8\xaf\x95 ?"));
		//发现有没有做完的测试，是否继续
		QPushButton *Ok = new QPushButton(QString::fromUtf8("\xE7\xBB\xA7\xE7\xBB\xAD")); //继续
		QPushButton *No = new QPushButton(QString::fromUtf8("\xE6\x94\xBE\xE5\xBC\x83 , \xE9\x87\x8D\xE6\x96\xB0\xE5\xBC\x80\xE5\xA7\x8B"));
		//放弃，重新开始
		Box.addButton(Ok, QMessageBox::AcceptRole);
		Box.addButton(No, QMessageBox::RejectRole);
		Box.exec();
		if (Box.clickedButton() == Ok)
			Read();
		else
			RemoveData();

		delete Ok;
		delete No;
	}
	else
		file.close();
}

void MainWindow::closeEvent(QCloseEvent * e)
{
	if (m_IsTesting)
	{
		QMessageBox Box(QMessageBox::Question, QString::fromUtf8("\xE8\xAF\xA2\xE9\x97\xAE") /*询问*/
			, QString::fromUtf8("\xE6\x98\xAF\xE5\x90\xA6\xE4\xBF\x9D\xE5\xAD\x98\xE6\xB5\x8B\xE8\xAF\x95\xE8\xBF\x9B\xE5\xBA\xA6 ?"));
		//是否保存测试进度?
		QPushButton *SaveBut = new QPushButton(QString::fromUtf8("\xE4\xBF\x9D\xE5\xAD\x98\xE5\xB9\xB6\xE9\x80\x80\xE5\x87\xBA")); //保存并退出
		QPushButton *Discard = new QPushButton(QString::fromUtf8("\xE6\x94\xBE\xE5\xBC\x83\xE5\xB9\xB6\xE9\x80\x80\xE5\x87\xBA")); //放弃并退出
		QPushButton *Cancel = new QPushButton(QString::fromUtf8("\xE5\x8F\x96\xE6\xB6\x88")); //取消
		Box.addButton(SaveBut, QMessageBox::AcceptRole);
		Box.addButton(Discard, QMessageBox::ApplyRole);
		Box.addButton(Cancel, QMessageBox::RejectRole);
		Box.setDefaultButton(SaveBut);
		Box.exec();

		if (Box.clickedButton() == SaveBut)
			Save();
		else if (Box.clickedButton() == Cancel)
			e->ignore();

		delete SaveBut;
		delete Discard;
		delete Cancel;
	}
}

void MainWindow::RemoveData()
{
	//删除存档
	remove("ui.txt");
	m_Test.RemoveData();
}

void MainWindow::Save()
{
	m_Test.Save();

	/*
	 * ui文件保存方法
	 * [01] “下一题”按钮的状态
	 * [02]
	 * 如果“下一题”按钮 IsEnabled 则说明现在这道题已经选择了答案，则保存现在的选择
	 * 否则不保存，结束保存
	 */
	QFile file("ui.txt");
	file.open(QIODevice::WriteOnly);
	QTextStream stream(&file);
	stream << TestButtonNext->isEnabled() << " ";
	if (TestButtonNext->isEnabled())
	{
		stream << m_TGetAnswer();
	}
	file.close();
}

void MainWindow::Read()
{
	if (m_Test.Read())//如果m_Test 成功读入（有存档时）
	{
		m_IsTesting = true;
		for (int i = 0; i < m_TestRadioButton.size(); i++)
			m_TestRadioButton[i]->setEnabled(true);
		TestButtonPrev->setEnabled(m_Test.HavePrev());
		ui->TestStart->setEnabled(false);
		TestScene->addItem(m_Test.GetNowPro());
		TestShape = m_Test.GetNowPro();

		QFile file("ui.txt");
		file.open(QIODevice::ReadOnly);
		QTextStream stream(&file);
		int IsEnable;
		stream >> IsEnable;
		if (IsEnable == (int)true) //当前题目已经做了
		{
			QString answer;
			stream >> answer;
			m_TSetAnswer(answer);
			TestButtonNext->setEnabled(true);
			ui->TestSubmit->setEnabled(true);
		}
		else
		{
			TestButtonNext->setEnabled(false);
			m_TSetAnswer("");
		}
		file.close();

		RemoveData();
	}
}

void MainWindow::m_StuInitRadio()
{
	vector<QString> ShapeName = CFactory::GetShapeName();

	QVBoxLayout *StuVLayout = new QVBoxLayout(this);
	QHBoxLayout *StuHLayout = new QHBoxLayout(this);
	int i = 0, num;
	num = (ShapeName.size() / 4) * 4;
	for (; i < num; i++)
	{
		QRadioButton *temp = new QRadioButton(ShapeName[i], this);
		m_StuRadioButton.push_back(temp);
		StuHLayout->addWidget(temp);
		if ((i + 1) % 4 == 0)
		{
			StuVLayout->addLayout(StuHLayout);
			StuHLayout = new QHBoxLayout(this);
		}
		connect(temp, SIGNAL(clicked()), this, SLOT(on_StuRadio_clicked()));
	}
	if (i != ShapeName.size())
	{
		StuHLayout = new QHBoxLayout(this);
		for (; i < ShapeName.size(); i++)
		{
			QRadioButton *temp = new QRadioButton(ShapeName[i], this);
			connect(temp, SIGNAL(clicked()), this, SLOT(on_StuRadio_clicked()));
			m_StuRadioButton.push_back(temp);
			StuHLayout->addWidget(temp);
		}
		StuHLayout->addStretch();
		StuVLayout->addLayout(StuHLayout);
	}
	ui->StugroupBox->setLayout(StuVLayout);
}

QString MainWindow::m_StuNowChoice()
{
	for (int i = 0; i < m_StuRadioButton.size(); i++)
	{
		if (m_StuRadioButton[i]->isChecked())
			return m_StuRadioButton[i]->text();
	}
	return "";
}

void MainWindow::on_StuRadio_clicked()
{
	ui->StuButtonAgain->setEnabled(true);
	QString NowChoice = m_StuNowChoice();
	if (StuModel != NowChoice)
	{
		StuScene->removeItem(StuShape);
		StuModel = NowChoice;
		StuShape = m_Stu.GetShape(NowChoice);
		StuScene->addItem(StuShape);
	}
}

void MainWindow::on_StuButtonAgain_clicked()
{
	StuScene->removeItem(StuShape);
	StuShape = m_Stu.GetShapeAgain();
	StuScene->addItem(StuShape);
}

MainWindow::~MainWindow()
{
	if (TestShowKey != NULL)
	{
		delete TestShowKey;
		TestShowKey = NULL;
	}
	delete ui;
}

//=======================================================
void MainWindow::m_TestInitAnswerBox()
{
	vector<QString> ShapeName = CFactory::GetShapeName();

	QVBoxLayout *TestVLayout = new QVBoxLayout(this);
	QHBoxLayout *TestHLayout = new QHBoxLayout(this);
	int i = 0, num;
	num = (ShapeName.size() / 4) * 4;
	for (; i < num; i++)
	{
		QRadioButton *temp = new QRadioButton(ShapeName[i], this);
		m_TestRadioButton.push_back(temp);
		TestHLayout->addWidget(temp);
		if ((i + 1) % 4 == 0)
		{
			TestVLayout->addLayout(TestHLayout);
			TestHLayout = new QHBoxLayout(this);
		}
		connect(temp, SIGNAL(clicked()), this, SLOT(on_TestRadio_clicked()));
	}
	if (i != ShapeName.size())
	{
		TestHLayout = new QHBoxLayout(this);
		for (; i < ShapeName.size(); i++)
		{
			QRadioButton *temp = new QRadioButton(ShapeName[i], this);
			connect(temp, SIGNAL(clicked()), this, SLOT(on_TestRadio_clicked()));
			m_TestRadioButton.push_back(temp);
			TestHLayout->addWidget(temp);
		}
		TestHLayout->addStretch();
		TestVLayout->addLayout(TestHLayout);
	}
	TestHLayout = new QHBoxLayout(this);
	TestHLayout->addWidget(TestButtonPrev);
	TestHLayout->addWidget(TestButtonNext);
	TestVLayout->addLayout(TestHLayout);

	ui->TestBoxAnswer->setLayout(TestVLayout);
}

void MainWindow::on_TestStart_clicked()
{
	m_TClearAnswer();
	TestScene->removeItem(TestShape);
	m_IsTesting = true;
	if (m_IsLookingKeys)
	{
		TestScene->removeItem(TestShowKey);
		delete TestShowKey;
		TestShowKey = NULL;
	}
	TestShape = NULL;
	ui->TestStart->setEnabled(false);
	ui->TestSubmit->setEnabled(false);
	ui->TestKeys->setEnabled(false);

	for (int i = 0; i < m_TestRadioButton.size(); i++)
		m_TestRadioButton[i]->setEnabled(true);
	TestButtonPrev->setEnabled(false);
	TestButtonNext->setEnabled(false);

	m_TDrawShape(m_Test.NewTest());
	m_IsLookingKeys = false;
}

void MainWindow::on_TestRadio_clicked()
{
	if (!m_IsLookingKeys)
	{
		if (m_Test.HaveNext())
		{
			TestButtonNext->setEnabled(true);
		}
		ui->TestSubmit->setEnabled(true);
	}
}

void MainWindow::on_TestButtonNext_clicked()
{
	if (!m_IsLookingKeys)//如果没有再看答案
	{
		m_Test.SetAnswer(m_TGetAnswer());
		CShape* NextPro;
		QString NextAns;
		m_Test.GetNext(&NextPro, NextAns);
		m_TSetAnswer(NextAns);
		m_TDrawShape(NextPro);
		if (NextAns == "")//如果现在这个问题还没有回答
		{
			m_TClearAnswer();
			TestButtonNext->setEnabled(false);
			ui->TestSubmit->setEnabled(false);
		}
		else if(m_Test.HaveNext())//如果在看已经答过的问题
		{
			TestButtonNext->setEnabled(true);
			ui->TestSubmit->setEnabled(true);
		}
		if (m_Test.HavePrev())
		{
			TestButtonPrev->setEnabled(true);
		}
	}
	else//如果在看答案
	{
		CShape* NextPro;
		QString NextAns;
		m_Test.GetNext(&NextPro, NextAns);
		m_TSetAnswer(NextAns);
		m_TDrawShape(NextPro);
		m_TWriteKey(NextPro->GetClassName(), NextAns);
		if (m_Test.HavePrev())//有上一个问题时
		{
			TestButtonPrev->setEnabled(true);
		}
		if (!m_Test.HaveNext())//有下一个问题时
		{
			TestButtonNext->setEnabled(false);
		}
	}
}

void MainWindow::on_TestButtonPrev_clicked()
{
	if (!m_IsLookingKeys)
	{
		m_Test.SetAnswer(m_TGetAnswer());//获得当前答案
		CShape* PrevPro;
		QString PrevAns;
		m_Test.GetPrev(&PrevPro, PrevAns);//得到储存的上一个问题和回答
		m_TSetAnswer(PrevAns);//设置回答
		m_TDrawShape(PrevPro);//绘制形状
		TestButtonNext->setEnabled(true);//应为在看上一题时一定有下一题，故TestButtonNext可点击
		ui->TestSubmit->setEnabled(true);
		if (!m_Test.HavePrev())
		{
			TestButtonPrev->setEnabled(false);
		}
	}
	else
	{
		CShape* PrevPro;
		QString PrevAns;
		m_Test.GetPrev(&PrevPro, PrevAns);
		m_TSetAnswer(PrevAns);
		m_TDrawShape(PrevPro);
		m_TWriteKey(PrevPro->GetClassName(), PrevAns);
		if (!m_Test.HavePrev())//没有上一个问题时
		{
			TestButtonPrev->setEnabled(false);
		}
		if (m_Test.HaveNext())//有下一个问题时
		{
			TestButtonNext->setEnabled(true);
		}
	}
}

void MainWindow::on_TestSubmit_clicked()
{
	ui->tab->setEnabled(true);
	m_IsTesting = false;
	m_Test.SetAnswer(m_TGetAnswer());
	double Grade = m_Test.GetGrade();
	QString info(QString::fromUtf8("\xe6\x82\xa8\xe7\x9a\x84\xe6\x88\x90\xe7\xbb\xa9\xe4\xb8\xba "));//“您的分数为 ”
	info += QString::number(Grade);
	info += QString::fromUtf8(" \xe5\x88\x86");
	QMessageBox::information(this, QString::fromUtf8("\xe6\x88\x90\xe7\xbb\xa9"), info);
	ui->TestSubmit->setEnabled(false);
	ui->TestStart->setEnabled(true);
	ui->TestKeys->setEnabled(true);

	for (int i = 0; i < m_TestRadioButton.size(); i++)
		m_TestRadioButton[i]->setEnabled(false);

	TestButtonNext->setEnabled(false);
	TestButtonPrev->setEnabled(false);

	m_Test.EndTest();
}

void MainWindow::on_TestKeys_clicked()
{
	m_IsLookingKeys = true;

	QString NowKey = m_Test.GetNowKey();
	QString Choose = m_TGetAnswer();

	ui->TestKeys->setEnabled(false);
	if (m_Test.HaveNext())
	{
		TestButtonNext->setEnabled(true);
	}
	if (m_Test.HavePrev())
	{
		TestButtonPrev->setEnabled(true);
	}
	m_TWriteKey(NowKey, Choose);
}

void MainWindow::m_TWriteKey(QString Key, QString Answer)
{
	QPoint Move(-200, 100);
	const int FontSize = 15;
	if (TestShowKey != NULL)
	{
		TestScene->removeItem(TestShowKey);
		delete TestShowKey;
		TestShowKey = NULL;
	}
	if (Key == Answer)
	{
		QString string = QString::fromUtf8("\xe6\xad\xa3\xe7\xa1\xae");//"正确"
		TestShowKey = TestScene->addText(string, QFont("STCaiyun", FontSize, QFont::Bold));
		TestShowKey->moveBy(Move.x(), Move.y());
	}
	else
	{
		QString string = QString::fromUtf8("\xe9\x94\x99\xe8\xaf\xaf,\xe4\xbd\xa0\xe9\x80\x89\xe6\x8b\xa9\xe7\x9a\x84\xe6\x98\xaf ");
		//"错误,你选择的是 "
		string += CFactory::TransNamToReaName(Answer);
		string += QString::fromUtf8(" \xe6\xad\xa3\xe7\xa1\xae\xe7\xad\x94\xe6\xa1\x88\xe6\x98\xaf ");//正确答案是
		string += CFactory::TransNamToReaName(Key);
		TestShowKey = TestScene->addText(string, QFont("STCaiyun", FontSize, QFont::Bold));
		TestShowKey->moveBy(Move.x(), Move.y());
	}
}

void MainWindow::m_TDrawShape(CShape* shape)
{
	if (shape != NULL)
	{
		TestScene->removeItem(TestShape);
		TestShape = shape;
		TestScene->addItem(shape);
	}
}

QString MainWindow::m_TGetAnswer()
{
	for (int i = 0; i < m_TestRadioButton.size(); i++)
	{
		if (m_TestRadioButton[i]->isChecked())
			return CFactory::TransNamToClassName(m_TestRadioButton[i]->text());
	}
	return "";
}

void MainWindow::m_TSetAnswer(QString shape)
{
	if (shape == "")
	{
		ui->TestRadioNone->setChecked(true);
		return;
	}
	for (int i = 0; i < m_TestRadioButton.size(); i++)
	{
		if (CFactory::TransNamToClassName(m_TestRadioButton[i]->text())
			== shape)
			m_TestRadioButton[i]->setChecked(true);
	}
}

void MainWindow::m_TClearAnswer()
{
	ui->TestRadioNone->setChecked(true);
}
void MainWindow::on_action_triggered()
{
    QString DataKey;
	HistoryDialog Dialog(DataKey, this);
	if (Dialog.exec() != QDialog::Accepted)
		return;
	QString answer;
	m_Test.LoginData(DataKey, &TestShape, answer);
	m_TDrawShape(TestShape);
	m_TSetAnswer(answer);
	ui->tabWidget->setCurrentIndex(1);
	ui->TestKeys->setEnabled(false);
	TestButtonPrev->setEnabled(false);
	if (m_Test.HaveNext())
		TestButtonNext->setEnabled(true);
	else
		TestButtonNext->setEnabled(false);
	m_TWriteKey(TestShape->GetClassName(), answer);
	m_IsLookingKeys = true;
	m_IsTesting = false;
}

void MainWindow::on_action_2_triggered()//设置
{
	int PaperNum, MaxData;
	SettingDialog Set(PaperNum, MaxData, this);
	if (Set.exec()==QDialog::Accepted)
	{
		if (MaxData != -1)
		{
			CHistory::SetClearAuto(true);
			CHistory::SetMaxData(MaxData);
			CHistory::FlashData();
		}
		else
			CHistory::SetClearAuto(false);
		if (PaperNum != -1)
		{
			m_Test.SetNumUnlimted(false);
			m_Test.SetPaperNum(PaperNum);
		}
		else
			m_Test.SetNumUnlimted(true);
	}
}
