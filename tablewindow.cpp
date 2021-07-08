#include"tablewindow.h"
void tableWindow::resizeEvent(QResizeEvent*)
{
	if (isFloating()) {
		tableview->resize(size().width(), size().height());
		tableview->move(0, 0);
	}
	else {
		tableview->resize(size().width(), size().height() - 20);
		tableview->move(0, 20);
	}
}
tableWindow::tableWindow(QSqlDatabase* DB, QWidget* parent)
	:QDockWidget(parent),
	db(DB),
	Parent(parent),
	tableview(new QTableView(this)),
	menu(new QMenu(tableview)),
	RefreshAction(new QAction("Refresh", menu)),
	AddAction(new QAction("Add", menu)),
	FindAction(new QAction("Find", menu)),
	PeopleAction(new QAction("People", menu)),
	SchoolAction(new QAction("School", menu)),
	CompanyAction(new QAction("Company", menu)),
	model(new QSqlRelationalTableModel(tableview, *db)),
	Filter(nullptr),
	findwidget(new FindWidget(tableview, this))
{
	setWindowTitle(db->connectionName());
	setAttribute(Qt::WA_DeleteOnClose);//窗口关闭时自动销毁
	//设置
	tableview->setSortingEnabled(true);//可排序
	tableview->setEditTriggers(QAbstractItemView::NoEditTriggers);//不可编辑
	tableview->setSelectionBehavior(QAbstractItemView::SelectRows);//选中行
	tableview->setContextMenuPolicy(Qt::CustomContextMenu);//右击菜单
	tableview->setModel(model);//绑定模型
	CFilterHeaderView* header = new CFilterHeaderView(tableview);//自定义表头
	header->setSectionResizeMode(QHeaderView::Stretch);//自适应窗口
	tableview->setHorizontalHeader(header);//绑定表头
	connect(tableview, &QTableView::doubleClicked, this, &tableWindow::dataClick);
	connect(tableview, &QTableView::customContextMenuRequested, this, &tableWindow::Menu);
	//右键菜单
	QMenu* menu_s(menu->addMenu("Data"));
	menu_s->addAction(PeopleAction);
	menu_s->addAction(SchoolAction);
	menu_s->addAction(CompanyAction);
	menu->addAction(AddAction);
	menu->addAction(RefreshAction);
	menu->addAction(FindAction);
	connect(PeopleAction, &QAction::triggered, this, &tableWindow::showPeople);
	connect(SchoolAction, &QAction::triggered, this, &tableWindow::showSchool);
	connect(CompanyAction, &QAction::triggered, this, &tableWindow::showCompany);
	connect(AddAction, &QAction::triggered, this, &tableWindow::add);
	connect(RefreshAction, &QAction::triggered, this, &tableWindow::refresh);
	connect(FindAction, &QAction::triggered, this, &tableWindow::find);
	//筛选设置
	connect(header, &CFilterHeaderView::filterClicked, this, &tableWindow::onFilterClicked);
	connect(tableview, &QAbstractItemView::clicked, header, &CFilterHeaderView::onUpdateCheckState);
	connect(model, &QAbstractItemModel::headerDataChanged, this, &tableWindow::onHeaderDataChanged);
	connect(model, &QSqlTableModel::beforeDelete, this, &tableWindow::onDelete);
	showPeople();//默认用户数据显示
}
tableWindow::~tableWindow()
{

	db->close();
	delete db; delete tableview;
	delete[]Filter; delete findwidget;
	QSqlDatabase::removeDatabase(windowTitle());
	((mainWindow*)Parent)->tablewindow->removeOne(this);

}
void tableWindow::dataClick(const QModelIndex& index)
{
	if (model->tableName() == "people") {
		peopleWindow peoplewindow(index.row(), this, model);
		peoplewindow.setWindowModality(Qt::ApplicationModal);
		peoplewindow.show();
		peoplewindow.exec();
	}
	else if (model->tableName() == "school") {
		schoolWindow schoolwindow(index.row(), this, model);
		schoolwindow.setWindowModality(Qt::ApplicationModal);
		schoolwindow.show();
		schoolwindow.exec();
	}
	else {
		companyWindow companywindow(index.row(), this, model);
		companywindow.setWindowModality(Qt::ApplicationModal);
		companywindow.show();
		companywindow.exec();
	}
	refresh();
}
void tableWindow::refresh()
{
	model->select();
	for (int row = 0; row < tableview->model()->rowCount(); row++)
		for (const auto col : showFilter->filter())
			showFilter->addData(col, tableview->model()->index(row, col).data().toString());
}
void tableWindow::add()
{
	if (!tableview->model()->insertRow(tableview->model()->rowCount())) {
		QMessageBox::warning(NULL, QStringLiteral("Error"),
			model->lastError().text(),
			QMessageBox::Yes);
	}
	else {
        if (model->tableName() == "people") {
            peopleWindow peoplewindow(tableview->model()->rowCount() - 1, this, model);
            peoplewindow.show();
            peoplewindow.exec();
        }
        else if (model->tableName() == "school") {
            schoolWindow schoolwindow(tableview->model()->rowCount() - 1, this, model);
            schoolwindow.show();
            schoolwindow.exec();
        }
        else{
            companyWindow companyindow(tableview->model()->rowCount() - 1, this, model);
            companyindow.show();
            companyindow.exec();
        }
		for (const auto col : showFilter->filter())
			showFilter->addData(col, tableview->model()->index(tableview->model()->rowCount() - 1, col).data().toString());
	}
}
void tableWindow::find()
{
	findwidget->show();
}
void tableWindow::onDelete(int row)
{
	for (const auto col : showFilter->filter()) {
		showFilter->removeData(col, model->index(row, col).data().toString());
		qDebug() << col << model->index(row, col).data().toString();
	}
}
void tableWindow::onFilterClicked(const int section)
{
	showFilter->move(cursor().pos() - QPoint(showFilter->width() / 2, 3));
    showFilter->showFilter(section);
}
void tableWindow::onHeaderDataChanged(Qt::Orientation orientation, int first, int last)
{
	for (int section = first; section <= last; ++section)
	{
		QVariant var = tableview->model()->headerData(section, orientation, FilterRole);
		if (var.isValid() && var.toBool()) showFilter->addFilter(section);
	}
}
void tableWindow::onFilterHide(int section)
{
	Filter[section].clear();//重新记录
	for (auto data : showFilter->getSelectData()) {
		Filter[section].append(model->relation(section).isValid() ?//判断关系表过滤
			tr("relTblAl_%1.%2 = '%3' OR ")
			.arg(section)
			.arg(model->relation(section).displayColumn())
			.arg(data) :
			tr("%1.%2 = '%3' OR ")
			.arg(model->tableName())
			.arg(model->headerData(section, Qt::Horizontal).toString())
			.arg(data));
	}
	Filter[section].remove(Filter[section].size() - 4, 4);//去末尾
	QString totalFilter;//整合条件
	for (int i = 0; i < model->columnCount(); i++)
		if (!Filter[i].isEmpty())
			totalFilter.append(tr("(%1) AND ").arg(Filter[i]));
	totalFilter.remove(totalFilter.size() - 5, 5);
	model->setFilter(totalFilter);
}
void tableWindow::showPeople()
{
	model->setTable("people");//指定数据表
	showFilter = QSharedPointer<CShowFilterWidget>(new CShowFilterWidget);
	connect(showFilter.get(), &CShowFilterWidget::filterHide, this, &tableWindow::onFilterHide);
	//设置关系表
	model->setRelation(4, QSqlRelation("major", "name", "name"));
	model->setRelation(5, QSqlRelation("job", "name", "name"));
	model->setRelation(6, QSqlRelation("work", "name", "name"));
	model->setRelation(9, QSqlRelation("school", "i", "name"));
	model->setRelation(10, QSqlRelation("company", "i", "name"));
	//重命名
	model->setHeaderData(4, Qt::Horizontal, "Major");
	model->setHeaderData(5, Qt::Horizontal, "Job");
	model->setHeaderData(6, Qt::Horizontal, "Work");
	model->setHeaderData(9, Qt::Horizontal, "School");
	model->setHeaderData(10, Qt::Horizontal, "Company");
	//隐藏列
	tableview->setColumnHidden(0, true);
	tableview->setColumnHidden(6, true);
	tableview->setColumnHidden(7, true);
	tableview->setColumnHidden(8, true);
	tableview->setColumnHidden(11, true);
	//设置筛选元件
	model->setHeaderData(4, Qt::Horizontal, true, FilterRole);
	model->setHeaderData(5, Qt::Horizontal, true, FilterRole);
	model->setHeaderData(9, Qt::Horizontal, true, FilterRole);
	model->setHeaderData(10, Qt::Horizontal, true, FilterRole);
	//设置索引
	if (Filter != nullptr)delete[]Filter;
	Filter = new QString[model->columnCount()];
	refresh();//刷新数据表
	PeopleAction->setDisabled(true);
	SchoolAction->setDisabled(false);
	CompanyAction->setDisabled(false);
}

