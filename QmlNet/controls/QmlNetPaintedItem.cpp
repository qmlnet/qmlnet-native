#include "QmlNetPaintedItem.h"
#include <QPainter>
#include <stdexcept>

QmlNetPaintedItem::QmlNetPaintedItem(QQuickItem *parent)
    : QQuickPaintedItem(parent)
{
}

QmlNetPaintedItem::~QmlNetPaintedItem() {
    setPaintedItemToHandler(m_paintHandler, nullptr);
}

QObject* QmlNetPaintedItem::paintHandler() const {
    return m_paintHandler;
}

void QmlNetPaintedItem::setPaintHandler(QObject* paintHandler) {
    setPaintedItemToHandler(m_paintHandler, nullptr);
    m_paintHandler = paintHandler;
    if(m_paintHandler != nullptr) {
        setPaintedItemToHandler(m_paintHandler, this);
    }
}

bool QmlNetPaintedItem::supportsTextInput() const {
    return m_supportsTextInput;
}

void QmlNetPaintedItem::setSupportsTextInput(bool supportsTextInput) {
    m_supportsTextInput = supportsTextInput;
    setFlag(ItemAcceptsInputMethod, supportsTextInput);
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
   //if the paint calls come in the UI thread this should not be necessary because the Renderer Thread halts the UI thread
   //but better safe than sorry
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

void QmlNetPaintedItem::setFont(int fontFamilyId, bool isBold, bool isItalic, bool isUnderline, int pxSize) {
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

void QmlNetPaintedItem::setFontFamily(int fontFamilyId) {
    auto fontFamilyName = m_fontFamilyMap[fontFamilyId];
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

void QmlNetPaintedItem::drawArc(int x, int y, int width, int height, int startAngle, int spanAngle) {
    checkRecordingAndAdd([x,y,width, height, startAngle, spanAngle](QPainter* p) {
        p->drawArc(x, y, width, height, startAngle, spanAngle);
    });
}

void QmlNetPaintedItem::drawChord(int x, int y, int width, int height, int startAngle, int spanAngle) {
    checkRecordingAndAdd([x,y,width, height, startAngle, spanAngle](QPainter* p) {
        p->drawChord(x, y, width, height, startAngle, spanAngle);
    });
}

void QmlNetPaintedItem::drawConvexPolygon(const QPoint *points, int pointCount) {
    std::vector<QPoint> pointsCopy;
    for(int i=0; i<pointCount; i++) {
        pointsCopy.push_back(points[i]);
    }
    checkRecordingAndAdd([pointsCopy](QPainter* p) {
        p->drawConvexPolygon(&pointsCopy[0], pointsCopy.size());
    });
}

void QmlNetPaintedItem::drawEllipse(int x, int y, int width, int height) {
    checkRecordingAndAdd([x,y,width, height](QPainter* p) {
        p->drawEllipse(x, y, width, height);
    });
}

void QmlNetPaintedItem::drawImage(const QPoint &point, const QImage &image, const QRect &source, Qt::ImageConversionFlags flags) {
    QPoint pointCopy = point;
    QImage imgCopy = image;
    QRect sourceCopy = source;
    checkRecordingAndAdd([pointCopy, imgCopy, sourceCopy, flags](QPainter* p) {
        p->drawImage(pointCopy, imgCopy, sourceCopy, flags);
    });
}

void QmlNetPaintedItem::drawLine(int x1, int y1, int x2, int y2) {
    checkRecordingAndAdd([x1, y1, x2, y2](QPainter* p) {
        p->drawLine(x1, y1, x2, y2);
    });
}

//void QmlNetPaintedItem::drawPath(const QPainterPath &path) {
//    QPainterPath pathCopy = path;
//    checkRecordingAndAdd([pathCopy](QPainter* p) {
//        p->drawPath(pathCopy);
//    });
//}

//void QmlNetPaintedItem::fillPath(const QPainterPath &path, int colorId) {
//    QPainterPath pathCopy = path;
//    auto color = m_colorMap[colorId];
//    checkRecordingAndAdd([pathCopy, color](QPainter* p) {
//        p->fillPath(pathCopy, QBrush(color));
//    });
//}

//void QmlNetPaintedItem::strokePath(const QPainterPath &path, int colorId) {
//    QPainterPath pathCopy = path;
//    auto color = m_colorMap[colorId];
//    checkRecordingAndAdd([pathCopy, color](QPainter* p) {
//        p->strokePath(pathCopy, QPen(color));
//    });
//}

void QmlNetPaintedItem::drawPie(int x, int y, int width, int height, int startAngle, int spanAngle) {
    checkRecordingAndAdd([x, y, width, height, startAngle, spanAngle](QPainter* p) {
        p->drawPie(x, y, width, height, startAngle, spanAngle);
    });
}

void QmlNetPaintedItem::drawPoint(int x, int y) {
    checkRecordingAndAdd([x, y](QPainter* p) {
        p->drawPoint(x, y);
    });
}

void QmlNetPaintedItem::drawPolygon(const QPoint *points, int pointCount, Qt::FillRule fillRule) {
    std::vector<QPoint> pointsCopy;
    for(int i=0; i<pointCount; i++) {
        pointsCopy.push_back(points[i]);
    }
    checkRecordingAndAdd([pointsCopy, fillRule](QPainter* p) {
        p->drawPolygon(&pointsCopy[0], pointsCopy.size(), fillRule);
    });
}

void QmlNetPaintedItem::drawPolyline(const QPoint *points, int pointCount) {
    std::vector<QPoint> pointsCopy;
    for(int i=0; i<pointCount; i++) {
        pointsCopy.push_back(points[i]);
    }
    checkRecordingAndAdd([pointsCopy](QPainter* p) {
        p->drawPolyline(&pointsCopy[0], pointsCopy.size());
    });
}

void QmlNetPaintedItem::drawRoundedRect(int x, int y, int w, int h, qreal xRadius, qreal yRadius, Qt::SizeMode mode) {
    checkRecordingAndAdd([x, y, w, h, xRadius, yRadius, mode](QPainter* p) {
        p->drawRoundedRect(x, y, w, h, xRadius, yRadius, mode);
    });
}

void QmlNetPaintedItem::eraseRect(int x, int y, int width, int height) {
    checkRecordingAndAdd([x, y, width, height](QPainter* p) {
        p->eraseRect(x, y, width, height);
    });
}

void QmlNetPaintedItem::setBackground(int colorId) {
    auto color = m_colorMap[colorId];
    checkRecordingAndAdd([color](QPainter* p) {
        p->setBackground(QBrush(color));
    });
}

void QmlNetPaintedItem::setBackgroundMode(Qt::BGMode mode) {
    checkRecordingAndAdd([mode](QPainter* p) {
        p->setBackgroundMode(mode);
    });
}

//void QmlNetPaintedItem::setClipPath(const QPainterPath &path, Qt::ClipOperation operation) {
//    QPainterPath pathCopy = path;
//    checkRecordingAndAdd([pathCopy, operation](QPainter* p) {
//        p->setClipPath(pathCopy, operation);
//    });
//}

void QmlNetPaintedItem::setClipRect(int x, int y, int width, int height, Qt::ClipOperation operation) {
    checkRecordingAndAdd([x, y, width, height, operation](QPainter* p) {
        p->setClipRect(x, y, width, height, operation);
    });
}

void QmlNetPaintedItem::setClipping(bool enable) {
    checkRecordingAndAdd([enable](QPainter* p) {
        p->setClipping(enable);
    });
}

void QmlNetPaintedItem::setCompositionMode(QPainter::CompositionMode mode) {
    checkRecordingAndAdd([mode](QPainter* p) {
        p->setCompositionMode(mode);
    });
}

void QmlNetPaintedItem::setLayoutDirection(Qt::LayoutDirection direction) {
    checkRecordingAndAdd([direction](QPainter* p) {
        p->setLayoutDirection(direction);
    });
}

void QmlNetPaintedItem::setOpacity(qreal opacity) {
    checkRecordingAndAdd([opacity](QPainter* p) {
        p->setOpacity(opacity);
    });
}

void QmlNetPaintedItem::setRenderHint(QPainter::RenderHint hint, bool on) {
    checkRecordingAndAdd([hint, on](QPainter* p) {
        p->setRenderHint(hint, on);
    });
}

void QmlNetPaintedItem::setTransform(const QTransform &transform, bool combine) {
    QTransform transformCopy = transform;
    checkRecordingAndAdd([transformCopy, combine](QPainter* p) {
        p->setTransform(transformCopy, combine);
    });
}

void QmlNetPaintedItem::setViewTransformEnabled(bool enable) {
    checkRecordingAndAdd([enable](QPainter* p) {
        p->setViewTransformEnabled(enable);
    });
}

void QmlNetPaintedItem::setWorldTransform(const QTransform &matrix, bool combine) {
    QTransform transformCopy = matrix;
    checkRecordingAndAdd([transformCopy, combine](QPainter* p) {
        p->setWorldTransform(transformCopy, combine);
    });
}

void QmlNetPaintedItem::setWorldMatrixEnabled(bool enable) {
    checkRecordingAndAdd([enable](QPainter* p) {
        p->setWorldMatrixEnabled(enable);
    });
}

void QmlNetPaintedItem::shear(qreal sh, qreal sv) {
    checkRecordingAndAdd([sh, sv](QPainter* p) {
        p->shear(sh, sv);
    });
}

void QmlNetPaintedItem::translate(qreal dx, qreal dy) {
    checkRecordingAndAdd([dx, dy](QPainter* p) {
        p->translate(dx, dy);
    });
}

int QmlNetPaintedItem::registerColor(QString colorString) {
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

int QmlNetPaintedItem::registerFontFamily(QString fontFamilyString) {
    for(int i=0; i<std::numeric_limits<int>::max(); i++) {
        if(m_fontFamilyMap.find(i) == m_fontFamilyMap.end()) {
            m_fontFamilyMap[i] = fontFamilyString;
            return i;
        }
    }
    throw std::runtime_error("No free font family id found");
}

void QmlNetPaintedItem::freeFontFamily(int fontFamilyId) {
    if(m_fontFamilyMap.find(fontFamilyId) != m_fontFamilyMap.end()) {
        m_fontFamilyMap.erase(fontFamilyId);
    }
}

QSize QmlNetPaintedItem::getStringSize(int fontFamilyId, int fontSizePx, QString text) {
    auto fontFamilyName = m_fontFamilyMap[fontFamilyId];
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
    //this makes the record API thread safe so that it is possible on the .Net side to add the recordings
    //in parallel (as long as they don't depend on each other)
    m_recordActionMutex.lock();
    m_recordedPaintActions.push_back(action);
    m_recordActionMutex.unlock();
}

void QmlNetPaintedItem::setPaintedItemToHandler(QObject* handler, QmlNetPaintedItem* paintedItemPtr) {
    if(handler != nullptr) {
        auto paintedItemRef = (int64_t)paintedItemPtr;
        auto inetQPainterRef = (int64_t)((INetQPainter*)paintedItemPtr);
        QMetaObject::invokeMethod(handler, "__setPaintedItem", Q_ARG(QVariant, QVariant::fromValue(paintedItemRef)), Q_ARG(QVariant, QVariant::fromValue(QVariant::fromValue(inetQPainterRef))));
    }
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

}
