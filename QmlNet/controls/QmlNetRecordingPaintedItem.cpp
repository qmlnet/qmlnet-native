#include "QmlNetRecordingPaintedItem.h"
#include <QPainter>
#include <stdexcept>

QmlNetRecordingPaintedItem::QmlNetRecordingPaintedItem(QQuickItem *parent)
    : QQuickPaintedItem(parent)
{
}

QmlNetRecordingPaintedItem::~QmlNetRecordingPaintedItem() {
    setPaintedItemToHandler(m_paintHandler, nullptr);
}

QObject* QmlNetRecordingPaintedItem::paintHandler() const {
    return m_paintHandler;
}

void QmlNetRecordingPaintedItem::setPaintHandler(QObject* paintHandler) {
    setPaintedItemToHandler(m_paintHandler, nullptr);
    m_paintHandler = paintHandler;
    if(m_paintHandler != nullptr) {
        setPaintedItemToHandler(m_paintHandler, this);
    }
}

bool QmlNetRecordingPaintedItem::supportsTextInput() const {
    return m_supportsTextInput;
}

void QmlNetRecordingPaintedItem::setSupportsTextInput(bool supportsTextInput) {
    m_supportsTextInput = supportsTextInput;
    setFlag(ItemAcceptsInputMethod, supportsTextInput);
}
bool QmlNetRecordingPaintedItem::preeditActive() {
    return m_preeditActive;
}

QString QmlNetRecordingPaintedItem::preeditText() {
    return m_preeditText;
}

void QmlNetRecordingPaintedItem::beginRecordPaintActions() {
   m_isRecording = true;
   m_recordedPaintActions.clear();
}

void QmlNetRecordingPaintedItem::endRecordPaintActions() {
   m_isRecording = false;
   //if the paint calls come in the UI thread this should not be necessary because the Renderer Thread halts the UI thread
   //but better safe than sorry
   m_paintActionMutex.lock();
   m_paintActions = m_recordedPaintActions;
   m_paintActionMutex.unlock();
   update();
}

void QmlNetRecordingPaintedItem::setPen(int colorId) {
    auto color = m_colorMap.at(colorId);
    checkRecordingAndAdd([color](QPainter* p) {
        QPen pen(color);
        p->setPen(color);
    });
}

void QmlNetRecordingPaintedItem::resetPen() {
    checkRecordingAndAdd([](QPainter* p) {
       p->setPen(QPen());
    });
}

void QmlNetRecordingPaintedItem::setBrush(int colorId) {
    auto color = m_colorMap.at(colorId);
    checkRecordingAndAdd([color](QPainter* p) {
        QBrush brush(color);
        p->setBrush(brush);
    });
}

void QmlNetRecordingPaintedItem::resetBrush() {
    checkRecordingAndAdd([](QPainter* p) {
       p->setBrush(QBrush());
    });
}

void QmlNetRecordingPaintedItem::setFont(int fontFamilyId, bool isBold, bool isItalic, bool isUnderline, int pxSize) {
    auto fontFamilyName = m_fontFamilyMap[fontFamilyId];
    checkRecordingAndAdd([fontFamilyName, isBold, isItalic, isUnderline, pxSize](QPainter* p) {
        auto font = QFont(fontFamilyName);
        font.setBold(isBold);
        font.setItalic(isItalic);
        font.setUnderline(isUnderline);
        font.setPixelSize(pxSize);
        p->setFont(font);
    });
}

void QmlNetRecordingPaintedItem::setFontFamily(int fontFamilyId) {
    auto fontFamilyName = m_fontFamilyMap[fontFamilyId];
    checkRecordingAndAdd([fontFamilyName](QPainter* p) {
       auto font = p->font();
       font.setFamily(fontFamilyName);
       p->setFont(font);
    });
}

void QmlNetRecordingPaintedItem::setFontBold(bool isBold) {
    checkRecordingAndAdd([isBold](QPainter* p) {
       auto font = p->font();
       font.setBold(isBold);
       p->setFont(font);
    });
}

void QmlNetRecordingPaintedItem::setFontItalic(bool isItalic) {
    checkRecordingAndAdd([isItalic](QPainter* p) {
       auto font = p->font();
       font.setItalic(isItalic);
       p->setFont(font);
    });
}

void QmlNetRecordingPaintedItem::setFontUnderline(bool isUnderline) {
    checkRecordingAndAdd([isUnderline](QPainter* p) {
       auto font = p->font();
       font.setUnderline(isUnderline);
       p->setFont(font);
    });
}

