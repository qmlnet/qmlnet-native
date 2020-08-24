#ifndef QMLNETRECORDINGPAINTEDITEM_H
#define QMLNETRECORDINGPAINTEDITEM_H

#include <QtQuick/QQuickPaintedItem>
#include <QObject>
#include <vector>
#include <map>
#include <QMutex>
#include "INetQPainter.h"


class QmlNetRecordingPaintedItem : public QQuickPaintedItem, INetQPainter
{
    Q_OBJECT
    Q_PROPERTY(QObject* paintHandler READ paintHandler WRITE setPaintHandler)
    Q_PROPERTY(bool supportsTextInput READ supportsTextInput WRITE setSupportsTextInput)
    Q_PROPERTY(bool preeditActive READ preeditActive NOTIFY preeditActiveChanged)
    Q_PROPERTY(QString preeditText READ preeditText NOTIFY preeditTextChanged)
    QML_ELEMENT
public:
    QmlNetRecordingPaintedItem(QQuickItem *parent = nullptr);
    ~QmlNetRecordingPaintedItem();

    QObject* paintHandler() const;
    void setPaintHandler(QObject* paintHandler);
    bool supportsTextInput() const;
    void setSupportsTextInput(bool supportsTextInput);
    bool preeditActive();
    Q_SIGNAL void preeditActiveChanged();
    QString preeditText();
    Q_SIGNAL void preeditTextChanged();

    void paint(QPainter *painter) override;

    void beginRecordPaintActions();
    void endRecordPaintActions();

    //Record api
    void setPen(int colorId) override;
    void resetPen() override;
    void setBrush(int colorId) override;
    void resetBrush() override;
    void setFont(int fontFamilyId, bool isBold, bool isItalic, bool isUnderline, int pxSize) override;
    void setFontFamily(int fontFamilyId) override;
    void setFontBold(bool isBold) override;
    void setFontItalic(bool isItalic) override;
    void setFontUnderline(bool isUnderline) override;
    void setFontSize(int pxSize) override;
    void drawText(int x, int y, QString text) override;
    void drawText(int x, int y, int width, int height, int flags, QString text) override;
    void drawRect(int x, int y, int width, int height) override;
    void fillRect(int x, int y, int width, int height, int colorId) override;
    void fillRect(int x, int y, int width, int height) override;

    void drawArc(int x, int y, int width, int height, int startAngle, int spanAngle) override;
    void drawChord(int x, int y, int width, int height, int startAngle, int spanAngle) override;
    void drawConvexPolygon(const QPoint *points, int pointCount) override;
    void drawEllipse(int x, int y, int width, int height) override;
    void drawImage(const QPoint &point, const QImage &image, const QRect &source, Qt::ImageConversionFlags flags = Qt::AutoColor) override;
    void drawLine(int x1, int y1, int x2, int y2) override;
//    void drawPath(const QPainterPath &path) override;
//    void fillPath(const QPainterPath &path, int colorId) override;
//    void strokePath(const QPainterPath &path, int colorId) override;
    void drawPie(int x, int y, int width, int height, int startAngle, int spanAngle) override;
    void drawPoint(int x, int y) override;
    void drawPolygon(const QPoint *points, int pointCount, Qt::FillRule fillRule = Qt::OddEvenFill) override;
    void drawPolyline(const QPoint *points, int pointCount) override;
    void drawRoundedRect(int x, int y, int w, int h, qreal xRadius, qreal yRadius, Qt::SizeMode mode = Qt::AbsoluteSize) override;
    void eraseRect(int x, int y, int width, int height) override;

    void setBackground(int colorId) override;
    void setBackgroundMode(Qt::BGMode mode) override;

//    void setClipPath(const QPainterPath &path, Qt::ClipOperation operation = Qt::ReplaceClip) override;
    void setClipRect(int x, int y, int width, int height, Qt::ClipOperation operation = Qt::ReplaceClip) override;
    void setClipping(bool enable) override;

    void setCompositionMode(QPainter::CompositionMode mode) override;

    void setLayoutDirection(Qt::LayoutDirection direction) override;

    void setOpacity(qreal opacity) override;
    void setRenderHint(QPainter::RenderHint hint, bool on) override;

    void setTransform(const QTransform &transform, bool combine) override;
    void setViewTransformEnabled(bool enable) override;

    void setWorldTransform(const QTransform &matrix, bool combine) override;
    void setWorldMatrixEnabled(bool enable) override;

    void shear(qreal sh, qreal sv) override;

    void translate(qreal dx, qreal dy) override;

    //color helper
    int registerColor(QString colorString) override;
    void freeColor(int colorId) override;

    int registerFontFamily(QString fontFamily) override;
    void freeFontFamily(int fontFamilyId) override;

    //helper
    QSize getStringSize(int fontFamilyId, int fontSizePx, QString text) override;

    //input method support
    void inputMethodEvent(QInputMethodEvent *e) override;
    QVariant inputMethodQuery(Qt::InputMethodQuery property) const override;

private:
    bool m_isRecording = false;
    std::vector<std::function<void(QPainter*)>> m_paintActions;
    std::vector<std::function<void(QPainter*)>> m_recordedPaintActions;
    QObject* m_paintHandler = nullptr;
    bool m_supportsTextInput;
    bool m_preeditActive;
    QString m_preeditText;

    std::map<int, QColor> m_colorMap;
    std::map<int, QString> m_fontFamilyMap;

    QMutex m_paintActionMutex;
    QMutex m_recordActionMutex;

    void checkRecordingAndAdd(std::function<void(QPainter*)> action);
    static void setPaintedItemToHandler(QObject* handler, QmlNetRecordingPaintedItem* paintedItemPtr);
};

#endif // QMLNETRECORDINGPAINTEDITEM_H
