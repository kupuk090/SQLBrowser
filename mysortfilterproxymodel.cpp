#include "mysortfilterproxymodel.h"
#include <QDebug>
#include <QTime>


MySortFilterProxyModel::MySortFilterProxyModel(QObject *parent) : QSortFilterProxyModel(parent)
{
    prevColumn = -1;
    sorted = false;
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

    if ((prevColumn >= 0) && (prevColumn == column))
    {
        emit layoutAboutToBeChanged();
        if (!sorted)
            std::reverse(sortedList->begin(),sortedList->end());
        emit layoutChanged();
    }
    else
    {
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

    sorted = true;
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
    Container currentItem;
    QVector<Container> *dataColumn = new QVector<Container>();
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
        {
            void (*quickSortPtr) (QVector<Container>::Iterator, QVector<Container>::Iterator) = &quickSort;
            worker(dataColumn, quickSortPtr, QThread::idealThreadCount());

//            quickSort(dataColumn);

            break;
        }

        case HeapSort:
        {
            void (*heapSortPtr) (QVector<Container>::Iterator, QVector<Container>::Iterator) = &heapSort;
            worker(dataColumn, heapSortPtr, QThread::idealThreadCount());

//            heapSort(dataColumn);

            break;
        }

        case StableSort:
        {
            void (*stableSortPtr) (QVector<Container>::Iterator, QVector<Container>::Iterator) = &stableSort;
            worker(dataColumn, stableSortPtr, QThread::idealThreadCount());

//            stableSort(dataColumn);

            break;
        }

        case SimpleSort:
        {
            void (*simpleSortPtr) (QVector<Container>::Iterator, QVector<Container>::Iterator) = &simpleSort;
            worker(dataColumn, simpleSortPtr, QThread::idealThreadCount());

//            simpleSort(dataColumn);

            break;
        }

        case TimSort:
        {
            void (*timSortPtr) (QVector<Container>::Iterator, QVector<Container>::Iterator) = &timSort;
//            worker(dataColumn, timSortPtr, QThread::idealThreadCount());
            worker(dataColumn, timSortPtr, 8);

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

void MySortFilterProxyModel::setSorted(bool value)
{
    sorted = value;
}

void MySortFilterProxyModel::setPrevColumn(int value)
{
    prevColumn = value;
}

void MySortFilterProxyModel::revertList()
{
    prevColumn = -1;
    sortedList->clear();
}

void MySortFilterProxyModel::giveSortChoice(MySortingMethods ch)
{
    choice = ch;
}




QTime stTimer;
StProxyModel::StProxyModel(QObject *parent) : QSortFilterProxyModel(parent)
{
}

bool StProxyModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    stTimer.restart();

    bool res = QSortFilterProxyModel::lessThan(left, right);
    m_time += stTimer.elapsed();

    return res;
}



void worker(QVector<Container> *arr, void (*sortFunc)(QVector<Container>::Iterator, QVector<Container>::Iterator), int threadCount)
{
    int size = arr->size();
    QVector< QFuture<void> > futureMass;

    QVector<Container>::Iterator begin = arr->begin();
    QVector<Container>::Iterator end = begin + size/threadCount + 1;
    for (auto i = 0; i < threadCount; i++)
    {
        QFuture<void> future = QtConcurrent::run(sortFunc, begin, end);
        begin = end;
        end = begin + size/threadCount;
        futureMass.append(future);
    }
    for (auto i = 0; i < threadCount; i++)
    {
        futureMass.value(i).waitForFinished();
    }

    myMerge(arr, (threadCount / 2));
}

// не удавшаяся реализация многопоточного слияния массивов

void myMerge(QVector<Container> *arr, int count)
{
    int step = count * 2;
    int size = arr->size();

    if (count > 0)
    {
        QVector<Container> tmp = QVector<Container>();
        QVector< QFuture<void> > futureMass = QVector< QFuture<void> >();

        tmp.fill(Container(), size);
        QVector<Container>::Iterator begin1 = arr->begin();
        QVector<Container>::Iterator end1 = begin1 + size/step + 1;
        QVector<Container>::Iterator begin2 = end1;
        QVector<Container>::Iterator end2 = begin2 + size/step;
        QVector<Container>::Iterator tmpIt = tmp.begin();

        for (auto i = 0; i < count; i++)
        {
            QFuture<void> future = QtConcurrent::run(std::merge, begin1, end1, begin2, end2, tmpIt,
                                                     [](const Container& a, const Container& b) -> bool
                                                     {
                                                         return a.m_key < b.m_key;
                                                     });
            if (i)
                tmpIt += size/count;
            else
                tmpIt += size/count + 1;

            begin1 = end2;
            end1 = begin1 + size/step;
            begin2 = end1;
            end2 = begin2 + size/step;
            if (i)
                tmpIt += count;
            else
                tmpIt += count + 1;
            futureMass.append(future);
        }
        for (auto i = 0; i < count; i++)
        {
            futureMass.value(i).waitForFinished();
        }

        std::copy(tmp.begin(), tmp.end(), arr->begin());

        myMerge(arr, (count / 2));
    }
}


//void myMerge(QVector<Container> *arr, int count)
//{
//    int step = count * 2;
//    int size = arr->size();

//    if (count > 0)
//    {
//        QVector<Container> tmp;

//        tmp.fill(Container(), size);
//        QVector<Container>::Iterator begin1 = arr->begin();
//        QVector<Container>::Iterator end1 = begin1 + size/step + 1;
//        QVector<Container>::Iterator begin2 = end1;
//        QVector<Container>::Iterator end2 = begin2 + size/step;
//        QVector<Container>::Iterator tmpIt = tmp.begin();

//        for (auto i = 0; i < count; i++)
//        {
//            tmpIt = std::merge(begin1, end1, begin2, end2, tmpIt,
//                    [](const Container& a, const Container& b) -> bool
//                    {
//                        return a.m_key < b.m_key;
//                    });

//            begin1 = end2;
//            end1 = begin1 + size/step;
//            begin2 = end1;
//            end2 = begin2 + size/step;
//        }

//        std::copy(tmp.begin(), tmp.end(), arr->begin());

//        myMerge(arr, (count / 2));
//    }
//}
