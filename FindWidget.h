#pragma once
#include<QDialog>
#include<QDialogButtonBox>
#include<QLineEdit>
#include<QVBoxLayout>
#include<QPushButton>
#include<QTableView>
#include<QMessageBox>
#include<QRegExp>//正则表达式
class FindWidget : public QDialog
{
private:
	int Findrow;
	QDialogButtonBox* btn;
	QLineEdit* findEdit;
	QVBoxLayout* layout;
	QTableView* tableview;
private slots:
	void Next();
	void Last();
public:
	FindWidget(QTableView* table, QWidget* parent = nullptr);
	~FindWidget() { delete btn; delete findEdit; delete layout; }
};