void QmlNetRecordingPaintedItem::setFontSize(int pxSize) {
    checkRecordingAndAdd([pxSize](QPainter* p) {
       auto font = p->font();
       font.setPixelSize(pxSize);
       p->setFont(font);
    });
}

void QmlNetRecordingPaintedItem::drawText(int x, int y, QString text) {
    checkRecordingAndAdd([x,y,text](QPainter* p) {
        auto vp = p->viewport();
        p->drawText(vp.x() + x, vp.y() + y, text);
    });
}

void QmlNetRecordingPaintedItem::drawText(int x, int y, int width, int height, int flags, QString text) {
    checkRecordingAndAdd([x,y,text, width, height, flags](QPainter* p) {
        QRect rect(x, y, width, height);
        p->drawText(rect, flags ,text);
    });
}

void QmlNetRecordingPaintedItem::drawRect(int x, int y, int width, int height) {
    checkRecordingAndAdd([x,y,width, height](QPainter* p) {
        p->drawRect(x, y, width, height);
    });
}

void QmlNetRecordingPaintedItem::fillRect(int x, int y, int width, int height, int colorId) {
    auto color = m_colorMap.at(colorId);
    checkRecordingAndAdd([x,y,width, height, color](QPainter* p) {
        QBrush brush(color);
        p->fillRect(x, y, width, height, brush);
    });
}

void QmlNetRecordingPaintedItem::fillRect(int x, int y, int width, int height) {
    checkRecordingAndAdd([x,y,width, height](QPainter* p) {
        p->fillRect(x, y, width, height, p->brush());
    });
}

void QmlNetRecordingPaintedItem::drawArc(int x, int y, int width, int height, int startAngle, int spanAngle) {
    checkRecordingAndAdd([x,y,width, height, startAngle, spanAngle](QPainter* p) {
        p->drawArc(x, y, width, height, startAngle, spanAngle);
    });
}

void QmlNetRecordingPaintedItem::drawChord(int x, int y, int width, int height, int startAngle, int spanAngle) {
    checkRecordingAndAdd([x,y,width, height, startAngle, spanAngle](QPainter* p) {
        p->drawChord(x, y, width, height, startAngle, spanAngle);
    });
}

void QmlNetRecordingPaintedItem::drawConvexPolygon(const QPoint *points, int pointCount) {
    std::vector<QPoint> pointsCopy;
    for(int i=0; i<pointCount; i++) {
        pointsCopy.push_back(points[i]);
    }
    checkRecordingAndAdd([pointsCopy](QPainter* p) {
        p->drawConvexPolygon(&pointsCopy[0], pointsCopy.size());
    });
}

void QmlNetRecordingPaintedItem::drawEllipse(int x, int y, int width, int height) {
    checkRecordingAndAdd([x,y,width, height](QPainter* p) {
        p->drawEllipse(x, y, width, height);
    });
}

void QmlNetRecordingPaintedItem::drawImage(const QPoint &point, const QImage &image, const QRect &source, Qt::ImageConversionFlags flags) {
    QPoint pointCopy = point;
    QImage imgCopy = image;
    QRect sourceCopy = source;
    checkRecordingAndAdd([pointCopy, imgCopy, sourceCopy, flags](QPainter* p) {
        p->drawImage(pointCopy, imgCopy, sourceCopy, flags);
    });
}

void QmlNetRecordingPaintedItem::drawLine(int x1, int y1, int x2, int y2) {
    checkRecordingAndAdd([x1, y1, x2, y2](QPainter* p) {
        p->drawLine(x1, y1, x2, y2);
    });
}

//void QmlNetRecordingPaintedItem::drawPath(const QPainterPath &path) {
//    QPainterPath pathCopy = path;
//    checkRecordingAndAdd([pathCopy](QPainter* p) {
//        p->drawPath(pathCopy);
//    });
//}

//void QmlNetRecordingPaintedItem::fillPath(const QPainterPath &path, int colorId) {
//    QPainterPath pathCopy = path;
//    auto color = m_colorMap[colorId];
//    checkRecordingAndAdd([pathCopy, color](QPainter* p) {
//        p->fillPath(pathCopy, QBrush(color));
//    });
//}

//void QmlNetRecordingPaintedItem::strokePath(const QPainterPath &path, int colorId) {
//    QPainterPath pathCopy = path;
//    auto color = m_colorMap[colorId];
//    checkRecordingAndAdd([pathCopy, color](QPainter* p) {
//        p->strokePath(pathCopy, QPen(color));
//    });
//}

