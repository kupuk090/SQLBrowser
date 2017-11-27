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

    switch (choice)
    {
        case QtMap:
            setSortedList(column, order);
            break;

        default:
            magic(column, order);
            break;
    }
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

void MySortFilterProxyModel::magic(int column, Qt::SortOrder order)
{
    MagicContainer currentItem;
    QVector<MagicContainer> *dataColumn = new QVector<MagicContainer>();
    QVariant currentValue;
    int currentRow;

    for (int i=0; i<sourceModel()->rowCount(); i++)
    {
        currentValue = sourceModel()->data(sourceModel()->index(i,column));
        currentRow = i;
        currentItem.m_key = currentValue;
        currentItem.m_value = currentRow;
        dataColumn->append(currentItem);
    }

    switch (choice)
    {
        case QuickSort:
            quickSort(dataColumn);
            break;

        case HeapSort:
            heapSort(dataColumn);
            break;

        case StableSort:
            stableSort(dataColumn);
            break;

        default:
            break;
    }

    *sortedList = values(*dataColumn);
    if (order == Qt::DescendingOrder)
        std::reverse(sortedList->begin(),sortedList->end());
}

// вернуть индекс прокси модели который соответствует индексу исходной модели
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

// вернуть индекс исходной модели который соответствует индексу прокси модели
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

void MySortFilterProxyModel::revertList()
{
    sortedList->clear();
}

void MySortFilterProxyModel::giveSortChoice(MySortingMethods ch)
{
    choice = ch;
}
