#include <QModelIndex>

#include "NetQModelIndex.h"

extern "C" {

Deleter(QModelIndex, qmodelindex)

SimpleGetter(QModelIndex, qmodelindex, column, int)
SimpleGetter(QModelIndex, qmodelindex, row, int)
WrappedGetter(QModelIndex, qmodelindex, parent, QModelIndex)

}