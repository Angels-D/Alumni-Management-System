#include "dataWindow.h"
void peopleWindow::save()
{
	if (!mapper->submit()) {
		QMessageBox::warning(NULL, QStringLiteral("Error"),
			model->lastError().text(),
			QMessageBox::Yes);
	}
	else close();
}
void peopleWindow::remove()
{
	if (!model->removeRow(Row)) {
		QMessageBox::warning(NULL, QStringLiteral("Error"),
			model->lastError().text(),
			QMessageBox::Yes);
	}
	else close();
}
peopleWindow::peopleWindow(const int& row, QWidget* parent, QSqlRelationalTableModel* Model)
	: QDialog(parent, Qt::WindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint | Qt::WindowCloseButtonHint)),
	Row(row), model(Model),
	idEdit(new QLineEdit(this)), nameEdit(new QLineEdit(this)), phoneEdit(new QLineEdit(this)), majorBox(new QComboBox(this)),
	jobBox(new QComboBox(this)), workBox(new QComboBox(this)), timeEdit(new QLineEdit(this)), addressEdit(new QLineEdit(this)),
	schoolBox(new QComboBox(this)), companyBox(new QComboBox(this)),
	btn(new QDialogButtonBox(QDialogButtonBox::Save | QDialogButtonBox::No | QDialogButtonBox::Cancel, this)),
	layout(new QFormLayout(this)),
	mapper(new QDataWidgetMapper(this))
{
    mapper->setModel(model);//绑定模型
    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);//设置手动保存
    //绑定关系表、设置可编辑
	majorBox->setModel(model->relationModel(4)); majorBox->setEditable(true);
	majorBox->setModelColumn(model->relationModel(4)->fieldIndex("name"));
	jobBox->setModel(model->relationModel(5)); jobBox->setEditable(true);
	jobBox->setModelColumn(model->relationModel(5)->fieldIndex("name"));
	workBox->setModel(model->relationModel(6)); workBox->setEditable(true);
	workBox->setModelColumn(model->relationModel(6)->fieldIndex("name"));
	schoolBox->setModel(model->relationModel(9)); schoolBox->setEditable(true);
	schoolBox->setModelColumn(model->relationModel(9)->fieldIndex("name"));
	companyBox->setModel(model->relationModel(10)); companyBox->setEditable(true);
	companyBox->setModelColumn(model->relationModel(10)->fieldIndex("name"));
    //绑定到模型数据
	mapper->addMapping(majorBox, 4); mapper->addMapping(jobBox, 5);
	mapper->addMapping(workBox, 6); mapper->addMapping(schoolBox, 9);
	mapper->addMapping(companyBox, 10);
	mapper->addMapping(idEdit, model->fieldIndex("Id"));
	mapper->addMapping(nameEdit, model->fieldIndex("Name"));
	mapper->addMapping(phoneEdit, model->fieldIndex("Phone"));
	mapper->addMapping(timeEdit, model->fieldIndex("Time"));
	mapper->addMapping(addressEdit, model->fieldIndex("Address"));
    mapper->setCurrentIndex(row);//定位数据行
    //自动排布
	layout->addRow("Id:", idEdit); layout->addRow("Name:", nameEdit); layout->addRow("Phone", phoneEdit);
	layout->addRow("Major:", majorBox); layout->addRow("Job", jobBox); layout->addRow("Work", workBox);
	layout->addRow("Time:", timeEdit); layout->addRow("Address:", addressEdit);
	layout->addRow("School:", schoolBox); layout->addRow("Company:", companyBox);
	layout->addRow(btn);
    //设置标题
	if (model->index(row, 2).data().isNull()) setWindowTitle("New");
	else setWindowTitle(model->index(row, 2).data().toString());
	btn->button(QDialogButtonBox::No)->setText(tr("Remove"));
    //绑定信号槽
	connect(btn->button(QDialogButtonBox::Save), SIGNAL(clicked()), this, SLOT(save()));
	connect(btn->button(QDialogButtonBox::No), SIGNAL(clicked()), this, SLOT(remove()));
	connect(btn->button(QDialogButtonBox::Cancel), SIGNAL(clicked()), this, SLOT(close()));
}
peopleWindow::~peopleWindow()
{
	delete idEdit; delete nameEdit; delete phoneEdit; delete majorBox;
	delete jobBox; delete workBox; delete timeEdit; delete addressEdit;
	delete schoolBox; delete companyBox;
    delete btn; delete layout;delete mapper;
}
void schoolWindow::save()
{
    if (!mapper->submit()) {
        QMessageBox::warning(NULL, QStringLiteral("Error"),
            model->lastError().text(),
            QMessageBox::Yes);
    }
    else close();
}
void schoolWindow::remove()
{
    if (!model->removeRow(Row)) {
        QMessageBox::warning(NULL, QStringLiteral("Error"),
            model->lastError().text(),
            QMessageBox::Yes);
    }
    else close();
}
schoolWindow::schoolWindow(const int& row, QWidget* parent, QSqlRelationalTableModel* Model)
	: QDialog(parent, Qt::WindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint | Qt::WindowCloseButtonHint)),
	Row(row), model(Model),
	idEdit(new QLineEdit(this)), nameEdit(new QLineEdit(this)),
    propertiesBox(new QComboBox(this)), addressEdit(new QLineEdit(this)),
	btn(new QDialogButtonBox(QDialogButtonBox::Save | QDialogButtonBox::No | QDialogButtonBox::Cancel, this)),
    layout(new QFormLayout(this)),
    mapper(new QDataWidgetMapper(this))
{
    mapper->setModel(model);
    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    propertiesBox->setModel(model->relationModel(4)); propertiesBox->setEditable(true);
    propertiesBox->setModelColumn(model->relationModel(4)->fieldIndex("name"));
    mapper->addMapping(propertiesBox, 4);
    mapper->addMapping(idEdit, model->fieldIndex("Id"));
    mapper->addMapping(nameEdit, model->fieldIndex("Name"));
    mapper->addMapping(addressEdit, model->fieldIndex("Address"));
    mapper->setCurrentIndex(row);
    layout->addRow("Id:", idEdit); layout->addRow("Name:", nameEdit);
    layout->addRow("Address:", addressEdit);layout->addRow("Properties:",propertiesBox);
    layout->addRow(btn);
    if (model->index(row, 2).data().isNull()) setWindowTitle("New");
    else setWindowTitle(model->index(row, 2).data().toString());
    btn->button(QDialogButtonBox::No)->setText(tr("Remove"));
    connect(btn->button(QDialogButtonBox::Save), SIGNAL(clicked()), this, SLOT(save()));
    connect(btn->button(QDialogButtonBox::No), SIGNAL(clicked()), this, SLOT(remove()));
    connect(btn->button(QDialogButtonBox::Cancel), SIGNAL(clicked()), this, SLOT(close()));
}
schoolWindow::~schoolWindow()
{
	delete idEdit; delete nameEdit;
    delete propertiesBox; delete addressEdit;
    delete btn; delete layout;delete mapper;
}
void companyWindow::save()
{
    if (!mapper->submit()) {
        QMessageBox::warning(NULL, QStringLiteral("Error"),
            model->lastError().text(),
            QMessageBox::Yes);
    }
    else close();
}
void companyWindow::remove()
{
    if (!model->removeRow(Row)) {
        QMessageBox::warning(NULL, QStringLiteral("Error"),
            model->lastError().text(),
            QMessageBox::Yes);
    }
    else close();
}
companyWindow::companyWindow(const int& row, QWidget* parent, QSqlRelationalTableModel* Model)
	: QDialog(parent, Qt::WindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint | Qt::WindowCloseButtonHint)),
	Row(row), model(Model),
	nameEdit(new QLineEdit(this)), propertiesBox(new QComboBox(this)),
	addressEdit(new QLineEdit(this)), tradeBox(new QComboBox(this)), scaleBox(new QComboBox(this)),
	btn(new QDialogButtonBox(QDialogButtonBox::Save | QDialogButtonBox::No | QDialogButtonBox::Cancel, this)),
    layout(new QFormLayout(this)),
    mapper(new QDataWidgetMapper(this))
{
    mapper->setModel(model);
    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    tradeBox->setModel(model->relationModel(3)); tradeBox->setEditable(true);
    tradeBox->setModelColumn(model->relationModel(3)->fieldIndex("name"));
    propertiesBox->setModel(model->relationModel(4)); propertiesBox->setEditable(true);
    propertiesBox->setModelColumn(model->relationModel(4)->fieldIndex("name"));
    scaleBox->setModel(model->relationModel(5)); scaleBox->setEditable(true);
    scaleBox->setModelColumn(model->relationModel(5)->fieldIndex("name"));
    mapper->addMapping(tradeBox, 3);
    mapper->addMapping(propertiesBox, 4);
    mapper->addMapping(scaleBox, 5);
    mapper->addMapping(nameEdit, model->fieldIndex("Name"));
    mapper->addMapping(addressEdit, model->fieldIndex("Address"));
    mapper->setCurrentIndex(row);
    layout->addRow("Name:", nameEdit);layout->addRow("Address:", addressEdit);
    layout->addRow("Trade:",tradeBox);layout->addRow("Properties:", propertiesBox);
    layout->addRow("Scale:",scaleBox);
    layout->addRow(btn);
    if (model->index(row, 2).data().isNull()) setWindowTitle("New");
    else setWindowTitle(model->index(row, 2).data().toString());
    btn->button(QDialogButtonBox::No)->setText(tr("Remove"));
    connect(btn->button(QDialogButtonBox::Save), SIGNAL(clicked()), this, SLOT(save()));
    connect(btn->button(QDialogButtonBox::No), SIGNAL(clicked()), this, SLOT(remove()));
    connect(btn->button(QDialogButtonBox::Cancel), SIGNAL(clicked()), this, SLOT(close()));
}
companyWindow::~companyWindow()
{
	delete nameEdit; delete propertiesBox; delete addressEdit;
	delete tradeBox; delete scaleBox;
    delete btn; delete layout;delete mapper;
}
