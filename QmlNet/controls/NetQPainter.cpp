#include "NetQPainter.h"
#include <stdexcept>

NetQPainter::NetQPainter(QPainter* qpainter)
    : m_qpainter(qpainter)
{
}
NetQPainter::~NetQPainter()
{

}

void NetQPainter::setPen(int colorId)
{
    auto color = m_colorMap.at(colorId);
    QPen pen(color);
    m_qpainter->setPen(color);
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
