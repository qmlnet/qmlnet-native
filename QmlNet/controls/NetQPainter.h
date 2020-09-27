#ifndef NETQPAINTER_H
#define NETQPAINTER_H

#include <QPainter>
#include <map>

class NetQPainter
{
public:
    NetQPainter(QPainter* qpainter);
    ~NetQPainter();

    void setPen(int colorId, int width);
    void resetPen();
    void setBrush(int colorId);
    void resetBrush();
    void setFont(int fontFamilyId, bool isBold, bool isItalic, bool isUnderline, int pxSize);
    void setFontFamily(int fontFamilyId);
    void setFontBold(bool isBold);
    void setFontItalic(bool isItalic);
    void setFontUnderline(bool isUnderline);
    void setFontSize(int pxSize);
    void drawText(int x, int y, QString text);
    void drawText(int x, int y, int width, int height, int flags, QString text);
    void drawRect(int x, int y, int width, int height);
    void fillRect(int x, int y, int width, int height, int colorId);
    void fillRect(int x, int y, int width, int height);
    void drawArc(int x, int y, int width, int height, int startAngle, int spanAngle);
    void drawChord(int x, int y, int width, int height, int startAngle, int spanAngle);
    void drawConvexPolygon(const QPoint *points, int pointCount);
    void drawEllipse(int x, int y, int width, int height);
    void drawImage(const QPoint &point, const QImage &image, const QRect &source, Qt::ImageConversionFlags flags = Qt::AutoColor);
    void drawLine(int x1, int y1, int x2, int y2);
//    void drawPath(const QPainterPath &path);
//    void fillPath(const QPainterPath &path, int colorId);
//    void strokePath(const QPainterPath &path, int colorId);
    void drawPie(int x, int y, int width, int height, int startAngle, int spanAngle);
    void drawPoint(int x, int y);
    void drawPolygon(const QPoint *points, int pointCount, Qt::FillRule fillRule = Qt::OddEvenFill);
    void drawPolyline(const QPoint *points, int pointCount);
    void drawRoundedRect(int x, int y, int w, int h, qreal xRadius, qreal yRadius, Qt::SizeMode mode = Qt::AbsoluteSize);
    void eraseRect(int x, int y, int width, int height);

    void setBackground(int colorId);
    void setBackgroundMode(Qt::BGMode mode);

//    void setClipPath(const QPainterPath &path, Qt::ClipOperation operation = Qt::ReplaceClip);
    void setClipRect(int x, int y, int width, int height, Qt::ClipOperation operation = Qt::ReplaceClip);
    void setClipping(bool enable);

    void setCompositionMode(QPainter::CompositionMode mode);

    void setLayoutDirection(Qt::LayoutDirection direction);

    void setOpacity(qreal opacity);
    void setRenderHint(QPainter::RenderHint hint, bool on);

    void setTransform(const QTransform &transform, bool combine);
    void setViewTransformEnabled(bool enable);

    void setWorldTransform(const QTransform &matrix, bool combine);
    void setWorldMatrixEnabled(bool enable);

    void shear(qreal sh, qreal sv);

    void translate(qreal dx, qreal dy);

    //color management
    int registerColor(QString colorString);
    void freeColor(int colorId);

    //font management
    int registerFontFamily(QString fontFamilyName);
    void freeFontFamily(int fontId);

    static QSize getStringSize(QChar* fontFamilyName, int fontSizePx, QString text);

private:
    QPainter* m_qpainter;

    std::map<int, QColor> m_colorMap;
    std::map<int, QString> m_fontFamilyMap;
};

#endif
