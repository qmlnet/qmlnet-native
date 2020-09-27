#include "NetQPainter.h"
#include <stdexcept>

NetQPainter::NetQPainter(QPainter* qpainter)
    : m_qpainter(qpainter)
{
}
NetQPainter::~NetQPainter()
{

}

void NetQPainter::setPen(int colorId, int width)
{
    auto color = m_colorMap.at(colorId);
    QPen pen(color);
    pen.setWidth(width);
    m_qpainter->setPen(pen);
}

void NetQPainter::resetPen() {
    m_qpainter->setPen(QPen());
}

void NetQPainter::setBrush(int colorId)
{
    auto color = m_colorMap.at(colorId);
    QBrush brush(color);
    m_qpainter->setBrush(brush);
}

void NetQPainter::resetBrush()
{
    m_qpainter->setBrush(QBrush());
}

void NetQPainter::setFont(int fontFamilyId, bool isBold, bool isItalic, bool isUnderline, int pxSize)
{
    auto fontFamilyName = m_fontFamilyMap[fontFamilyId];
    auto font = QFont(fontFamilyName);
    font.setBold(isBold);
    font.setItalic(isItalic);
    font.setUnderline(isUnderline);
    font.setPixelSize(pxSize);
    m_qpainter->setFont(font);
}

void NetQPainter::setFontFamily(int fontFamilyId)
{
    auto fontFamilyName = m_fontFamilyMap[fontFamilyId];
    auto font = m_qpainter->font();
    font.setFamily(fontFamilyName);
    m_qpainter->setFont(font);
}

void NetQPainter::setFontBold(bool isBold)
{
    auto font = m_qpainter->font();
    font.setBold(isBold);
    m_qpainter->setFont(font);
}

void NetQPainter::setFontItalic(bool isItalic)
{
    auto font = m_qpainter->font();
    font.setItalic(isItalic);
    m_qpainter->setFont(font);
}

void NetQPainter::setFontUnderline(bool isUnderline)
{
    auto font = m_qpainter->font();
    font.setUnderline(isUnderline);
    m_qpainter->setFont(font);
}

void NetQPainter::setFontSize(int pxSize)
{
    auto font = m_qpainter->font();
    font.setPixelSize(pxSize);
    m_qpainter->setFont(font);
}

void NetQPainter::drawText(int x, int y, QString text)
{
    auto vp = m_qpainter->viewport();
    m_qpainter->drawText(vp.x() + x, vp.y() + y, text);
}

void NetQPainter::drawText(int x, int y, int width, int height, int flags, QString text)
{
    QRect rect(x, y, width, height);
    m_qpainter->drawText(rect, flags ,text);
}

void NetQPainter::drawRect(int x, int y, int width, int height)
{
    m_qpainter->drawRect(x, y, width, height);
}

void NetQPainter::fillRect(int x, int y, int width, int height, int colorId)
{
    auto color = m_colorMap.at(colorId);
    QBrush brush(color);
    m_qpainter->fillRect(x, y, width, height, brush);
}

void NetQPainter::fillRect(int x, int y, int width, int height)
{
    m_qpainter->fillRect(x, y, width, height, m_qpainter->brush());
}

void NetQPainter::drawArc(int x, int y, int width, int height, int startAngle, int spanAngle)
{
    m_qpainter->drawArc(x, y, width, height, startAngle, spanAngle);
}

void NetQPainter::drawChord(int x, int y, int width, int height, int startAngle, int spanAngle)
{
    m_qpainter->drawChord(x, y, width, height, startAngle, spanAngle);
}

void NetQPainter::drawConvexPolygon(const QPoint *points, int pointCount)
{
    m_qpainter->drawConvexPolygon(points, pointCount);
}

void NetQPainter::drawEllipse(int x, int y, int width, int height)
{
    m_qpainter->drawEllipse(x, y, width, height);
}

void NetQPainter::drawImage(const QPoint &point, const QImage &image, const QRect &source, Qt::ImageConversionFlags flags)
{
    m_qpainter->drawImage(point, image, source, flags);
}

void NetQPainter::drawLine(int x1, int y1, int x2, int y2)
{
    m_qpainter->drawLine(x1, y1, x2, y2);
}

