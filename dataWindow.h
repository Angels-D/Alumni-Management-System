#pragma once
#include<QDialog>//对话窗口类
#include<QDialogButtonBox>//对话框按钮组
#include<QMessageBox>//标准对话框
#include<QPushButton>//按钮事件
#include<QFormLayout>//排布器
#include<QLineEdit>//行编辑器
#include<QComboBox>//下拉框
#include<QtSql>//数据库
#include<QDataWidgetMapper>//数据映射
#include"Data_S.h"
//用户视窗
class peopleWindow :public QDialog
{
	Q_OBJECT
private:
	PEOPLE* people;
	const int Row;
	QSqlRelationalTableModel* model;
	QLineEdit* idEdit; QLineEdit* nameEdit; QLineEdit* phoneEdit; QComboBox* majorBox;
	QComboBox* jobBox; QComboBox* workBox; QLineEdit* timeEdit; QLineEdit* addressEdit;
	QComboBox* schoolBox; QComboBox* companyBox;
	QDialogButtonBox* btn;
	QFormLayout* layout;
	QDataWidgetMapper* mapper;
private slots:
	void save();
	void remove();
	void cancel() { if (windowTitle() == "New") model->removeRow(model->rowCount() - 1); close(); }
public:
	peopleWindow(const int& row, QWidget* parent = nullptr, QSqlRelationalTableModel* Model = nullptr);
	~peopleWindow();
};
//学校视窗
class schoolWindow :public QDialog
{
	Q_OBJECT
private:
	SCHOOL* school;
	const int Row;
	QSqlRelationalTableModel* model;
	QLineEdit* idEdit; QLineEdit* nameEdit;
    QComboBox* propertiesBox; QLineEdit* addressEdit;
	QDialogButtonBox* btn;
	QFormLayout* layout;
    QDataWidgetMapper* mapper;
private slots:
    void save();
    void remove();
    void cancel() { if (windowTitle() == "New") model->removeRow(model->rowCount() - 1); close(); }
public:
	schoolWindow(const int& row, QWidget* parent = nullptr, QSqlRelationalTableModel* Model = nullptr);
	~schoolWindow();
};
//公司视窗
class companyWindow :public QDialog
{
	Q_OBJECT
private:
	COMPANY* company;
	const int Row;
	QSqlRelationalTableModel* model;
	QLineEdit* nameEdit; QComboBox* propertiesBox;
	QLineEdit* addressEdit; QComboBox* tradeBox; QComboBox* scaleBox;
	QDialogButtonBox* btn;
	QFormLayout* layout;
    QDataWidgetMapper* mapper;
private slots:
    void save();
    void remove();
    void cancel() { if (windowTitle() == "New") model->removeRow(model->rowCount() - 1); close(); }
public:
	companyWindow(const int& row, QWidget* parent = nullptr, QSqlRelationalTableModel* Model = nullptr);
	~companyWindow();
};
