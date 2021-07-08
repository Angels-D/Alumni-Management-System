#pragma once
#include <QDialog>//对话窗口
#include <QMainWindow>//主窗口类
#include <QToolBar>//工具栏类
#include <QAction>//工具按钮
#include <QLabel>//标签类
#include <QFormLayout>
#include "tablewindow.h"
#include "information.h"//作者注信息
class tableWindow;
//关于视窗
class aboutWindow : public QDialog
{
	Q_OBJECT
private:
	//显示信息
	QLabel* author; QLabel* email;
	QLabel* qq; QLabel* date;
	QLabel* edition; QLabel* image;
	QFormLayout* layout;
public:
	aboutWindow(QWidget* parent = nullptr);
	~aboutWindow() { delete email; delete qq; delete author; delete date; delete edition; delete image; delete layout; }
};
//主视窗
class mainWindow :public QMainWindow
{
	Q_OBJECT
private:
	aboutWindow* aboutwindow;
	QToolBar* toolBar;//工具栏
	QAction* connectAction;//工具栏按钮-连接
	QAction* aboutAction;//工具栏按钮-关于
private slots:
	void connectActionSlot();
	void aboutActionSlot() { aboutwindow->show(); }
public:
	QList<tableWindow*>* tablewindow;//数据视窗列表
	mainWindow(QWidget* parent = nullptr);
	~mainWindow();
};
