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
    setData(cont.m_key, cont.m_value);
}

void swap1(MagicContainer &left, MagicContainer &right)
{
    MagicContainer tmp(setData(left));

    left = setData(right);
    right = setData(tmp);
}

void quickSort(QVector<MagicContainer> *arr, int first, int last)
{
    int left = first, right = last;
    QVariant middle = arr->at((left+right)/2).m_key;
    while (left <= right)
    {
        while (arr->at(left).m_key < middle)
            left++;
        while (arr->at(right).m_key > middle)
            right--;
        if (left <= right)
            swap1(arr->at(left++), arr->at(right--));
    }
    if (first < right)
        quickSort(arr, first, right);
    if (last > left)
        quickSort(arr, left, last);
}

void quickSort(QVector<MagicContainer> *arr)
{
    quickSort(arr, 0, arr->size()-1);
}
