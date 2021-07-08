#pragma once
#include <QWidget>
#include <QMap>
#include <QList>
#include <QListView>
#include <QStandardItemModel>
#include <QHBoxLayout>
#include <QPainter>
#include <QBitmap>
QT_BEGIN_NAMESPACE
class QListView;
class QStandardItemModel;
class QStandardItem;
QT_END_NAMESPACE
class CShowFilterWidget : public QWidget
{
	Q_OBJECT
public:
	explicit CShowFilterWidget(QWidget* parent = nullptr);
private Q_SLOTS:
	void onItemCliked(const QModelIndex& index);
Q_SIGNALS:
	void filterHide(int section);
public:
	void addFilter(int section);
	void addData(int section, const QString& strData);
	void removeData(int section, const QString& strData);
	void showFilter(int section);
	QList<int> filter() const;
	QList<QString> getSelectData() const;
protected:
	virtual void hideEvent(QHideEvent* event);
	virtual void paintEvent(QPaintEvent* event);
private:
	QMap<int, QMap<QString, bool> > m_filterData;
	int m_currentSection = -1;
	QListView* m_listView = nullptr;
	QStandardItemModel* m_model = nullptr;
	QList<QStandardItem*> m_items;
};
