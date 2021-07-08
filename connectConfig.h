#pragma once
#include<QDialog>//对话窗口类
#include<QDialogButtonBox>//对话框按钮组
#include<QMessageBox>//标准对话框
#include<QPushButton>//按钮事件
#include<QFormLayout>//表单布局
#include<QLineEdit>//行编辑器
#include<QComboBox>//下拉框
#include<QtSql>//数据库
class connectConfig :public QDialog
{
	Q_OBJECT
private:
	QFormLayout* layout;//布局器
	QComboBox* kindBox;//数据库类型
	QLineEdit* hostLine;//主机名
	QLineEdit* dataLine;//数据库名
	QLineEdit* userLine;//用户名
	QLineEdit* portLine;//端口号
	QLineEdit* passwordLine;//密码
	QLineEdit* connectLine;//连接名
	QDialogButtonBox* btn;
	QSqlDatabase* db;//数据库
private slots:
	void link();
public:
	connectConfig(QWidget* parent = nullptr);
	~connectConfig() {
		delete kindBox; delete hostLine; delete dataLine; delete userLine;
		delete portLine; delete passwordLine; delete btn; delete layout;
	}
	QSqlDatabase* getDB() { return db; }
};
