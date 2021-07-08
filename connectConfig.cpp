#include "connectConfig.h"
void connectConfig::link()
{
	//查重
	if (QSqlDatabase::contains(connectLine->text())) {
		QMessageBox::warning(NULL, QStringLiteral("Warn"),
			"Connect name repetition\nPlease change connect",
			QMessageBox::Yes);
		return;
	}
	db = new QSqlDatabase(QSqlDatabase::addDatabase(kindBox->currentText(), connectLine->text()));
	//设置连接信息
	db->setHostName(hostLine->text());
	db->setDatabaseName(dataLine->text());
	db->setUserName(userLine->text());
	db->setPort(portLine->text().toUInt());
	db->setPassword(passwordLine->text());
	//链接
	if (!db->open()) {
		QMessageBox::warning(NULL, QStringLiteral("Error"),
			db->lastError().text(),
			QMessageBox::Yes);
		delete db;
		db = nullptr;
		QSqlDatabase::removeDatabase(connectLine->text());
	}
	else close();
}
connectConfig::connectConfig(QWidget* parent)
	:QDialog(parent, Qt::WindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint | Qt::WindowCloseButtonHint)),
	layout(new QFormLayout(this)),
	kindBox(new QComboBox(this)),
	hostLine(new QLineEdit("localhost", this)),
	dataLine(new QLineEdit("Alumni", this)),
	userLine(new QLineEdit("AnglesD", this)),
	portLine(new QLineEdit("3306", this)),
	passwordLine(new QLineEdit(this)),
	connectLine(new QLineEdit(this)),
	btn(new QDialogButtonBox(QDialogButtonBox::Yes | QDialogButtonBox::Cancel, this)),
	db(nullptr)
{
	setWindowTitle("Connect Config");
	layout->addRow("Model:", kindBox); layout->addRow("Connect:", connectLine);
	layout->addRow("Host:", hostLine); layout->addRow("Data:", dataLine);
	layout->addRow("User:", userLine); layout->addRow("Port:", portLine);
	layout->addRow("Password:", passwordLine); layout->addRow(btn);
	setLayout(layout);
	btn->button(QDialogButtonBox::Yes)->setText(tr("Connect"));
	kindBox->addItem("QMYSQL");
	passwordLine->setEchoMode(QLineEdit::Password);
	portLine->setValidator(new QIntValidator(0, 25565, portLine));
	connect(btn, &QDialogButtonBox::accepted, this, &connectConfig::link);
	connect(btn, &QDialogButtonBox::rejected, this, &connectConfig::close);
}
