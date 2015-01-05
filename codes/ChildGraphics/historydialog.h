#ifndef HISTORYDIALOG_H
#define HISTORYDIALOG_H

#include <QDialog>
#include <QStringList>
#include <QPushButton>
#include "hislistwidget.h"

class HistoryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HistoryDialog(QString &DataKey,QWidget *parent = 0);
    ~HistoryDialog();

private slots:

    void on_ButtonDelete_clicked();

    void on_listWidget_doubleClicked(const QModelIndex &index);

    void SubmitLoginData();

private:
	QString &m_DataKey;
    HisListWidget *List;
    QPushButton *DeleteButton;
    QPushButton *ReadButton;
};

#endif // HISTORYDIALOG_H
