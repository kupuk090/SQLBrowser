#include "mysortfilterproxymodel.h"
#include <QDebug>
#include <QTime>


MySortFilterProxyModel::MySortFilterProxyModel(QObject *parent) : QSortFilterProxyModel(parent)
{
    sortedList = new QList<int>();
    connect(this, SIGNAL(modelReset()), this, SLOT(revertList()));
}

MySortFilterProxyModel::~MySortFilterProxyModel()
{
}

void MySortFilterProxyModel::sort(int column, Qt::SortOrder order)
{
    QTime timer;
    timer.start();

    setSortedList(column, order);
//    qDebug() << "Сортировка по столбцу" << sourceModel()->headerData(column, Qt::Horizontal).toString()
//             << "в направлении" << order << "заняла: " << timer.elapsed() << "ms";
}

//вернуть индекс прокси модели который соответствует индексу исходной модели
QModelIndex MySortFilterProxyModel::mapFromSource(const QModelIndex &sourceIndex) const
{
    if (!sourceIndex.isValid())
        return QModelIndex();
    else
    {
        if (sortedList->isEmpty())
            return QSortFilterProxyModel::mapFromSource(sourceIndex);
        else
            return createIndex(sortedList->indexOf(sourceIndex.row()),sourceIndex.column());
    }
}

//вернуть индекс исходной модели который соответствует индексу прокси модели
QModelIndex MySortFilterProxyModel::mapToSource(const QModelIndex &proxyIndex) const
{
    if (!proxyIndex.isValid())
        return QModelIndex();
    else
    {
        if (sortedList->isEmpty())
            return QSortFilterProxyModel::mapToSource(proxyIndex);
        else
            return createIndex(sortedList->at(proxyIndex.row()),proxyIndex.column());
    }
}

Qt::ItemFlags MySortFilterProxyModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;
    else
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

void MySortFilterProxyModel::setSortedList(int column, Qt::SortOrder order)
{
    QMultiMap<QVariant, int> *sortedColumn = new QMultiMap<QVariant, int>();
    QVariant currentValue;
    int currentRow;
    for (int i=0; i<sourceModel()->rowCount(); i++)
    {
        currentValue = sourceModel()->data(sourceModel()->index(i,column));
        currentRow = i;
        sortedColumn->insert(currentValue, currentRow);
    }

    *sortedList = sortedColumn->values();
    if (order == Qt::DescendingOrder)
        std::reverse(sortedList->begin(),sortedList->end());
}

void MySortFilterProxyModel::revertList()
{
    sortedList->clear();
}
