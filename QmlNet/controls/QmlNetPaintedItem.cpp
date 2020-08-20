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

bool QmlNetPaintedItem::supportsTextInput() const {
    return m_supportsTextInput;
}

void QmlNetPaintedItem::setSupportsTextInput(bool supportsTextInput) {
    m_supportsTextInput = supportsTextInput;
    setFlag(ItemAcceptsInputMethod, supportsTextInput);
    setFlag(ItemIsFocusScope, supportsTextInput);
}
bool QmlNetPaintedItem::preeditActive() {
    return m_preeditActive;
}

QString QmlNetPaintedItem::preeditText() {
    return m_preeditText;
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

void QmlNetPaintedItem::setPen(int colorId) {
    auto color = m_colorMap.at(colorId);
    checkRecordingAndAdd([color](QPainter* p) {
        QPen pen(color);
        p->setPen(color);
    });
}

void QmlNetPaintedItem::resetPen() {
    checkRecordingAndAdd([](QPainter* p) {
       p->setPen(QPen());
    });
}

void QmlNetPaintedItem::setBrush(int colorId) {
    auto color = m_colorMap.at(colorId);
    checkRecordingAndAdd([color](QPainter* p) {
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

void QmlNetPaintedItem::setFontFamily(QString fontFamilyName) {
    checkRecordingAndAdd([fontFamilyName](QPainter* p) {
       auto font = p->font();
       font.setFamily(fontFamilyName);
       p->setFont(font);
    });
}

void QmlNetPaintedItem::setFontBold(bool isBold) {
    checkRecordingAndAdd([isBold](QPainter* p) {
       auto font = p->font();
       font.setBold(isBold);
       p->setFont(font);
    });
}

void QmlNetPaintedItem::setFontItalic(bool isItalic) {
    checkRecordingAndAdd([isItalic](QPainter* p) {
       auto font = p->font();
       font.setItalic(isItalic);
       p->setFont(font);
    });
}

void QmlNetPaintedItem::setFontUnderline(bool isUnderline) {
    checkRecordingAndAdd([isUnderline](QPainter* p) {
       auto font = p->font();
       font.setUnderline(isUnderline);
       p->setFont(font);
    });
}

void QmlNetPaintedItem::setFontSize(int pxSize) {
    checkRecordingAndAdd([pxSize](QPainter* p) {
       auto font = p->font();
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

void QmlNetPaintedItem::drawText(int x, int y, int width, int height, int flags, QString text) {
    checkRecordingAndAdd([x,y,text, width, height, flags](QPainter* p) {
        QRect rect(x, y, width, height);
        p->drawText(rect, flags ,text);
    });
}

void QmlNetPaintedItem::drawRect(int x, int y, int width, int height) {
    checkRecordingAndAdd([x,y,width, height](QPainter* p) {
        p->drawRect(x, y, width, height);
    });
}

void QmlNetPaintedItem::fillRect(int x, int y, int width, int height, int colorId) {
    auto color = m_colorMap.at(colorId);
    checkRecordingAndAdd([x,y,width, height, color](QPainter* p) {
        QBrush brush(color);
        p->fillRect(x, y, width, height, brush);
    });
}

void QmlNetPaintedItem::fillRect(int x, int y, int width, int height) {
    checkRecordingAndAdd([x,y,width, height](QPainter* p) {
        p->fillRect(x, y, width, height, p->brush());
    });
}

int QmlNetPaintedItem::createColor(QString colorString) {
    QColor color(colorString);
    for(int i=0; i<std::numeric_limits<int>::max(); i++) {
        if(m_colorMap.find(i) == m_colorMap.end()) {
            m_colorMap[i] = color;
            return i;
        }
    }
    throw std::runtime_error("No free color id found");
}

void QmlNetPaintedItem::freeColor(int colorId) {
    if(m_colorMap.find(colorId) != m_colorMap.end()) {
        m_colorMap.erase(colorId);
    }
}

QSize QmlNetPaintedItem::getStringSize(QString fontFamilyName, int fontSizePx, QString text) {
    QFont font(fontFamilyName);
    font.setPixelSize(fontSizePx);

    QFontMetrics metrics(font);
    return metrics.size(0, text);
}

void QmlNetPaintedItem::inputMethodEvent(QInputMethodEvent *e)
{
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

QVariant QmlNetPaintedItem::inputMethodQuery(Qt::InputMethodQuery property) const {
    return QQuickItem::inputMethodQuery(property);
}

void QmlNetPaintedItem::checkRecordingAndAdd(std::function<void(QPainter*)> action) {
    if(!m_isRecording) {
        throw std::runtime_error("No recording session is running. Call beginRecordPaintActions");
    }
    m_recordedPaintActions.push_back(action);
}

void QmlNetPaintedItem::paint(QPainter *painter)
{
    m_paintActionMutex.lock();

    for(auto pa : m_paintActions) {
        pa(painter);
    }

    m_paintActionMutex.unlock();
}

extern "C" {

Q_DECL_EXPORT void qqmlnetpainteditem_beginRecordPaintActions(QmlNetPaintedItem* paintedItem) {
    paintedItem->beginRecordPaintActions();
}

Q_DECL_EXPORT void qqmlnetpainteditem_endRecordPaintActions(QmlNetPaintedItem* paintedItem) {
    paintedItem->endRecordPaintActions();
}

Q_DECL_EXPORT void qqmlnetpainteditem_setPen(QmlNetPaintedItem* paintedItem, int colorId) {
    paintedItem->setPen(colorId);
}

Q_DECL_EXPORT void qqmlnetpainteditem_resetPen(QmlNetPaintedItem* paintedItem) {
    paintedItem->resetPen();
}

Q_DECL_EXPORT void qqmlnetpainteditem_setBrush(QmlNetPaintedItem* paintedItem, int colorId) {
    paintedItem->setBrush(colorId);
}

Q_DECL_EXPORT void qqmlnetpainteditem_resetBrush(QmlNetPaintedItem* paintedItem) {
    paintedItem->resetBrush();
}

Q_DECL_EXPORT void qqmlnetpainteditem_setFont(QmlNetPaintedItem* paintedItem, QChar* fontFamilyName, bool isBold, bool isItalic, bool isUnderline, int pxSize) {
    paintedItem->setFont(QString(fontFamilyName), isBold, isItalic, isUnderline, pxSize);
}

Q_DECL_EXPORT void qqmlnetpainteditem_setFontFamily(QmlNetPaintedItem* paintedItem, QChar* fontFamilyName) {
    paintedItem->setFontFamily(QString(fontFamilyName));
}

Q_DECL_EXPORT void qqmlnetpainteditem_setFontBold(QmlNetPaintedItem* paintedItem, bool isBold) {
    paintedItem->setFontBold(isBold);
}

Q_DECL_EXPORT void qqmlnetpainteditem_setFontItalic(QmlNetPaintedItem* paintedItem, bool isItalic) {
    paintedItem->setFontItalic(isItalic);
}

Q_DECL_EXPORT void qqmlnetpainteditem_setFontUnderline(QmlNetPaintedItem* paintedItem, bool isUnderline) {
    paintedItem->setFontUnderline(isUnderline);
}

Q_DECL_EXPORT void qqmlnetpainteditem_setFontSize(QmlNetPaintedItem* paintedItem, int pxSize) {
    paintedItem->setFontSize(pxSize);
}

Q_DECL_EXPORT void qqmlnetpainteditem_drawText(QmlNetPaintedItem* paintedItem, int x, int y, QChar* text) {
    paintedItem->drawText(x, y, QString(text));
}

Q_DECL_EXPORT void qqmlnetpainteditem_drawTextRect(QmlNetPaintedItem* paintedItem, int x, int y, int width, int height, int flags, QChar* text) {
    paintedItem->drawText(x, y, width, height, flags, QString(text));
}

Q_DECL_EXPORT void qqmlnetpainteditem_drawRect(QmlNetPaintedItem* paintedItem, int x, int y, int width, int height) {
    paintedItem->drawRect(x, y, width, height);
}

Q_DECL_EXPORT void qqmlnetpainteditem_fillRectColor(QmlNetPaintedItem* paintedItem, int x, int y, int width, int height, int colorId) {
    paintedItem->fillRect(x, y, width, height, colorId);
}

Q_DECL_EXPORT void qqmlnetpainteditem_fillRect(QmlNetPaintedItem* paintedItem, int x, int y, int width, int height) {
    paintedItem->fillRect(x, y, width, height);
}

Q_DECL_EXPORT int qqmlnetpainteditem_createColor(QmlNetPaintedItem* paintedItem, QChar* colorString) {
    return paintedItem->createColor(QString(colorString));
}

Q_DECL_EXPORT void qqmlnetpainteditem_freeColor(QmlNetPaintedItem* paintedItem, int colorId) {
    paintedItem->freeColor(colorId);
}

struct StringSizeResult {
    int width;
    int height;
};

Q_DECL_EXPORT StringSizeResult qqmlnetpainteditem_getStringSize(QmlNetPaintedItem* paintedItem, QChar* fontFamily, int fontSizePx, QChar* text) {
    auto size = paintedItem->getStringSize(QString(fontFamily), fontSizePx, QString(text));
    StringSizeResult result;
    result.width = size.width();
    result.height = size.height();
    return result;
}

}
