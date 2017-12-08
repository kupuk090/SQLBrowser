#ifndef MYSORTFILTERPROXYMODEL_H
#define MYSORTFILTERPROXYMODEL_H

#include <QVariant>
#include <QtSql/QtSql>
#include <QtSql/QSqlQuery>
#include <QSortFilterProxyModel>
#include <QtConcurrent/QtConcurrent>
#include "sortings.h"


enum MySortingMethods { QtMap, QuickSort, HeapSort, StableSort, SimpleSort, TimSort, ShellSort };

class MySortFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    MySortFilterProxyModel(QObject *parent = 0);
    ~MySortFilterProxyModel();
    void setSortedList(int column, Qt::SortOrder order);
    void sort(int column, Qt::SortOrder order);
    void magic(int column, Qt::SortOrder order);

protected:
    QModelIndex mapFromSource(const QModelIndex &sourceIndex) const;
    QModelIndex mapToSource(const QModelIndex &proxyIndex) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

private:
    QList<int> *sortedList;
    MySortingMethods choice;

public slots:
    void revertList();
    void giveSortChoice(MySortingMethods ch);
};


class StProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    mutable int m_time = 0;
    StProxyModel(QObject *parent = 0);
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const;
};


#endif // MYSORTFILTERPROXYMODEL_H
