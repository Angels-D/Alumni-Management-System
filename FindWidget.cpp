#include "FindWidget.h"
void FindWidget::Next()
{
	QRegExp exp(findEdit->text());
	for (int row = Findrow + 1; row < tableview->model()->rowCount(); row++)
		for (int col = 0; col < tableview->model()->columnCount(); col++)
			if (exp.exactMatch(tableview->model()->index(row, col).data().toString())) {
				tableview->selectRow(Findrow = row);
				return;
			}
	QMessageBox::warning(NULL, QStringLiteral("Warn"),
		"Can't find the next massage!",
		QMessageBox::Yes);
}
void FindWidget::Last()
{
	QRegExp exp(findEdit->text());
	for (int row = Findrow - 1; row >= 0; row--)
		for (int col = 0; col < tableview->model()->columnCount(); col++)
			if (exp.exactMatch(tableview->model()->index(row, col).data().toString())) {
				tableview->selectRow(Findrow = row);
				return;
			}
	QMessageBox::warning(NULL, QStringLiteral("Warn"),
		"Can't find the last massage!",
		QMessageBox::Yes);
}
FindWidget::FindWidget(QTableView* table, QWidget* parent)
	:QDialog(parent, Qt::WindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint | Qt::WindowCloseButtonHint)),
	Findrow(-1),
	btn(new QDialogButtonBox(QDialogButtonBox::Yes | QDialogButtonBox::No, this)),
	findEdit(new QLineEdit(this)),
	layout(new QVBoxLayout(this)),
	tableview(table)
{
	setWindowTitle("Find");
	btn->button(QDialogButtonBox::Yes)->setText(tr("Next"));
	btn->button(QDialogButtonBox::No)->setText(tr("Last"));
	layout->addWidget(findEdit);
	layout->addWidget(btn);
	connect(btn, &QDialogButtonBox::accepted, this, &FindWidget::Next);
	connect(btn, &QDialogButtonBox::rejected, this, &FindWidget::Last);
}
