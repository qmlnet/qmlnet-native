#include "QmlNetPaintedItem.h"
#include <QPainter>
#include <stdexcept>

QmlNetPaintedItemBase::QmlNetPaintedItemBase(QSharedPointer<NetReference> netReference, QQuickItem *parent)
    : QQuickPaintedItem(parent),
      m_netReference(netReference) {
    valueMeta = new NetValueMetaObject(this, netReference);
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
    auto preeditShouldBeActive = !e->preeditString().isEmpty();
    bool hasBeenCommited = false;

    if(m_preeditActive != preeditShouldBeActive) {
        m_preeditActive = preeditShouldBeActive;
        Q_EMIT preeditActiveChanged();
        hasBeenCommited = true;
    }
    if(m_preeditText != e->preeditString()) {
        m_preeditText = e->preeditString();
        Q_EMIT preeditTextChanged();
    }
    if(hasBeenCommited && !e->commitString().isEmpty()) {
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
    qDebug() << "Paint";
}

extern "C" {

Q_DECL_EXPORT void qqmlnetpainteditembase_update(QmlNetPaintedItemBase* paintedItem) {
    paintedItem->update();
}

}
