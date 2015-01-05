#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>

namespace Ui {
class SettingDialog;
}

class SettingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingDialog(int &PaperNum, int &MaxData, QWidget *parent = 0);
    ~SettingDialog();
private slots:
	void SetHEnableSlot();
	void SetPEnableSlot();
	void SubmitSlot();
private:
    Ui::SettingDialog *ui;
	int &m_PaperNum;
	int &m_MaxData;
};

#endif // SETTINGDIALOG_H
