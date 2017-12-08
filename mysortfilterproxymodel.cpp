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


    emit layoutAboutToBeChanged();
    switch (choice)
    {
        case QtMap:
            setSortedList(column, order);
            break;

        default:
            magic(column, order);
            break;
    }
    emit layoutChanged();
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

    delete sortedColumn;
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

        case SimpleSort:
            simpleSort(dataColumn);
            break;

        case TimSort:
        {
//            QFuture<void> future1 = QtConcurrent::run(timSort, dataColumn->begin(), dataColumn->begin() + dataColumn->size()/2);
//            QFuture<void> future2 = QtConcurrent::run(timSort, dataColumn->begin() + dataColumn->size()/2 + 1, dataColumn->end());
//            future1.waitForFinished();
//            future2.waitForFinished();
//            std::merge(dataColumn->begin(), dataColumn->begin() + dataColumn->size()/2,
//                       dataColumn->begin() + dataColumn->size()/2 + 1, dataColumn->end(), dataColumn->begin(),
//                       [](const MagicContainer& a, const MagicContainer& b) -> bool
//                           {
//                               return a.m_key < b.m_key;
//                           });

//            int size = dataColumn->size();
//            QVector<MagicContainer>::Iterator begin = dataColumn->begin();
//            QFuture<void> future1 = QtConcurrent::run(timSort, begin, begin + size/4);
//            QFuture<void> future2 = QtConcurrent::run(timSort, begin + size/4 + 1, begin + size/2);
//            QFuture<void> future3 = QtConcurrent::run(timSort, begin + size/2 + 1, begin + 3*size/4);
//            QFuture<void> future4 = QtConcurrent::run(timSort, begin + 3*size/4 + 1, dataColumn->end());
//            future1.waitForFinished();
//            future2.waitForFinished();
//            future3.waitForFinished();
//            future4.waitForFinished();
//            std::merge(begin, begin + size/4, begin + size/4 + 1, begin + size/2, dataColumn->begin(),
//                       [](const MagicContainer& a, const MagicContainer& b) -> bool
//                           {
//                               return a.m_key < b.m_key;
//                           });
//            std::merge(begin + size/2 + 1, begin + 3*size/4, begin + 3*size/4 + 1, dataColumn->end(), dataColumn->begin() + size/2 + 1,
//                       [](const MagicContainer& a, const MagicContainer& b) -> bool
//                           {
//                               return a.m_key < b.m_key;
//                           });
//            future1 = QtConcurrent::run(timSort, begin, begin + size/2);
//            future2 = QtConcurrent::run(timSort, begin + size/2 + 1, dataColumn->end());
//            future1.waitForFinished();
//            future2.waitForFinished();
//            std::merge(begin, begin + size/2, begin + size/2 + 1, dataColumn->end(), dataColumn->begin(),
//                       [](const MagicContainer& a, const MagicContainer& b) -> bool
//                           {
//                               return a.m_key < b.m_key;
//                           });

            // более правильная версия
            int size = dataColumn->size();
            QVector<MagicContainer>::Iterator begin = dataColumn->begin();
            QVector<MagicContainer> *tmp = new QVector<MagicContainer>();
            qDebug() << begin->m_key;
            qDebug() << (begin+1)->m_key;
            QFuture<void> future1 = QtConcurrent::run(timSort, begin, begin + size/4);
            QFuture<void> future2 = QtConcurrent::run(timSort, begin + size/4 + 1, begin + size/2);
            QFuture<void> future3 = QtConcurrent::run(timSort, begin + size/2 + 1, begin + 3*size/4);
            QFuture<void> future4 = QtConcurrent::run(timSort, begin + 3*size/4 + 1, dataColumn->end());
            future1.waitForFinished();
            future2.waitForFinished();
            future3.waitForFinished();
            future4.waitForFinished();
            qDebug() << size/2;
            tmp->fill(MagicContainer(), size/2);
            std::merge(begin, begin + size/4, begin + size/4 + 1, begin + size/2, tmp->begin(),
                       [](const MagicContainer& a, const MagicContainer& b) -> bool
                           {
                               return a.m_key < b.m_key;
                           });
            std::copy(tmp->begin(), tmp->end(), begin);
            tmp->clear();
            tmp->fill(MagicContainer(), size/2);
            std::merge(begin + size/2 + 1, begin + 3*size/4, begin + 3*size/4 + 1, dataColumn->end(), tmp->begin(),
                       [](const MagicContainer& a, const MagicContainer& b) -> bool
                           {
                               return a.m_key < b.m_key;
                           });
            std::copy(tmp->begin(), tmp->end(), begin + size/2 + 1);
            tmp->clear();
            future1 = QtConcurrent::run(timSort, begin, begin + size/2);
            future2 = QtConcurrent::run(timSort, begin + size/2 + 1, dataColumn->end());
            future1.waitForFinished();
            future2.waitForFinished();
            tmp->fill(MagicContainer(), size);
            std::merge(begin, begin + size/2, begin + size/2 + 1, dataColumn->end(), tmp->begin(),
                       [](const MagicContainer& a, const MagicContainer& b) -> bool
                           {
                               return a.m_key < b.m_key;
                           });
            std::copy(tmp->begin(), tmp->end(), begin);
            delete tmp;

//            timSort(dataColumn);
            break;
        }

        default:
            break;
    }

    *sortedList = values(*dataColumn);
    if (order == Qt::DescendingOrder)
        std::reverse(sortedList->begin(),sortedList->end());

    delete dataColumn;
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
