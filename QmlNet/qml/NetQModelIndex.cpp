#include <QModelIndex>

#include "NetQModelIndex.h"

extern "C" {

Creator(QModelIndex, qmodelindex)
Deleter(QModelIndex, qmodelindex)

SimpleGetter(QModelIndex, qmodelindex, column, int)
SimpleGetter(QModelIndex, qmodelindex, row, int)
WrappedGetter(QModelIndex, qmodelindex, parent, QModelIndex)

}