void QmlNetRecordingPaintedItem::drawPie(int x, int y, int width, int height, int startAngle, int spanAngle) {
    checkRecordingAndAdd([x, y, width, height, startAngle, spanAngle](QPainter* p) {
        p->drawPie(x, y, width, height, startAngle, spanAngle);
    });
}

void QmlNetRecordingPaintedItem::drawPoint(int x, int y) {
    checkRecordingAndAdd([x, y](QPainter* p) {
        p->drawPoint(x, y);
    });
}

void QmlNetRecordingPaintedItem::drawPolygon(const QPoint *points, int pointCount, Qt::FillRule fillRule) {
    std::vector<QPoint> pointsCopy;
    for(int i=0; i<pointCount; i++) {
        pointsCopy.push_back(points[i]);
    }
    checkRecordingAndAdd([pointsCopy, fillRule](QPainter* p) {
        p->drawPolygon(&pointsCopy[0], pointsCopy.size(), fillRule);
    });
}

void QmlNetRecordingPaintedItem::drawPolyline(const QPoint *points, int pointCount) {
    std::vector<QPoint> pointsCopy;
    for(int i=0; i<pointCount; i++) {
        pointsCopy.push_back(points[i]);
    }
    checkRecordingAndAdd([pointsCopy](QPainter* p) {
        p->drawPolyline(&pointsCopy[0], pointsCopy.size());
    });
}

void QmlNetRecordingPaintedItem::drawRoundedRect(int x, int y, int w, int h, qreal xRadius, qreal yRadius, Qt::SizeMode mode) {
    checkRecordingAndAdd([x, y, w, h, xRadius, yRadius, mode](QPainter* p) {
        p->drawRoundedRect(x, y, w, h, xRadius, yRadius, mode);
    });
}

void QmlNetRecordingPaintedItem::eraseRect(int x, int y, int width, int height) {
    checkRecordingAndAdd([x, y, width, height](QPainter* p) {
        p->eraseRect(x, y, width, height);
    });
}

void QmlNetRecordingPaintedItem::setBackground(int colorId) {
    auto color = m_colorMap[colorId];
    checkRecordingAndAdd([color](QPainter* p) {
        p->setBackground(QBrush(color));
    });
}

void QmlNetRecordingPaintedItem::setBackgroundMode(Qt::BGMode mode) {
    checkRecordingAndAdd([mode](QPainter* p) {
        p->setBackgroundMode(mode);
    });
}

//void QmlNetRecordingPaintedItem::setClipPath(const QPainterPath &path, Qt::ClipOperation operation) {
//    QPainterPath pathCopy = path;
//    checkRecordingAndAdd([pathCopy, operation](QPainter* p) {
//        p->setClipPath(pathCopy, operation);
//    });
//}

void QmlNetRecordingPaintedItem::setClipRect(int x, int y, int width, int height, Qt::ClipOperation operation) {
    checkRecordingAndAdd([x, y, width, height, operation](QPainter* p) {
        p->setClipRect(x, y, width, height, operation);
    });
}

void QmlNetRecordingPaintedItem::setClipping(bool enable) {
    checkRecordingAndAdd([enable](QPainter* p) {
        p->setClipping(enable);
    });
}

void QmlNetRecordingPaintedItem::setCompositionMode(QPainter::CompositionMode mode) {
    checkRecordingAndAdd([mode](QPainter* p) {
        p->setCompositionMode(mode);
    });
}

void QmlNetRecordingPaintedItem::setLayoutDirection(Qt::LayoutDirection direction) {
    checkRecordingAndAdd([direction](QPainter* p) {
        p->setLayoutDirection(direction);
    });
}

void QmlNetRecordingPaintedItem::setOpacity(qreal opacity) {
    checkRecordingAndAdd([opacity](QPainter* p) {
        p->setOpacity(opacity);
    });
}

void QmlNetRecordingPaintedItem::setRenderHint(QPainter::RenderHint hint, bool on) {
    checkRecordingAndAdd([hint, on](QPainter* p) {
        p->setRenderHint(hint, on);
    });
}

void QmlNetRecordingPaintedItem::setTransform(const QTransform &transform, bool combine) {
    QTransform transformCopy = transform;
    checkRecordingAndAdd([transformCopy, combine](QPainter* p) {
        p->setTransform(transformCopy, combine);
    });
}

void QmlNetRecordingPaintedItem::setViewTransformEnabled(bool enable) {
    checkRecordingAndAdd([enable](QPainter* p) {
        p->setViewTransformEnabled(enable);
    });
}

