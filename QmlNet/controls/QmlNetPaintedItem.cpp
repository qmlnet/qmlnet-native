#include "NetQPainter.h"
#include "QmlNetPaintedItem.h"
#include <QPainter>
#include <stdexcept>

using setRefCb = void (*)(uint64_t, QmlNetPaintedItemBase *);
using paintCb = void (*)(uint64_t, NetQPainter *);
using heightChangedCb = void (*)(uint64_t, int);
using widthChangedCb = void (*)(uint64_t, int);

struct Q_DECL_EXPORT QmlNetPaintedItemCallbacks {
    setRefCb setRef;
    paintCb paint;
    heightChangedCb heightChanged;
    widthChangedCb widthChanged;
};

static QmlNetPaintedItemCallbacks sharedCallbacks {nullptr, nullptr, nullptr, nullptr};
QmlNetPaintedItemBase::QmlNetPaintedItemBase(QSharedPointer<NetReference> netReference, QQuickItem *parent)
    : QQuickPaintedItem(parent),
      m_netReference(netReference) {
    valueMeta = new NetValueMetaObject(this, netReference);
    QObject::connect(this,
                     &QmlNetPaintedItemBase::heightChanged,
                     this,
                     &QmlNetPaintedItemBase::onHeightChanged);
    QObject::connect(this,
                     &QmlNetPaintedItemBase::widthChanged,
                     this,
                     &QmlNetPaintedItemBase::onWidthChanged);
    if(sharedCallbacks.setRef != nullptr) {
        sharedCallbacks.setRef(netReference->getObjectId(), this);
    }
}

QmlNetPaintedItemBase::~QmlNetPaintedItemBase() {
}

bool QmlNetPaintedItemBase::supportsTextInput() const {
    return m_supportsTextInput;
}

void QmlNetPaintedItemBase::setSupportsTextInput(bool supportsTextInput) {
    m_supportsTextInput = supportsTextInput;
    setFlag(ItemAcceptsInputMethod, supportsTextInput);
}

bool QmlNetPaintedItemBase::preeditActive() {
    return m_preeditActive;
}

QString QmlNetPaintedItemBase::preeditText() {
    return m_preeditText;
}

//input method support
void QmlNetPaintedItemBase::inputMethodEvent(QInputMethodEvent *e) {
//    qDebug() << "InputMethod event. PreeditString=" << e->preeditString() << ", CommitString=" << e->commitString();
    auto preeditShouldBeActive = !e->preeditString().isEmpty();

    if(m_preeditActive != preeditShouldBeActive) {
        m_preeditActive = preeditShouldBeActive;
        Q_EMIT preeditActiveChanged();
    }
    if(m_preeditText != e->preeditString()) {
        m_preeditText = e->preeditString();
        Q_EMIT preeditTextChanged();
    }
    if(!e->commitString().isEmpty()) {
        QKeyEvent* event = new QKeyEvent(QKeyEvent::KeyPress,
                                         Qt::Key_unknown,
                                         Qt::NoModifier,
                                         e->commitString());
        QCoreApplication::postEvent(this,event);
    }
    QQuickItem::inputMethodEvent(e);
}

QVariant QmlNetPaintedItemBase::inputMethodQuery(Qt::InputMethodQuery property) const  {
    return QQuickItem::inputMethodQuery(property);
}

void QmlNetPaintedItemBase::paint(QPainter *painter) {
    NetQPainter netqPainter(painter);
    if(sharedCallbacks.paint != nullptr) {
        sharedCallbacks.paint(m_netReference->getObjectId(), &netqPainter);
    }
}

void QmlNetPaintedItemBase::onHeightChanged() {
    if(sharedCallbacks.heightChanged != nullptr) {
        sharedCallbacks.heightChanged(m_netReference->getObjectId(), height());
    }
}

void QmlNetPaintedItemBase::onWidthChanged() {
    if(sharedCallbacks.widthChanged != nullptr) {
        sharedCallbacks.widthChanged(m_netReference->getObjectId(), width());
    }
}

extern "C" {

Q_DECL_EXPORT void qqmlnetpainteditembase_setCallbacks(QmlNetPaintedItemCallbacks* callbacks) {
    sharedCallbacks = *callbacks;
}

Q_DECL_EXPORT void qqmlnetpainteditembase_update(QmlNetPaintedItemBase* paintedItem) {
    paintedItem->update();
}

Q_DECL_EXPORT int qqmlnetpainteditembase_getHeight(QmlNetPaintedItemBase* paintedItem) {
    return paintedItem->height();
}

Q_DECL_EXPORT int qqmlnetpainteditembase_getWidth(QmlNetPaintedItemBase* paintedItem) {
    return paintedItem->width();
}

}
