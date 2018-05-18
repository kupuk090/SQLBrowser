#include "sortings.h"


void timSort(QVector<Container> *arr)
{
    gfx::timsort(arr->begin(), arr->end(), [](const Container& a, const Container& b) -> bool
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
