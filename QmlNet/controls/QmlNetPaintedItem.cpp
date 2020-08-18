#include "QmlNetPaintedItem.h"
#include <QPainter>

QmlNetPaintedItem::QmlNetPaintedItem(QQuickItem *parent)
    : QQuickPaintedItem(parent)
{
}

QObject* QmlNetPaintedItem::paintHandler() const {
    return m_paintHandler;
}

void QmlNetPaintedItem::setPaintHandler(QObject* paintHandler) {
    m_paintHandler = paintHandler;
    if(m_paintHandler != nullptr) {
        QMetaObject::invokeMethod(m_paintHandler, "__setPaintedItem", Q_ARG(QVariant, QVariant::fromValue((int64_t)this)));
    }
}


void QmlNetPaintedItem::beginRecordPaintActions() {
   m_isRecording = true;
   m_recordedPaintActions.clear();
}

void QmlNetPaintedItem::endRecordPaintActions() {
   m_isRecording = false;
   m_paintActionMutex.lock();
   m_paintActions = m_recordedPaintActions;
   m_paintActionMutex.unlock();
   update();
}

void QmlNetPaintedItem::setPen(QString colorString) {
    checkRecordingAndAdd([colorString](QPainter* p) {
        QColor color(colorString);
        QPen pen(color);
        p->setPen(color);
    });
}

void QmlNetPaintedItem::resetPen() {
    checkRecordingAndAdd([](QPainter* p) {
       p->setPen(QPen());
    });
}

void QmlNetPaintedItem::setBrush(QString colorString) {
    checkRecordingAndAdd([colorString](QPainter* p) {
        QColor color(colorString);
        QBrush brush(color);
        p->setBrush(brush);
    });
}

void QmlNetPaintedItem::resetBrush() {
    checkRecordingAndAdd([](QPainter* p) {
       p->setBrush(QBrush());
    });
}

void QmlNetPaintedItem::setFont(QString fontFamilyName, bool isBold, bool isItalic, bool isUnderline, int pxSize) {
    checkRecordingAndAdd([fontFamilyName, isBold, isItalic, isUnderline, pxSize](QPainter* p) {
        auto font = QFont(fontFamilyName);
        font.setBold(isBold);
        font.setItalic(isItalic);
        font.setUnderline(isUnderline);
        font.setPixelSize(pxSize);
        p->setFont(font);
    });
}

void QmlNetPaintedItem::drawText(int x, int y, QString text) {
    checkRecordingAndAdd([x,y,text](QPainter* p) {
        auto vp = p->viewport();
        p->drawText(vp.x() + x, vp.y() + y, text);
    });
}

void QmlNetPaintedItem::drawRect(int x, int y, int width, int height) {
    checkRecordingAndAdd([x,y,width, height](QPainter* p) {
        p->drawRect(x, y, width, height);
    });
}

void QmlNetPaintedItem::fillRect(int x, int y, int width, int height, QString colorString) {
    checkRecordingAndAdd([x,y,width, height, colorString](QPainter* p) {
        QColor color(colorString);
        QBrush brush(color);
        p->fillRect(x, y, width, height, brush);
    });
}

void QmlNetPaintedItem::fillRect(int x, int y, int width, int height) {
    checkRecordingAndAdd([x,y,width, height](QPainter* p) {
        p->fillRect(x, y, width, height, p->brush());
    });
}

void QmlNetPaintedItem::checkRecordingAndAdd(std::function<void(QPainter*)> action) {
    if(!m_isRecording) {
        //TODO: throw
    }
    m_recordedPaintActions.push_back(action);
}

void QmlNetPaintedItem::paint(QPainter *painter)
{
    std::vector<std::function<void(QPainter*)>> paintActionsCopy;
    m_paintActionMutex.lock();
    paintActionsCopy = m_paintActions;
    m_paintActionMutex.unlock();

    for(auto pa : paintActionsCopy) {
        pa(painter);
    }
}

extern "C" {

Q_DECL_EXPORT void qqmlnetpainteditem_beginRecordPaintActions(QmlNetPaintedItem* paintedItem) {
    paintedItem->beginRecordPaintActions();
}

Q_DECL_EXPORT void qqmlnetpainteditem_endRecordPaintActions(QmlNetPaintedItem* paintedItem) {
    paintedItem->endRecordPaintActions();
}

Q_DECL_EXPORT void qqmlnetpainteditem_setPen(QmlNetPaintedItem* paintedItem, QChar* colorString) {
    paintedItem->setPen(QString(colorString));
}

Q_DECL_EXPORT void qqmlnetpainteditem_resetPen(QmlNetPaintedItem* paintedItem) {
    paintedItem->resetPen();
}

Q_DECL_EXPORT void qqmlnetpainteditem_setBrush(QmlNetPaintedItem* paintedItem, QChar* colorString) {
    paintedItem->setBrush(QString(colorString));
}

Q_DECL_EXPORT void qqmlnetpainteditem_resetBrush(QmlNetPaintedItem* paintedItem) {
    paintedItem->resetBrush();
}

Q_DECL_EXPORT void qqmlnetpainteditem_setFont(QmlNetPaintedItem* paintedItem, QChar* fontFamilyName, bool isBold, bool isItalic, bool isUnderline, int pxSize) {
    paintedItem->setFont(QString(fontFamilyName), isBold, isItalic, isUnderline, pxSize);
}

Q_DECL_EXPORT void qqmlnetpainteditem_drawText(QmlNetPaintedItem* paintedItem, int x, int y, QChar* text) {
    paintedItem->drawText(x, y, QString(text));
}

Q_DECL_EXPORT void qqmlnetpainteditem_drawRect(QmlNetPaintedItem* paintedItem, int x, int y, int width, int height) {
    paintedItem->drawRect(x, y, width, height);
}

Q_DECL_EXPORT void qqmlnetpainteditem_fillRectColor(QmlNetPaintedItem* paintedItem, int x, int y, int width, int height, QChar* color) {
    paintedItem->fillRect(x, y, width, height, QString(color));
}

Q_DECL_EXPORT void qqmlnetpainteditem_fillRect(QmlNetPaintedItem* paintedItem, int x, int y, int width, int height) {
    paintedItem->fillRect(x, y, width, height);
}

}
