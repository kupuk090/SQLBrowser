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
    void setPrevColumn(int value);
    void setSorted(bool value);

protected:
    QModelIndex mapFromSource(const QModelIndex &sourceIndex) const;
    QModelIndex mapToSource(const QModelIndex &proxyIndex) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

private:
    QList<int> *sortedList;
    MySortingMethods choice;
    int prevColumn;
    bool sorted;

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


void worker(QVector<Container> *arr,
            void (*sortFunc)(QVector<Container>::Iterator, QVector<Container>::Iterator),
            int threadCount = QThread::idealThreadCount());

void myMerge(QVector<Container> *arr,
             int count = (QThread::idealThreadCount() / 2));


#endif // MYSORTFILTERPROXYMODEL_H
