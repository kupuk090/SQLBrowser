#ifndef SORTINGS_H
#define SORTINGS_H

#include <QVector>
#include <QVariant>
#include <QtAlgorithms>
#include "timsort.hpp"


typedef struct Container
{
    QVariant m_key;
    int m_value;
} Container;

// возвращает список значений QVector<MagicContainer> (в данном случае номера строк)
QList<int> values(QVector<Container> cont);

// функции сортировки столбца
void timSort(QVector<Container> *arr);
void timSort(QVector<Container>::Iterator begin, QVector<Container>::Iterator end);


#endif // SORTINGS_H
