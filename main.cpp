#include <QApplication>
#include <QFile>
#include "mainWindow.h"
int main(int argc, char* argv[])
{
	QApplication alumni(argc, argv);
	QFile file(":/style_sheet.qss");
	if (file.open(QIODevice::ReadOnly)) { alumni.setStyleSheet(file.readAll()); }
	mainWindow mainwindow((QWidget*)QApplication::desktop());
	mainwindow.show();
	return alumni.exec();
}