//    void drawPath(const QPainterPath &path) override;
//    void fillPath(const QPainterPath &path, int colorId) override;
//    void strokePath(const QPainterPath &path, int colorId) override;
void NetQPainter::drawPie(int x, int y, int width, int height, int startAngle, int spanAngle)
{
    m_qpainter->drawPie(x, y, width, height, startAngle, spanAngle);
}

void NetQPainter::drawPoint(int x, int y)
{
    m_qpainter->drawPoint(x, y);
}

void NetQPainter::drawPolygon(const QPoint *points, int pointCount, Qt::FillRule fillRule)
{
    m_qpainter->drawPolygon(points, pointCount, fillRule);
}

void NetQPainter::drawPolyline(const QPoint *points, int pointCount)
{
    m_qpainter->drawPolyline(points, pointCount);
}

void NetQPainter::drawRoundedRect(int x, int y, int w, int h, qreal xRadius, qreal yRadius, Qt::SizeMode mode)
{
    m_qpainter->drawRoundedRect(x, y, w, h, xRadius, yRadius, mode);
}

void NetQPainter::eraseRect(int x, int y, int width, int height)
{
    m_qpainter->eraseRect(x, y, width, height);
}

void NetQPainter::setBackground(int colorId)
{
    auto color = m_colorMap[colorId];
    m_qpainter->setBackground(QBrush(color));
}

void NetQPainter::setBackgroundMode(Qt::BGMode mode)
{
    m_qpainter->setBackgroundMode(mode);
}

//    void setClipPath(const QPainterPath &path, Qt::ClipOperation operation = Qt::ReplaceClip) override;
void NetQPainter::setClipRect(int x, int y, int width, int height, Qt::ClipOperation operation)
{
    m_qpainter->setClipRect(x, y, width, height, operation);
}

void NetQPainter::setClipping(bool enable)
{
    m_qpainter->setClipping(enable);
}

void NetQPainter::setCompositionMode(QPainter::CompositionMode mode)
{
    m_qpainter->setCompositionMode(mode);
}

void NetQPainter::setLayoutDirection(Qt::LayoutDirection direction)
{
    m_qpainter->setLayoutDirection(direction);
}

void NetQPainter::setOpacity(qreal opacity)
{
    m_qpainter->setOpacity(opacity);
}

void NetQPainter::setRenderHint(QPainter::RenderHint hint, bool on)
{
    m_qpainter->setRenderHint(hint, on);
}

void NetQPainter::setTransform(const QTransform &transform, bool combine)
{
    m_qpainter->setTransform(transform, combine);
}

void NetQPainter::setViewTransformEnabled(bool enable)
{
    m_qpainter->setViewTransformEnabled(enable);
}

void NetQPainter::setWorldTransform(const QTransform &matrix, bool combine)
{
    m_qpainter->setTransform(matrix, combine);
}

void NetQPainter::setWorldMatrixEnabled(bool enable)
{
    m_qpainter->setWorldMatrixEnabled(enable);
}

void NetQPainter::shear(qreal sh, qreal sv)
{
    m_qpainter->shear(sh, sv);
}

void NetQPainter::translate(qreal dx, qreal dy)
{
    m_qpainter->translate(dx, dy);
}

//color management
int NetQPainter::registerColor(QString colorString)
{
    QColor color(colorString);
    for(int i=0; i<std::numeric_limits<int>::max(); i++) {
        if(m_colorMap.find(i) == m_colorMap.end()) {
            m_colorMap[i] = color;
            return i;
        }
    }
    throw std::runtime_error("No free color id found");
}

void NetQPainter::freeColor(int colorId)
{
    if(m_colorMap.find(colorId) != m_colorMap.end()) {
        m_colorMap.erase(colorId);
    }
}

//font management
int NetQPainter::registerFontFamily(QString fontFamilyString)
{
    for(int i=0; i<std::numeric_limits<int>::max(); i++) {
        if(m_fontFamilyMap.find(i) == m_fontFamilyMap.end()) {
            m_fontFamilyMap[i] = fontFamilyString;
            return i;
        }
    }
    throw std::runtime_error("No free font family id found");
}

