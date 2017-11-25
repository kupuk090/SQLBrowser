#ifndef SORTINGS_H
#define SORTINGS_H

#include <QVector>
#include <QVariant>


typedef struct MagicContainer
{
    QVariant m_key;
    int m_value;
} MagicContainer;

MagicContainer setData(QVariant key, int value);
MagicContainer setData(MagicContainer cont);
void swap1(MagicContainer &left, MagicContainer &right);
void quickSort(QVector<MagicContainer> *arr, int first, int last);
void quickSort(QVector<MagicContainer> *arr);

#endif // SORTINGS_H
