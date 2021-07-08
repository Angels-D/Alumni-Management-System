#pragma once
#include <QDockWidget>//停靠窗口
#include <QMenu>//菜单
#include <QAction>//工具按钮
#include <QTableView>//表格类
#include "FindWidget.h"//数据查找类
#include "FilterHeaderView.h"//自定义表头
#include "ShowFilterWidget.h"//自定义筛选框
#include "connectConfig.h"//链接设置窗口类
#include "dataWindow.h"//详细窗口类
#include "mainWindow.h"
//表格数据视窗
class tableWindow :public QDockWidget
{
	Q_OBJECT
private:
	QSqlDatabase* db;
	QWidget* Parent;//父窗口
	QTableView* tableview;//数据表格
	QMenu* menu;//菜单
	QAction* RefreshAction;//菜单-刷新
	QAction* AddAction;//菜单-添加
	QAction* FindAction;//菜单-查找
	QAction* PeopleAction;//用户数据
	QAction* SchoolAction;//学校数据
	QAction* CompanyAction;//公司数据
	QSharedPointer<CShowFilterWidget> showFilter;//筛选框
	QSqlRelationalTableModel* model;//数据模型
	QString* Filter;//筛选设置
	FindWidget* findwidget;//查找视窗
	void resizeEvent(QResizeEvent*);//自适应窗口
public:
	tableWindow(QSqlDatabase* DB = nullptr, QWidget* parent = nullptr);
	~tableWindow();
private slots:
	void dataClick(const QModelIndex& index);
	void Menu(const QPoint& pos) { menu->exec(this->parentWidget()->pos() + pos + QPoint(30, 130)); }
	void refresh();//右键菜单-刷新
	void add();//右键菜单-增加
	void find();//右键菜单-查找（支持正则表达式）
	void showPeople();
	void showSchool();
	void showCompany();
	void onDelete(int row);
	void onFilterClicked(const int section);
	void onHeaderDataChanged(Qt::Orientation orientation, int first, int last);
	void onFilterHide(int section);
};