void NetQPainter::freeFontFamily(int fontId)
{
    if(m_fontFamilyMap.find(fontId) != m_fontFamilyMap.end()) {
        m_fontFamilyMap.erase(fontId);
    }
}

QSize NetQPainter::getStringSize(QChar* fontFamilyName, int fontSizePx, QString text)
{
    QString fontFamilyNameStr(fontFamilyName);
    QFont font(fontFamilyNameStr);
    font.setPixelSize(fontSizePx);

    QFontMetrics metrics(font);
    return metrics.size(0, text);
}

extern "C" {

Q_DECL_EXPORT void netqpainter_setPen(NetQPainter* painter, int colorId, int width) {
    painter->setPen(colorId, width);
}

Q_DECL_EXPORT void netqpainter_resetPen(NetQPainter* painter) {
    painter->resetPen();
}

Q_DECL_EXPORT void netqpainter_setBrush(NetQPainter* painter, int colorId) {
    painter->setBrush(colorId);
}

Q_DECL_EXPORT void netqpainter_resetBrush(NetQPainter* painter) {
    painter->resetBrush();
}

Q_DECL_EXPORT void netqpainter_setFont(NetQPainter* painter, int fontFamilyId, bool isBold, bool isItalic, bool isUnderline, int pxSize) {
    painter->setFont(fontFamilyId, isBold, isItalic, isUnderline, pxSize);
}

Q_DECL_EXPORT void netqpainter_setFontFamily(NetQPainter* painter, int fontFamilyId) {
    painter->setFontFamily(fontFamilyId);
}

Q_DECL_EXPORT void netqpainter_setFontBold(NetQPainter* painter, bool isBold) {
    painter->setFontBold(isBold);
}

Q_DECL_EXPORT void netqpainter_setFontItalic(NetQPainter* painter, bool isItalic) {
    painter->setFontItalic(isItalic);
}

Q_DECL_EXPORT void netqpainter_setFontUnderline(NetQPainter* painter, bool isUnderline) {
    painter->setFontUnderline(isUnderline);
}

Q_DECL_EXPORT void netqpainter_setFontSize(NetQPainter* painter, int pxSize) {
    painter->setFontSize(pxSize);
}

Q_DECL_EXPORT void netqpainter_drawText(NetQPainter* painter, int x, int y, QChar* text) {
    painter->drawText(x, y, QString(text));
}

Q_DECL_EXPORT void netqpainter_drawTextRect(NetQPainter* painter, int x, int y, int width, int height, int flags, QChar* text) {
    painter->drawText(x, y, width, height, flags, QString(text));
}

Q_DECL_EXPORT void netqpainter_drawRect(NetQPainter* painter, int x, int y, int width, int height) {
    painter->drawRect(x, y, width, height);
}

Q_DECL_EXPORT void netqpainter_fillRectColor(NetQPainter* painter, int x, int y, int width, int height, int colorId) {
    painter->fillRect(x, y, width, height, colorId);
}

Q_DECL_EXPORT void netqpainter_fillRect(NetQPainter* painter, int x, int y, int width, int height) {
    painter->fillRect(x, y, width, height);
}

Q_DECL_EXPORT int netqpainter_registerColor(NetQPainter* painter, QChar* colorString) {
    return painter->registerColor(QString(colorString));
}

Q_DECL_EXPORT void netqpainter_freeColor(NetQPainter* painter, int colorId) {
    painter->freeColor(colorId);
}

Q_DECL_EXPORT int netqpainter_registerFontFamily(NetQPainter* painter, QChar* fontFamilyString) {
    return painter->registerFontFamily(QString(fontFamilyString));
}

Q_DECL_EXPORT void netqpainter_freeFontFamily(NetQPainter* painter, int fontId) {
    painter->freeFontFamily(fontId);
}

struct StringSizeResult {
    int width;
    int height;
};

Q_DECL_EXPORT StringSizeResult netqpainter_getStringSize(QChar* fontFamilyName, int fontSizePx, QChar* text) {
    auto size = NetQPainter::getStringSize(fontFamilyName, fontSizePx, QString(text));
    StringSizeResult result;
    result.width = size.width();
    result.height = size.height();
    return result;
}


Q_DECL_EXPORT void netqpainter_drawArc(NetQPainter* painter, int x, int y, int width, int height, int startAngle, int spanAngle) {
    painter->drawArc(x, y, width, height, startAngle, spanAngle);
}

Q_DECL_EXPORT void netqpainter_drawChord(NetQPainter* painter, int x, int y, int width, int height, int startAngle, int spanAngle) {
    painter->drawChord(x, y, width, height, startAngle, spanAngle);
}

struct NetQPainter_Point {
    int x;
    int y;
};

struct NetQPainter_Rect {
    int x;
    int y;
    int width;
    int height;
};

Q_DECL_EXPORT void netqpainter_drawConvexPolygon(NetQPainter* painter, NetQPainter_Point* points, int pointCount) {
    std::vector<QPoint> pointVector;
    for(int i=0; i<pointCount; i++) {
        pointVector.push_back(QPoint(points[i].x, points[i].y));
    }
    painter->drawConvexPolygon(&pointVector[0], pointVector.size());
}

Q_DECL_EXPORT void netqpainter_drawEllipse(NetQPainter* painter, int x, int y, int width, int height) {
    painter->drawEllipse(x, y, width, height);
}

Q_DECL_EXPORT void netqpainter_drawImage(NetQPainter* painter, NetQPainter_Point point, uchar* imgData, int imgDataSize, NetQPainter_Rect sourceRect, int flags) {
    QImage img;
    img.loadFromData(imgData, imgDataSize);
    QPoint p(point.x, point.y);
    QRect sr(sourceRect.x, sourceRect.y, sourceRect.width, sourceRect.height);

    painter->drawImage(p, img, sr, (Qt::ImageConversionFlags)flags);
}

Q_DECL_EXPORT void netqpainter_drawImageFile(NetQPainter* painter, NetQPainter_Point point, QString filePath, NetQPainter_Rect sourceRect, int flags) {
    QImage img(filePath);
    QPoint p(point.x, point.y);
    QRect sr(sourceRect.x, sourceRect.y, sourceRect.width, sourceRect.height);

    painter->drawImage(p, img, sr, (Qt::ImageConversionFlags)flags);
}

Q_DECL_EXPORT void netqpainter_drawLine(NetQPainter* painter, int x1, int y1, int x2, int y2) {
    painter->drawLine(x1, y1, x2, y2);
}

//void drawPath(const QPainterPath &path) override;
//void fillPath(const QPainterPath &path, int colorId) override;
//void strokePath(const QPainterPath &path, int colorId) override;

Q_DECL_EXPORT void netqpainter_drawPie(NetQPainter* painter, int x, int y, int width, int height, int startAngle, int spanAngle) {
    painter->drawPie(x, y, width, height, startAngle, spanAngle);
}

Q_DECL_EXPORT void netqpainter_drawPoint(NetQPainter* painter, int x, int y) {
    painter->drawPoint(x, y);
}

Q_DECL_EXPORT void netqpainter_drawPolygon(NetQPainter* painter, NetQPainter_Point* points, int pointCount, bool oddFill) {
    std::vector<QPoint> pointVector;
    for(int i=0; i<pointCount; i++) {
        pointVector.push_back(QPoint(points[i].x, points[i].y));
    }

    Qt::FillRule fillRule = oddFill ? Qt::FillRule::OddEvenFill : Qt::FillRule::WindingFill;
    painter->drawPolygon(&pointVector[0], pointVector.size(), fillRule);
}

Q_DECL_EXPORT void netqpainter_drawPolyline(NetQPainter* painter, NetQPainter_Point* points, int pointCount) {
    std::vector<QPoint> pointVector;
    for(int i=0; i<pointCount; i++) {
        pointVector.push_back(QPoint(points[i].x, points[i].y));
    }

    painter->drawPolyline(&pointVector[0], pointVector.size());
}

Q_DECL_EXPORT void netqpainter_drawRoundedRect(NetQPainter* painter, int x, int y, int w, int h, qreal xRadius, qreal yRadius, bool absoluteSize) {
    painter->drawRoundedRect(x, y, w, h, xRadius, yRadius, absoluteSize ? Qt::SizeMode::AbsoluteSize : Qt::SizeMode::RelativeSize);
}

Q_DECL_EXPORT void netqpainter_eraseRect(NetQPainter* painter, int x, int y, int width, int height) {
    painter->eraseRect(x, y, width, height);
}

Q_DECL_EXPORT void netqpainter_setBackground(NetQPainter* painter, int colorId) {
    painter->setBackground(colorId);
}

Q_DECL_EXPORT void netqpainter_setBackgroundMode(NetQPainter* painter, bool opaque) {
    painter->setBackgroundMode(opaque ? Qt::BGMode::OpaqueMode : Qt::BGMode::TransparentMode);
}

//void setClipPath(const QPainterPath &path, Qt::ClipOperation operation = Qt::ReplaceClip) override;

enum NetQPainter_ClipOperation {
    NoClip = 1,
    ReplaceClip,
    IntersectClip
};

Q_DECL_EXPORT void netqpainter_setClipRect(NetQPainter* painter, int x, int y, int width, int height, NetQPainter_ClipOperation operation) {
    Qt::ClipOperation cop = Qt::ClipOperation::NoClip;
    switch(operation) {
    case NetQPainter_ClipOperation::NoClip:
        cop = Qt::ClipOperation::NoClip;
        break;
    case NetQPainter_ClipOperation::ReplaceClip:
        cop = Qt::ClipOperation::ReplaceClip;
        break;
    case NetQPainter_ClipOperation::IntersectClip:
        cop = Qt::ClipOperation::IntersectClip;
        break;
    }

    painter->setClipRect(x, y, width, height, cop);
}

Q_DECL_EXPORT void netqpainter_setClipping(NetQPainter* painter, bool enable) {
    painter->setClipping(enable);
}

enum NetQPainter_CompositionMode {
    CompositionMode_SourceOver = 1,
    CompositionMode_DestinationOver,
    CompositionMode_Clear,
    CompositionMode_Source,
    CompositionMode_Destination,
    CompositionMode_SourceIn,
    CompositionMode_DestinationIn,
    CompositionMode_SourceOut,
    CompositionMode_DestinationOut,
    CompositionMode_SourceAtop,
    CompositionMode_DestinationAtop,
    CompositionMode_Xor,

    //svg 1.2 blend modes
    CompositionMode_Plus,
    CompositionMode_Multiply,
    CompositionMode_Screen,
    CompositionMode_Overlay,
    CompositionMode_Darken,
    CompositionMode_Lighten,
    CompositionMode_ColorDodge,
    CompositionMode_ColorBurn,
    CompositionMode_HardLight,
    CompositionMode_SoftLight,
    CompositionMode_Difference,
    CompositionMode_Exclusion,

    // ROPs
    RasterOp_SourceOrDestination,
    RasterOp_SourceAndDestination,
    RasterOp_SourceXorDestination,
    RasterOp_NotSourceAndNotDestination,
    RasterOp_NotSourceOrNotDestination,
    RasterOp_NotSourceXorDestination,
    RasterOp_NotSource,
    RasterOp_NotSourceAndDestination,
    RasterOp_SourceAndNotDestination,
    RasterOp_NotSourceOrDestination,
    RasterOp_SourceOrNotDestination,
    RasterOp_ClearDestination,
    RasterOp_SetDestination,
    RasterOp_NotDestination
};

Q_DECL_EXPORT void netqpainter_setCompositionMode(NetQPainter* painter, NetQPainter_CompositionMode mode) {
    QPainter::CompositionMode cmode;
    switch(mode)
    {
    case NetQPainter_CompositionMode::CompositionMode_SourceOver:
        cmode = QPainter::CompositionMode::CompositionMode_SourceOver;
        break;
    case NetQPainter_CompositionMode::CompositionMode_DestinationOver:
        cmode = QPainter::CompositionMode::CompositionMode_DestinationOver;
        break;
    case NetQPainter_CompositionMode::CompositionMode_Clear:
        cmode = QPainter::CompositionMode::CompositionMode_Clear;
        break;
    case NetQPainter_CompositionMode::CompositionMode_Source:
        cmode = QPainter::CompositionMode::CompositionMode_Source;
        break;
    case NetQPainter_CompositionMode::CompositionMode_Destination:
        cmode = QPainter::CompositionMode::CompositionMode_Destination;
        break;
    case NetQPainter_CompositionMode::CompositionMode_SourceIn:
        cmode = QPainter::CompositionMode::CompositionMode_SourceIn;
        break;
    case NetQPainter_CompositionMode::CompositionMode_DestinationIn:
        cmode = QPainter::CompositionMode::CompositionMode_DestinationIn;
        break;
    case NetQPainter_CompositionMode::CompositionMode_SourceOut:
        cmode = QPainter::CompositionMode::CompositionMode_SourceOut;
        break;
    case NetQPainter_CompositionMode::CompositionMode_DestinationOut:
        cmode = QPainter::CompositionMode::CompositionMode_DestinationOut;
        break;
    case NetQPainter_CompositionMode::CompositionMode_SourceAtop:
        cmode = QPainter::CompositionMode::CompositionMode_SourceAtop;
        break;
    case NetQPainter_CompositionMode::CompositionMode_DestinationAtop:
        cmode = QPainter::CompositionMode::CompositionMode_DestinationAtop;
        break;
    case NetQPainter_CompositionMode::CompositionMode_Xor:
        cmode = QPainter::CompositionMode::CompositionMode_Xor;
        break;
    case NetQPainter_CompositionMode::CompositionMode_Plus:
        cmode = QPainter::CompositionMode::CompositionMode_Plus;
        break;
    case NetQPainter_CompositionMode::CompositionMode_Multiply:
        cmode = QPainter::CompositionMode::CompositionMode_Multiply;
        break;
    case NetQPainter_CompositionMode::CompositionMode_Screen:
        cmode = QPainter::CompositionMode::CompositionMode_Screen;
        break;
    case NetQPainter_CompositionMode::CompositionMode_Overlay:
        cmode = QPainter::CompositionMode::CompositionMode_Overlay;
        break;
    case NetQPainter_CompositionMode::CompositionMode_Darken:
        cmode = QPainter::CompositionMode::CompositionMode_Darken;
        break;
    case NetQPainter_CompositionMode::CompositionMode_Lighten:
        cmode = QPainter::CompositionMode::CompositionMode_Lighten;
        break;
    case NetQPainter_CompositionMode::CompositionMode_ColorDodge:
        cmode = QPainter::CompositionMode::CompositionMode_ColorDodge;
        break;
    case NetQPainter_CompositionMode::CompositionMode_ColorBurn:
        cmode = QPainter::CompositionMode::CompositionMode_ColorBurn;
        break;
    case NetQPainter_CompositionMode::CompositionMode_HardLight:
        cmode = QPainter::CompositionMode::CompositionMode_HardLight;
        break;
    case NetQPainter_CompositionMode::CompositionMode_SoftLight:
        cmode = QPainter::CompositionMode::CompositionMode_SoftLight;
        break;
    case NetQPainter_CompositionMode::CompositionMode_Difference:
        cmode = QPainter::CompositionMode::CompositionMode_Difference;
        break;
    case NetQPainter_CompositionMode::CompositionMode_Exclusion:
        cmode = QPainter::CompositionMode::CompositionMode_Exclusion;
        break;
    case NetQPainter_CompositionMode::RasterOp_SourceOrDestination:
        cmode = QPainter::CompositionMode::RasterOp_SourceOrDestination;
        break;
    case NetQPainter_CompositionMode::RasterOp_SourceAndDestination:
        cmode = QPainter::CompositionMode::RasterOp_SourceAndDestination;
        break;
    case NetQPainter_CompositionMode::RasterOp_SourceXorDestination:
        cmode = QPainter::CompositionMode::RasterOp_SourceXorDestination;
        break;
    case NetQPainter_CompositionMode::RasterOp_NotSourceAndNotDestination:
        cmode = QPainter::CompositionMode::RasterOp_NotSourceAndNotDestination;
        break;
    case NetQPainter_CompositionMode::RasterOp_NotSourceOrNotDestination:
        cmode = QPainter::CompositionMode::RasterOp_NotSourceOrNotDestination;
        break;
    case NetQPainter_CompositionMode::RasterOp_NotSourceXorDestination:
        cmode = QPainter::CompositionMode::RasterOp_NotSourceXorDestination;
        break;
    case NetQPainter_CompositionMode::RasterOp_NotSource:
        cmode = QPainter::CompositionMode::RasterOp_NotSource;
        break;
    case NetQPainter_CompositionMode::RasterOp_NotSourceAndDestination:
        cmode = QPainter::CompositionMode::RasterOp_NotSourceAndDestination;
        break;
    case NetQPainter_CompositionMode::RasterOp_SourceAndNotDestination:
        cmode = QPainter::CompositionMode::RasterOp_SourceAndNotDestination;
        break;
    case NetQPainter_CompositionMode::RasterOp_NotSourceOrDestination:
        cmode = QPainter::CompositionMode::RasterOp_NotSourceOrDestination;
        break;
    case NetQPainter_CompositionMode::RasterOp_SourceOrNotDestination:
        cmode = QPainter::CompositionMode::RasterOp_SourceOrNotDestination;
        break;
    case NetQPainter_CompositionMode::RasterOp_ClearDestination:
        cmode = QPainter::CompositionMode::RasterOp_ClearDestination;
        break;
    case NetQPainter_CompositionMode::RasterOp_SetDestination:
        cmode = QPainter::CompositionMode::RasterOp_SetDestination;
        break;
    case NetQPainter_CompositionMode::RasterOp_NotDestination:
        cmode = QPainter::CompositionMode::RasterOp_NotDestination;
        break;
    }

    painter->setCompositionMode(cmode);
}

enum NetQPainter_LayoutDirection {
    LeftToRight = 1,
    RightToLeft,
    LayoutDirectionAuto
};


Q_DECL_EXPORT void netqpainter_setLayoutDirection(NetQPainter* painter, NetQPainter_LayoutDirection dir) {
    Qt::LayoutDirection lDir = Qt::LayoutDirection::LeftToRight;
    switch(dir)
    {
    case NetQPainter_LayoutDirection::LeftToRight:
        lDir = Qt::LayoutDirection::LeftToRight;
        break;
    case NetQPainter_LayoutDirection::RightToLeft:
        lDir = Qt::LayoutDirection::RightToLeft;
        break;
    case NetQPainter_LayoutDirection::LayoutDirectionAuto:
        lDir = Qt::LayoutDirection::LayoutDirectionAuto;
        break;
    }

    painter->setLayoutDirection(lDir);
}

Q_DECL_EXPORT void netqpainter_setOpacity(NetQPainter* painter, double opacity) {
    painter->setOpacity(opacity);
}

Q_DECL_EXPORT void netqpainter_setRenderHint(NetQPainter* painter, QPainter::RenderHint hint, bool on) {
    painter->setRenderHint(hint, on);
}

Q_DECL_EXPORT void netqpainter_setTransform(NetQPainter* painter, double h11, double h12, double h13, double h21, double h22, double h23, double h31, double h32, double h33, bool combine) {
    QTransform transform(h11, h12, h13, h21, h22, h23, h31, h32, h33);
    painter->setTransform(transform, combine);
}

Q_DECL_EXPORT void netqpainter_setViewTransformEnabled(NetQPainter* painter, bool enabled) {
    painter->setViewTransformEnabled(enabled);
}

Q_DECL_EXPORT void netqpainter_setWorldTransform(NetQPainter* painter, double h11, double h12, double h13, double h21, double h22, double h23, double h31, double h32, double h33, bool combine) {
    QTransform transform(h11, h12, h13, h21, h22, h23, h31, h32, h33);
    painter->setWorldTransform(transform, combine);
}

Q_DECL_EXPORT void netqpainter_setWorldMatrixEnabled(NetQPainter* painter, bool enabled) {
    painter->setWorldMatrixEnabled(enabled);
}

Q_DECL_EXPORT void netqpainter_shear(NetQPainter* painter, double sh, double sv) {
    painter->shear(sh, sv);
}

Q_DECL_EXPORT void netqpainter_translate(NetQPainter* painter, double dx, double dy) {
    painter->translate(dx, dy);
}

}
