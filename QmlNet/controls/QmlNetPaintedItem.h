#ifndef QMLNETPAINTEDITEM_H
#define QMLNETPAINTEDITEM_H

#include <QtQuick/QQuickPaintedItem>
#include <QObject>
#include <vector>
#include <map>
#include "INetQPainter.h"


class QmlNetPaintedItem : public QQuickPaintedItem, INetQPainter
{
    Q_OBJECT
    Q_PROPERTY(QObject* paintHandler READ paintHandler WRITE setPaintHandler)
    Q_PROPERTY(bool supportsTextInput READ supportsTextInput WRITE setSupportsTextInput)
    Q_PROPERTY(bool preeditActive READ preeditActive NOTIFY preeditActiveChanged)
    Q_PROPERTY(QString preeditText READ preeditText NOTIFY preeditTextChanged)
    QML_ELEMENT
public:
    QmlNetPaintedItem(QQuickItem *parent = nullptr);
    virtual ~QmlNetPaintedItem();

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

    void checkRecordingAndAdd(std::function<void(QPainter*)> action);
    static void setPaintedItemToHandler(QObject* handler, QmlNetPaintedItem* paintedItemPtr);
};

#endif // QMLNETPAINTEDITEM_H
