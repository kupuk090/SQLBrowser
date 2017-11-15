#ifndef MYSORTFILTERPROXYMODEL_H
#define MYSORTFILTERPROXYMODEL_H

#include <QVariant>
#include <QtSql/QtSql>
#include <QtSql/QSqlQuery>
#include <QSortFilterProxyModel>

class MySortFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    MySortFilterProxyModel(QObject *parent = 0);
    ~MySortFilterProxyModel();
    void setSortedList(int column, Qt::SortOrder order);

protected:
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const;
    void sort(int column, Qt::SortOrder order);
    QModelIndex mapFromSource(const QModelIndex &sourceIndex) const;
    QModelIndex mapToSource(const QModelIndex &proxyIndex) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

private:
    QList<int> *sortedList;

public slots:
    void revertList();

signals:
    void updateTable() const;
};

#endif // MYSORTFILTERPROXYMODEL_H
