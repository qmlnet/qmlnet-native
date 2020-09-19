#ifndef QMLNETPAINTEDITEM_H
#define QMLNETPAINTEDITEM_H

#include <QtQuick/QQuickPaintedItem>
#include <QObject>
#include <QmlNet/types/NetTypeInfo.h>
#include <QmlNet.h>
#include <QmlNet/types/Callbacks.h>
#include <QmlNet/qml/NetValueMetaObject.h>

class QmlNetPaintedItemBase : public QQuickPaintedItem {
    Q_OBJECT

    Q_PROPERTY(bool supportsTextInput READ supportsTextInput WRITE setSupportsTextInput)
    Q_PROPERTY(bool preeditActive READ preeditActive NOTIFY preeditActiveChanged)
    Q_PROPERTY(QString preeditText READ preeditText NOTIFY preeditTextChanged)

public:
    QmlNetPaintedItemBase(QSharedPointer<NetReference> netReference, QQuickItem *parent = nullptr);

    virtual ~QmlNetPaintedItemBase();

    bool supportsTextInput() const;

    void setSupportsTextInput(bool supportsTextInput);

    bool preeditActive();

    Q_SIGNAL void preeditActiveChanged();

    QString preeditText();

    Q_SIGNAL void preeditTextChanged();

    //input method support
    void inputMethodEvent(QInputMethodEvent *e) override;

    QVariant inputMethodQuery(Qt::InputMethodQuery property) const override;

    void paint(QPainter *painter) override;

    Q_SLOT void onHeightChanged();
    Q_SLOT void onWidthChanged();

private:
    bool m_supportsTextInput;
    bool m_preeditActive;
    QString m_preeditText;

    QSharedPointer<NetReference> m_netReference;
    NetValueMetaObject* valueMeta;
};

template <int N>
class QmlNetPaintedItem : public QmlNetPaintedItemBase
{

public:
    QmlNetPaintedItem(QQuickItem *parent = nullptr)
        : QmlNetPaintedItemBase(QmlNet::instantiateType(s_netTypeInfo), parent) {
    }

    virtual ~QmlNetPaintedItem() {
    }

    static void init(QSharedPointer<NetTypeInfo> info) {
        s_netTypeInfo = info;
        static_cast<QMetaObject &>(staticMetaObject) = *metaObjectFor(info, &QmlNetPaintedItemBase::staticMetaObject);
    }

    static QMetaObject staticMetaObject;

private:
    static QSharedPointer<NetTypeInfo> s_netTypeInfo;
};

template <int N>
QSharedPointer<NetTypeInfo> QmlNetPaintedItem<N>::s_netTypeInfo = nullptr;
template <int N>
QMetaObject QmlNetPaintedItem<N>::staticMetaObject = QMetaObject();

#endif // QMLNETPAINTEDITEM_H