void tableWindow::showSchool()
{
	model->setTable("school");
	showFilter = QSharedPointer<CShowFilterWidget>(new CShowFilterWidget);
	connect(showFilter.get(), &CShowFilterWidget::filterHide, this, &tableWindow::onFilterHide);
	model->setRelation(4, QSqlRelation("propertiess", "name", "name"));
	model->setHeaderData(4, Qt::Horizontal, "Properties");
	tableview->setColumnHidden(0, true);
	model->setHeaderData(4, Qt::Horizontal, true, FilterRole);
	if (Filter != nullptr)delete[]Filter;
	Filter = new QString[model->columnCount()];
	refresh();
	PeopleAction->setDisabled(false);
	SchoolAction->setDisabled(true);
	CompanyAction->setDisabled(false);
}

void tableWindow::showCompany()
{
	model->setTable("Company");
	showFilter = QSharedPointer<CShowFilterWidget>(new CShowFilterWidget);
	connect(showFilter.get(), &CShowFilterWidget::filterHide, this, &tableWindow::onFilterHide);
	model->setRelation(3, QSqlRelation("trade", "name", "name"));
	model->setRelation(4, QSqlRelation("propertiesc", "name", "name"));
	model->setRelation(5, QSqlRelation("scale", "name", "name"));
	model->setHeaderData(3, Qt::Horizontal, "Trade");
	model->setHeaderData(4, Qt::Horizontal, "Properties");
	model->setHeaderData(5, Qt::Horizontal, "Scale");
	tableview->setColumnHidden(0, true);
	model->setHeaderData(3, Qt::Horizontal, true, FilterRole);
	model->setHeaderData(4, Qt::Horizontal, true, FilterRole);
	model->setHeaderData(5, Qt::Horizontal, true, FilterRole);
	if (Filter != nullptr)delete[]Filter;
	Filter = new QString[model->columnCount()];
	refresh();
	PeopleAction->setDisabled(false);
	SchoolAction->setDisabled(false);
	CompanyAction->setDisabled(true);
}