void QmlNetRecordingPaintedItem::setWorldTransform(const QTransform &matrix, bool combine) {
    QTransform transformCopy = matrix;
    checkRecordingAndAdd([transformCopy, combine](QPainter* p) {
        p->setWorldTransform(transformCopy, combine);
    });
}

void QmlNetRecordingPaintedItem::setWorldMatrixEnabled(bool enable) {
    checkRecordingAndAdd([enable](QPainter* p) {
        p->setWorldMatrixEnabled(enable);
    });
}

void QmlNetRecordingPaintedItem::shear(qreal sh, qreal sv) {
    checkRecordingAndAdd([sh, sv](QPainter* p) {
        p->shear(sh, sv);
    });
}

void QmlNetRecordingPaintedItem::translate(qreal dx, qreal dy) {
    checkRecordingAndAdd([dx, dy](QPainter* p) {
        p->translate(dx, dy);
    });
}

int QmlNetRecordingPaintedItem::registerColor(QString colorString) {
    QColor color(colorString);
    for(int i=0; i<std::numeric_limits<int>::max(); i++) {
        if(m_colorMap.find(i) == m_colorMap.end()) {
            m_colorMap[i] = color;
            return i;
        }
    }
    throw std::runtime_error("No free color id found");
}

void QmlNetRecordingPaintedItem::freeColor(int colorId) {
    if(m_colorMap.find(colorId) != m_colorMap.end()) {
        m_colorMap.erase(colorId);
    }
}

int QmlNetRecordingPaintedItem::registerFontFamily(QString fontFamilyString) {
    for(int i=0; i<std::numeric_limits<int>::max(); i++) {
        if(m_fontFamilyMap.find(i) == m_fontFamilyMap.end()) {
            m_fontFamilyMap[i] = fontFamilyString;
            return i;
        }
    }
    throw std::runtime_error("No free font family id found");
}

void QmlNetRecordingPaintedItem::freeFontFamily(int fontFamilyId) {
    if(m_fontFamilyMap.find(fontFamilyId) != m_fontFamilyMap.end()) {
        m_fontFamilyMap.erase(fontFamilyId);
    }
}

QSize QmlNetRecordingPaintedItem::getStringSize(int fontFamilyId, int fontSizePx, QString text) {
    auto fontFamilyName = m_fontFamilyMap[fontFamilyId];
    QFont font(fontFamilyName);
    font.setPixelSize(fontSizePx);

    QFontMetrics metrics(font);
    return metrics.size(0, text);
}

void QmlNetRecordingPaintedItem::inputMethodEvent(QInputMethodEvent *e)
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

QVariant QmlNetRecordingPaintedItem::inputMethodQuery(Qt::InputMethodQuery property) const {
    return QQuickItem::inputMethodQuery(property);
}

void QmlNetRecordingPaintedItem::checkRecordingAndAdd(std::function<void(QPainter*)> action) {
    if(!m_isRecording) {
        throw std::runtime_error("No recording session is running. Call beginRecordPaintActions");
    }
    //this makes the record API thread safe so that it is possible on the .Net side to add the recordings
    //in parallel (as long as they don't depend on each other)
    m_recordActionMutex.lock();
    m_recordedPaintActions.push_back(action);
    m_recordActionMutex.unlock();
}

void QmlNetRecordingPaintedItem::setPaintedItemToHandler(QObject* handler, QmlNetRecordingPaintedItem* paintedItemPtr) {
    if(handler != nullptr) {
        auto paintedItemRef = (int64_t)paintedItemPtr;
        auto inetQPainterRef = (int64_t)((INetQPainter*)paintedItemPtr);
        QMetaObject::invokeMethod(handler, "__setPaintedItem", Q_ARG(QVariant, QVariant::fromValue(paintedItemRef)), Q_ARG(QVariant, QVariant::fromValue(QVariant::fromValue(inetQPainterRef))));
    }
}

void QmlNetRecordingPaintedItem::paint(QPainter *painter)
{
    m_paintActionMutex.lock();

    for(auto pa : m_paintActions) {
        pa(painter);
    }

    m_paintActionMutex.unlock();
}

extern "C" {

Q_DECL_EXPORT void qqmlnetrecordingpainteditem_beginRecordPaintActions(QmlNetRecordingPaintedItem* paintedItem) {
    paintedItem->beginRecordPaintActions();
}

Q_DECL_EXPORT void qqmlnetrecordingpainteditem_endRecordPaintActions(QmlNetRecordingPaintedItem* paintedItem) {
    paintedItem->endRecordPaintActions();
}

}
