#include "settingdialog.h"
#include "ui_settingdialog.h"
#include "chistory.h"

SettingDialog::SettingDialog(int &PaperNum, int &MaxData, QWidget *parent) : m_PaperNum(PaperNum), m_MaxData(MaxData),
    QDialog(parent),
    ui(new Ui::SettingDialog)
{
	m_PaperNum = -1;
	m_MaxData = -1;
    ui->setupUi(this);
	setWindowTitle(QString::fromUtf8(""));
	ui->PspinBoxNum->setRange(1, 100);
	ui->HspinBoxDelDay->setRange(2, 100);
	ui->HradioAutoDel->setChecked(CHistory::GetClearAuto());
	ui->PradioFix->setChecked(!CHistory::GetPaperUnlimted());
	SetPEnableSlot();
	SetHEnableSlot();
	connect(ui->PradioFix, SIGNAL(toggled(bool)), this, SLOT(SetPEnableSlot()));
	connect(ui->HradioAutoDel, SIGNAL(toggled(bool)), this, SLOT(SetHEnableSlot()));
	connect(ui->pushButtonSubmit, SIGNAL(clicked()), this, SLOT(SubmitSlot()));
}

SettingDialog::~SettingDialog()
{
    delete ui;
}

void SettingDialog::SetHEnableSlot()
{
	bool Enable = ui->HradioAutoDel->isChecked();
	ui->HlabelDelDay->setEnabled(Enable);
	ui->HspinBoxDelDay->setEnabled(Enable);
	ui->HspinBoxDelDay->setValue(CHistory::GetMaxData());
}

void SettingDialog::SetPEnableSlot()
{
	bool Enable = ui->PradioFix->isChecked();
	ui->PlabelNum->setEnabled(Enable);
	ui->PspinBoxNum->setEnabled(Enable);
	ui->PspinBoxNum->setValue(CHistory::GetPaperNum());
}

void SettingDialog::SubmitSlot()
{
	if (ui->HradioAutoDel->isChecked())
		m_MaxData = ui->HspinBoxDelDay->value();
	else
		m_MaxData = -1;
	if (ui->PradioFix->isChecked())
		m_PaperNum = ui->PspinBoxNum->value();
	else
		m_PaperNum = -1;
}