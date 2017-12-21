#include "sortings.h"

void quickSort(QVector<Container> *arr)
{
    qSort(arr->begin(), arr->end(), [](const Container& a, const Container& b) -> bool
    {
        return a.m_key < b.m_key;
    });
}

void heapSort(QVector<Container> *arr)
{
    std::make_heap(arr->begin(), arr->end(), [](const Container& a, const Container& b) -> bool
    {
        return a.m_key < b.m_key;
    });
    std::sort_heap(arr->begin(), arr->end(), [](const Container& a, const Container& b) -> bool
    {
        return a.m_key < b.m_key;
    });
}

void stableSort(QVector<Container> *arr)
{
    std::stable_sort(arr->begin(), arr->end(), [](const Container& a, const Container& b) -> bool
    {
        return a.m_key < b.m_key;
    });
}

void simpleSort(QVector<Container> *arr)
{
    std::sort(arr->begin(), arr->end(), [](const Container& a, const Container& b) -> bool
    {
        return a.m_key < b.m_key;
    });
}

void timSort(QVector<Container> *arr)
{
    gfx::timsort(arr->begin(), arr->end(), [](const Container& a, const Container& b) -> bool
    {
        return a.m_key < b.m_key;
    });
}

void quickSort(QVector<Container>::Iterator begin, QVector<Container>::Iterator end)
{
    qSort(begin, end, [](const Container& a, const Container& b) -> bool
    {
        return a.m_key < b.m_key;
    });
}

void heapSort(QVector<Container>::Iterator begin, QVector<Container>::Iterator end)
{
    std::make_heap(begin, end, [](const Container& a, const Container& b) -> bool
    {
        return a.m_key < b.m_key;
    });
    std::sort_heap(begin, end, [](const Container& a, const Container& b) -> bool
    {
        return a.m_key < b.m_key;
    });
}

void stableSort(QVector<Container>::Iterator begin, QVector<Container>::Iterator end)
{
    std::stable_sort(begin, end, [](const Container& a, const Container& b) -> bool
    {
        return a.m_key < b.m_key;
    });
}

void simpleSort(QVector<Container>::Iterator begin, QVector<Container>::Iterator end)
{
    std::sort(begin, end, [](const Container& a, const Container& b) -> bool
    {
        return a.m_key < b.m_key;
    });
}

void timSort(QVector<Container>::Iterator begin, QVector<Container>::Iterator end)
{
    gfx::timsort(begin, end, [](const Container& a, const Container& b) -> bool
    {
        return a.m_key < b.m_key;
    });
}

QList<int> values(QVector<Container> cont)
{
    QList<int> tmp = QList<int>();

    for (auto& i : cont)
        tmp.append(i.m_value);

    return tmp;
}
