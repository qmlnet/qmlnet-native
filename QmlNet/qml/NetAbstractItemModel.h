#include <QAbstractItemModel>
#include "NetQModelIndex.h"
#include "NetVariant.h"
#include "NetUtil.h"

using ModelIdx = NetQModelIndexContainer*;
using Variant = NetVariantContainer*;

// int FlagsDelegate( IntPtr )
using FlagsDelegate = std::function<int(ModelIdx)>;

// IntPtr DataDelegate( IntPtr, int )
using DataDelegate = std::function<Variant(ModelIdx, int)>;

// IntPtr HeaderDataDelegate( int, int, int )
using HeaderDataDelegate = std::function<Variant(int, int, int)>;

// int RowCountDelegate( IntPtr )
using RowCountDelegate = std::function<int(ModelIdx)>;

// int ColumnCountDelegate( IntPtr )
using ColumnCountDelegate = RowCountDelegate;

// IntPtr IndexDelegate( int, int, IntPtr )
using IndexDelegate = std::function<ModelIdx(int, int, ModelIdx)>;

// IntPtr ParentDelegate( IntPtr )
using ParentDelegate = std::function<ModelIdx(ModelIdx)>;

#define SynthesizeGetSetter(kind, name, delegate, delegateName, delKind) void net_ ## name ## _set_ ## delegateName(Net ## kind ## Container* container, delKind func) {\
    container->data->delegate = func;\
}\
delKind net_ ## name ## _get_ ## delegateName(Net ## kind ## Container* container) {\
    return container->data->delegate;\
}

class NetAbstractItemModel : public QAbstractItemModel
{
    Q_OBJECT
private:
    NetQModelIndexContainer* wrap(const QModelIndex& idx) const { return new NetQModelIndexContainer{ QSharedPointer<QModelIndex>(new QModelIndex(idx)) }; }
public:
    NetAbstractItemModel();
    FlagsDelegate m_flags = [=](ModelIdx idx) -> int {
        return QAbstractItemModel::flags(*(idx->data.data()));
    };
    Qt::ItemFlags flags(const QModelIndex &idx) const override {
        return (Qt::ItemFlag) m_flags(wrap(idx));
    }

    DataDelegate m_data = [=](ModelIdx idx, int role) -> Variant {
        return new NetVariantContainer{ NetVariant::fromQVariant(new QVariant(QAbstractItemModel::data(*(idx->data.data()), role)))};
    };
    QVariant data(const QModelIndex &idx, int role = Qt::DisplayRole) const override {
        return m_data(wrap(idx), role)->variant->toQVariant();
    }

    HeaderDataDelegate m_headerData = [=](int section, int orientation, int role) -> Variant {
        return new NetVariantContainer{ NetVariant::fromQVariant( new QVariant( QAbstractItemModel::headerData(section, (Qt::Orientation)orientation, role) ) )};
    };
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override {
        return m_headerData(section, orientation, role)->variant->toQVariant();
    }

    RowCountDelegate m_rowCount = [=](ModelIdx idx) -> int {
        return QAbstractItemModel::rowCount(*(idx->data.data()));
    };
    int rowCount(const QModelIndex &parent = QModelIndex()) const override {
        return m_rowCount(wrap(parent));
    }

    ColumnCountDelegate m_columnCount = [=](ModelIdx idx) -> int {
        return QAbstractItemModel::columnCount(*(idx->data.data()));
    };
    int columnCount(const QModelIndex &parent = QModelIndex()) const override {
        return m_columnCount(wrap(parent));
    }

    IndexDelegate m_index = [=](int row, int column, ModelIdx idx) -> ModelIdx {
        return new NetQModelIndexContainer{ QSharedPointer<QModelIndex>(new QModelIndex(createIndex(row, column))) };
    };
    QModelIndex index(int row, int column, const QModelIndex& parent) const override {
        return *(m_index(row, column, wrap(parent))->data.data());
    }

    ParentDelegate m_parent = [=](ModelIdx idx) -> ModelIdx {
        return new NetQModelIndexContainer{ QSharedPointer<QModelIndex>(new QModelIndex()) };
    };
    QModelIndex parent(const QModelIndex& idx) const override {
        return *(m_parent(wrap(idx))->data.data());
    }
};

Container(NetAbstractItemModel)

extern "C" {

Creator(NetAbstractItemModel, abstract_item_model)
Deleter(NetAbstractItemModel, abstract_item_model)

SynthesizeGetSetter(NetAbstractItemModel, abstract_item_model, m_flags, flags, FlagsDelegate)
SynthesizeGetSetter(NetAbstractItemModel, abstract_item_model, m_data, data, DataDelegate)
SynthesizeGetSetter(NetAbstractItemModel, abstract_item_model, m_headerData, header_data, HeaderDataDelegate)
SynthesizeGetSetter(NetAbstractItemModel, abstract_item_model, m_rowCount, row_count, RowCountDelegate)
SynthesizeGetSetter(NetAbstractItemModel, abstract_item_model, m_columnCount, column_count, ColumnCountDelegate)
SynthesizeGetSetter(NetAbstractItemModel, abstract_item_model, m_index, index, IndexDelegate)
SynthesizeGetSetter(NetAbstractItemModel, abstract_item_model, m_parent, parent, ParentDelegate)

}