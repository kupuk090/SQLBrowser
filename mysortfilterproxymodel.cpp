#include "mysortfilterproxymodel.h"
#include <QDebug>
#include <QTime>


MySortFilterProxyModel::MySortFilterProxyModel(QObject *parent) : QSortFilterProxyModel(parent)
{
    sortedList = new QList<int>();
    connect(this, SIGNAL(sourceModelChanged()), this, SLOT(revertList()));
}

MySortFilterProxyModel::~MySortFilterProxyModel()
{
}

bool MySortFilterProxyModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    QVariant leftData = sourceModel()->data(left);
    QVariant rightData = sourceModel()->data(right);
    QModelIndex newLeft = left;
    QModelIndex newRight = right;
    int count = 0;

    // проверяем не равны ли полученные данные и если равны, то переходим к сравнению по следующей колонке
    while (sourceModel()->data(newLeft) == sourceModel()->data(newRight))
    {
        if (count != sourceModel()->columnCount())
        {
            newLeft = left.sibling(left.row(),count);
            newRight = right.sibling(right.row(),count);
            count++;
        }
        else
            return true;
    }
    count = 0;

    if (leftData.type() == QVariant::Int)
        return leftData.toInt() < rightData.toInt();

    if (leftData.type() == QVariant::String)
        return leftData.toString() < rightData.toString();

    if (leftData.type() == QVariant::DateTime)
        return leftData.toDateTime() < rightData.toDateTime();

    if (leftData.type() == QVariant::Date)
        return leftData.toDate() < rightData.toDate();

    if (leftData.type() == QVariant::Time)
        return leftData.toTime() < rightData.toTime();

    return false;
}

void MySortFilterProxyModel::sort(int column, Qt::SortOrder order)
{
    QTime timer;
    timer.start();

    setSortedList(column, order);
    qDebug() << "Сортировка по столбцу" << sourceModel()->headerData(column, Qt::Horizontal).toString()
             << "в направлении" << order << "заняла: " << timer.elapsed() << "ms";
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
            return createIndex(sortedList->indexOf(sourceIndex.row()),sourceIndex.column(),sourceIndex.internalPointer());
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
            return createIndex(sortedList->at(proxyIndex.row()),proxyIndex.column(),sourceModel());
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

void MySortFilterProxyModel::revertList()
{
    sortedList->clear();
}
