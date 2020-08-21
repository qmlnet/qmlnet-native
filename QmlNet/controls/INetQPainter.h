#ifndef NETQPAINTER_H
#define NETQPAINTER_H

#include <QImage>
#include <QPainter>
#include <QPainterPath>
#include <QPoint>
#include <QRect>
#include <QSize>
#include <QString>

class INetQPainter
{
public:
    virtual ~INetQPainter() = default;

    virtual void setPen(int colorId) = 0;
    virtual void resetPen() = 0;
    virtual void setBrush(int colorId) = 0;
    virtual void resetBrush() = 0;
    virtual void setFont(int fontFamilyId, bool isBold, bool isItalic, bool isUnderline, int pxSize) = 0;
    virtual void setFontFamily(int fontFamilyId) = 0;
    virtual void setFontBold(bool isBold) = 0;
    virtual void setFontItalic(bool isItalic) = 0;
    virtual void setFontUnderline(bool isUnderline) = 0;
    virtual void setFontSize(int pxSize) = 0;
    virtual void drawText(int x, int y, QString text) = 0;
    virtual void drawText(int x, int y, int width, int height, int flags, QString text) = 0;
    virtual void drawRect(int x, int y, int width, int height) = 0;
    virtual void fillRect(int x, int y, int width, int height, int colorId) = 0;
    virtual void fillRect(int x, int y, int width, int height) = 0;
    virtual void drawArc(int x, int y, int width, int height, int startAngle, int spanAngle) = 0;
    virtual void drawChord(int x, int y, int width, int height, int startAngle, int spanAngle) = 0;
    virtual void drawConvexPolygon(const QPoint *points, int pointCount) = 0;
    virtual void drawEllipse(int x, int y, int width, int height) = 0;
    virtual void drawImage(const QPoint &point, const QImage &image, const QRect &source, Qt::ImageConversionFlags flags = Qt::AutoColor) = 0;
    virtual void drawLine(int x1, int y1, int x2, int y2) = 0;
//    virtual void drawPath(const QPainterPath &path) = 0;
//    virtual void fillPath(const QPainterPath &path, int colorId) = 0;
//    virtual void strokePath(const QPainterPath &path, int colorId) = 0;
    virtual void drawPie(int x, int y, int width, int height, int startAngle, int spanAngle) = 0;
    virtual void drawPoint(int x, int y) = 0;
    virtual void drawPolygon(const QPoint *points, int pointCount, Qt::FillRule fillRule = Qt::OddEvenFill) = 0;
    virtual void drawPolyline(const QPoint *points, int pointCount) = 0;
    virtual void drawRoundedRect(int x, int y, int w, int h, qreal xRadius, qreal yRadius, Qt::SizeMode mode = Qt::AbsoluteSize) = 0;
    virtual void eraseRect(int x, int y, int width, int height) = 0;

    virtual void setBackground(int colorId) = 0;
    virtual void setBackgroundMode(Qt::BGMode mode) = 0;

//    virtual void setClipPath(const QPainterPath &path, Qt::ClipOperation operation = Qt::ReplaceClip) = 0;
    virtual void setClipRect(int x, int y, int width, int height, Qt::ClipOperation operation = Qt::ReplaceClip) = 0;
    virtual void setClipping(bool enable) = 0;

    virtual void setCompositionMode(QPainter::CompositionMode mode) = 0;

    virtual void setLayoutDirection(Qt::LayoutDirection direction) = 0;

    virtual void setOpacity(qreal opacity) = 0;
    virtual void setRenderHint(QPainter::RenderHint hint, bool on) = 0;

    virtual void setTransform(const QTransform &transform, bool combine) = 0;
    virtual void setViewTransformEnabled(bool enable) = 0;

    virtual void setWorldTransform(const QTransform &matrix, bool combine) = 0;
    virtual void setWorldMatrixEnabled(bool enable) = 0;

    virtual void shear(qreal sh, qreal sv) = 0;

    virtual void translate(qreal dx, qreal dy) = 0;

    //color management
    virtual int registerColor(QString colorString) = 0;
    virtual void freeColor(int colorId) = 0;

    //font management
    virtual int registerFontFamily(QString fontFamilyName) = 0;
    virtual void freeFontFamily(int fontId) = 0;

    virtual QSize getStringSize(int fontFamilyId, int fontSizePx, QString text) = 0;
};

#endif // NETQPAINTER_H
