#ifndef QMLNETPAINTEDITEM_H
#define QMLNETPAINTEDITEM_H

#include <QtQuick/QQuickPaintedItem>
#include <QObject>
#include <vector>


class QmlNetPaintedItem : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QObject* paintHandler READ paintHandler WRITE setPaintHandler)
    QML_ELEMENT
public:
    QmlNetPaintedItem(QQuickItem *parent = nullptr);

    QObject* paintHandler() const;
    void setPaintHandler(QObject* paintHandler);

    void paint(QPainter *painter) override;

    void beginRecordPaintActions();
    void endRecordPaintActions();

    //Record api
    void setPen(QString color);
    void resetPen();
    void setBrush(QString color);
    void resetBrush();
    void setFont(QString fontFamilyName, bool isBold, bool isItalic, bool isUnderline, int pxSize);
    void drawText(int x, int y, QString text);
    void drawRect(int x, int y, int width, int height);
    void fillRect(int x, int y, int width, int height, QString color);
    void fillRect(int x, int y, int width, int height);

private:
    bool m_isRecording = false;
    std::vector<std::function<void(QPainter*)>> m_paintActions;
    std::vector<std::function<void(QPainter*)>> m_recordedPaintActions;
    QObject* m_paintHandler = nullptr;

    QMutex m_paintActionMutex;

    void checkRecordingAndAdd(std::function<void(QPainter*)> action);
};

#endif // QMLNETPAINTEDITEM_H
