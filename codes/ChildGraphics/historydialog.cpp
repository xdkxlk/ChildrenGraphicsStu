#include "historydialog.h"
#include "chistory.h"
#include <QDateTime>
#include <QString>
#include <QDebug>
#include <qmessagebox.h>
#include <QListWidgetItem>
#include <QHBoxLayout>
#include <QVBoxLayout>
HistoryDialog::HistoryDialog(QString &DataKey, QWidget *parent) :
QDialog(parent), m_DataKey(DataKey)
{
    List = new HisListWidget(this);
    QHBoxLayout *Layout = new QHBoxLayout(this);
    QVBoxLayout *BLayout = new QVBoxLayout(this);
    DeleteButton = new QPushButton(QString::fromUtf8("\xe5\x88\xa0\xe9\x99\xa4"),this); //É¾³ý
	ReadButton = new QPushButton(QString::fromUtf8("\xe8\xbd\xbd\xe5\x85\xa5"), this);  //ÔØÈë
    BLayout->addStretch();
    BLayout->addWidget(DeleteButton);
    BLayout->addWidget(ReadButton);
    Layout->addWidget(List);
    Layout->addLayout(BLayout);
    setLayout(Layout);
	setWindowTitle(QString::fromUtf8("\xE5\x8E\x86\xE5\x8F\xB2"));//ÀúÊ·
    List->addItems(CHistory::GetDataHead());
    List->setCurrentRow(0);
    if (List->count() == 0)
	{
        DeleteButton->setEnabled(false);
        ReadButton->setEnabled(false);
	}
    connect(List,SIGNAL(Delete()),this,SLOT(on_ButtonDelete_clicked()));
    connect(List,SIGNAL(Login()),this,SLOT(SubmitLoginData()));
    connect(List,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(on_listWidget_doubleClicked(QModelIndex)));
    connect(DeleteButton,SIGNAL(clicked()),this,SLOT(on_ButtonDelete_clicked()));
    connect(ReadButton,SIGNAL(clicked()),this,SLOT(SubmitLoginData()));
}

HistoryDialog::~HistoryDialog()
{
}

void HistoryDialog::on_ButtonDelete_clicked()
{
	QMessageBox *Box = new QMessageBox(QMessageBox::Icon::Warning, QString::fromUtf8("\xe8\xad\xa6\xe5\x91\x8a"), QString::fromUtf8("\xe7\xa1\xae\xe5\xae\x9a\xe5\x88\xa0\xe9\x99\xa4\xe6\xad\xa4\xe6\x9d\xa1\xe5\x8e\x86\xe5\x8f\xb2\xe8\xae\xb0\xe5\xbd\x95"));
	QPushButton *Ok = new QPushButton(QString::fromUtf8("\xe7\xa1\xae\xe5\xae\x9a"), this);
	QPushButton *Cancel = new QPushButton(QString::fromUtf8("\xe5\x8f\x96\xe6\xb6\x88"), this);
	Box->addButton(Ok, QMessageBox::ButtonRole::AcceptRole);
	Box->addButton(Cancel, QMessageBox::ButtonRole::RejectRole);
	Box->exec();
	if (Box->clickedButton()==Ok)
	{
        QString str = List->currentItem()->text();
		QString temp;
        int size = CHistory::KeySize();
		for (int i = 0; i < size; i++)
		{
			temp.append(str.at(i));
		}
        CHistory::Remove(temp);
        List->takeItem(List->currentRow());
        if (List->count() == 0)
		{
            DeleteButton->setEnabled(false);
            ReadButton->setEnabled(false);
		}
	}
}

void HistoryDialog::on_listWidget_doubleClicked(const QModelIndex &index)
{
	SubmitLoginData();
}

void HistoryDialog::SubmitLoginData()
{
    QString str = List->currentItem()->text();
	QString temp;
    int size = CHistory::KeySize();
	for (int i = 0; i < size; i++)
	{
		temp.append(str.at(i));
	}
	m_DataKey = temp;
	disconnect(ReadButton, SIGNAL(clicked()), this, SLOT(SubmitLoginData()));
    connect(ReadButton, SIGNAL(clicked()), this, SLOT(accept()));
    emit ReadButton->clicked();
}
