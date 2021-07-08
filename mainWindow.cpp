#include "mainWindow.h"
aboutWindow::aboutWindow(QWidget* parent)
	:QDialog(parent, Qt::WindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint | Qt::WindowCloseButtonHint)),
	author(new QLabel("Author: " + _author, this)),
	email(new QLabel("Email: " + _email, this)),
	qq(new QLabel("QQ: " + _qq, this)),
	date(new QLabel("Date: " + _date, this)),
	edition(new QLabel("Edition: " + _edition, this)),
	image(new QLabel(this)),
	layout(new QFormLayout(this))
{
	setWindowTitle("About");
	image->setPixmap(QPixmap(":/image.ico").scaled(64, 64, Qt::KeepAspectRatio));
	//布局
	layout->addRow(image); layout->addRow(author);
	layout->addRow(email); layout->addRow(qq);
	layout->addRow(date); layout->addRow(edition);
	setLayout(layout);
}
mainWindow::mainWindow(QWidget* parent)
	:QMainWindow(parent),
	aboutwindow(new aboutWindow(this)),
	toolBar(addToolBar("Menu")),
	connectAction(toolBar->addAction("&Connect")),
	aboutAction(toolBar->addAction("&About")),
	tablewindow(new QList<tableWindow*>)
{
	setWindowTitle("Alumni System");
	resize(parent->size() / 1.5);//自适应屏幕分辨率
	toolBar->setMovable(false);//设置工具栏不可移动
	setDockNestingEnabled(true);//允许浮动窗口
	setContextMenuPolicy(Qt::NoContextMenu);//关闭右键菜单
	//绑定触发器
	connectAction->setShortcut(QKeySequence(tr("ALT+C")));
	aboutAction->setShortcut(QKeySequence(tr("ALT+A")));
	connect(connectAction, &QAction::triggered, this, &mainWindow::connectActionSlot);
	connect(aboutAction, &QAction::triggered, this, &mainWindow::aboutActionSlot);
}
mainWindow::~mainWindow()
{
	for (auto i : *tablewindow)  removeDockWidget(i);
	delete toolBar;
	delete aboutwindow;
	delete tablewindow;
}
void mainWindow::connectActionSlot()
{
	connectConfig connectconfig(this);
	connectconfig.show();
	connectconfig.exec();
	if (!connectconfig.getDB()) return;
	tablewindow->append(new tableWindow(connectconfig.getDB(), this));
	if (tablewindow->size() == 1)addDockWidget(Qt::BottomDockWidgetArea, *(tablewindow->end() - 1));
	else tabifyDockWidget(*tablewindow->begin(), *(tablewindow->end() - 1));
}
