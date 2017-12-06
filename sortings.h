#ifndef SORTINGS_H
#define SORTINGS_H

#include <QVector>
#include <QVariant>
#include <QtAlgorithms>
#include "timsort.hpp"


typedef struct MagicContainer
{
    QVariant m_key;
    int m_value;
} MagicContainer;

QList<int> values(QVector<MagicContainer> cont);

MagicContainer setData(QVariant key, int value);
MagicContainer setData(MagicContainer cont);
void quickSort(QVector<MagicContainer> *arr);
void heapSort(QVector<MagicContainer> *arr);
void stableSort(QVector<MagicContainer> *arr);
void simpleSort(QVector<MagicContainer> *arr);
void timSort(QVector<MagicContainer> *arr);

void quickSort(QVector<MagicContainer>::Iterator begin, QVector<MagicContainer>::Iterator end);
void heapSort(QVector<MagicContainer>::Iterator begin, QVector<MagicContainer>::Iterator end);
void stableSort(QVector<MagicContainer>::Iterator begin, QVector<MagicContainer>::Iterator end);
void simpleSort(QVector<MagicContainer>::Iterator begin, QVector<MagicContainer>::Iterator end);
void timSort(QVector<MagicContainer>::Iterator begin, QVector<MagicContainer>::Iterator end);


#endif // SORTINGS_H
