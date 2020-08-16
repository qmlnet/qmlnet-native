#include "NetAbstractItemModel.h"

NetAbstractItemModel::NetAbstractItemModel() {}

extern "C" {

Creator(NetAbstractItemModel, abstract_item_model)
Deleter(NetAbstractItemModel, abstract_item_model)

void net_abstract_item_model_beginInsertColumns(NetNetAbstractItemModelContainer* container, ModelIdx parent, int first, int last) {
    container->data->beginInsertColumns(parent, first, last);
}
SideEffecter(NetAbstractItemModel, abstract_item_model, endInsertColumns)

void net_abstract_item_model_beginInsertRows(NetNetAbstractItemModelContainer* container, ModelIdx parent, int first, int last) {
    container->data->beginInsertRows(parent, first, last);
}
SideEffecter(NetAbstractItemModel, abstract_item_model, endInsertRows)

void net_abstract_item_model_beginMoveColumns(NetNetAbstractItemModelContainer* container, ModelIdx sourceParent, int sourceFirst, int sourceLast, ModelIdx destinationParent, int destinationChild) {
    container->data->beginMoveColumns(sourceParent, sourceFirst, sourceLast, destinationParent, destinationChild);
}
SideEffecter(NetAbstractItemModel, abstract_item_model, endMoveColumns)

void net_abstract_item_model_beginMoveRows(NetNetAbstractItemModelContainer* container, ModelIdx sourceParent, int sourceFirst, int sourceLast, ModelIdx destinationParent, int destinationChild) {
    container->data->beginMoveRows(sourceParent, sourceFirst, sourceLast, destinationParent, destinationChild);
}
SideEffecter(NetAbstractItemModel, abstract_item_model, endMoveRows)

void net_abstract_item_model_beginRemoveColumns(NetNetAbstractItemModelContainer* container, ModelIdx parent, int first, int last) {
    container->data->beginRemoveColumns(parent, first, last);
}
SideEffecter(NetAbstractItemModel, abstract_item_model, endRemoveColumns)

void net_abstract_item_model_beginRemoveRows(NetNetAbstractItemModelContainer* container, ModelIdx parent, int first, int last) {
    container->data->beginRemoveRows(parent, first, last);
}
SideEffecter(NetAbstractItemModel, abstract_item_model, endRemoveRows)

SideEffecter(NetAbstractItemModel, abstract_item_model, beginResetModel)
SideEffecter(NetAbstractItemModel, abstract_item_model, endResetModel)

SynthesizeGetSetter(NetAbstractItemModel, abstract_item_model, m_flags, flags, FlagsDelegate)
SynthesizeGetSetter(NetAbstractItemModel, abstract_item_model, m_data, data, DataDelegate)
SynthesizeGetSetter(NetAbstractItemModel, abstract_item_model, m_headerData, header_data, HeaderDataDelegate)
SynthesizeGetSetter(NetAbstractItemModel, abstract_item_model, m_rowCount, row_count, RowCountDelegate)
SynthesizeGetSetter(NetAbstractItemModel, abstract_item_model, m_columnCount, column_count, ColumnCountDelegate)
SynthesizeGetSetter(NetAbstractItemModel, abstract_item_model, m_index, index, IndexDelegate)
SynthesizeGetSetter(NetAbstractItemModel, abstract_item_model, m_parent, parent, ParentDelegate)
SynthesizeGetSetter(NetAbstractItemModel, abstract_item_model, m_roleNames, role_names, RoleNamesDelegate)

}