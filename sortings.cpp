#include "sortings.h"

MagicContainer setData(QVariant key, int value)
{
    MagicContainer tmp;

    tmp.m_key = key;
    tmp.m_value = value;

    return tmp;
}

MagicContainer setData(MagicContainer cont)
{
    return setData(cont.m_key, cont.m_value);
}

void quickSort(QVector<MagicContainer> *arr)
{
    qSort(arr->begin(), arr->end(), [](const MagicContainer& a, const MagicContainer& b) -> bool
    {
        return a.m_key < b.m_key;
    });
}

void heapSort(QVector<MagicContainer> *arr)
{
    std::make_heap(arr->begin(), arr->end(), [](const MagicContainer& a, const MagicContainer& b) -> bool
    {
        return a.m_key < b.m_key;
    });
    std::sort_heap(arr->begin(), arr->end(), [](const MagicContainer& a, const MagicContainer& b) -> bool
    {
        return a.m_key < b.m_key;
    });
}

void stableSort(QVector<MagicContainer> *arr)
{
    std::stable_sort(arr->begin(), arr->end(), [](const MagicContainer& a, const MagicContainer& b) -> bool
    {
        return a.m_key < b.m_key;
    });
}

void simpleSort(QVector<MagicContainer> *arr)
{
    std::sort(arr->begin(), arr->end(), [](const MagicContainer& a, const MagicContainer& b) -> bool
    {
        return a.m_key < b.m_key;
    });
}

void timSort(QVector<MagicContainer> *arr)
{
    gfx::timsort(arr->begin(), arr->end(), [](const MagicContainer& a, const MagicContainer& b) -> bool
    {
        return a.m_key < b.m_key;
    });
}

QList<int> values(QVector<MagicContainer> cont)
{
    QList<int> *tmp = new QList<int>();

    for (auto& i : cont)
        tmp->append(i.m_value);

    return *tmp;
}
