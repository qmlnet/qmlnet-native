#ifndef QMLNETPAINTEDITEM_H
#define QMLNETPAINTEDITEM_H

#include <QtQuick/QQuickPaintedItem>
#include <QObject>
#include <vector>
#include <map>


class QmlNetPaintedItem : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QObject* paintHandler READ paintHandler WRITE setPaintHandler)
    Q_PROPERTY(bool supportsTextInput READ supportsTextInput WRITE setSupportsTextInput)
    Q_PROPERTY(bool preeditActive READ preeditActive NOTIFY preeditActiveChanged)
    Q_PROPERTY(QString preeditText READ preeditText NOTIFY preeditTextChanged)
    QML_ELEMENT
public:
    QmlNetPaintedItem(QQuickItem *parent = nullptr);

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
    void setPen(int colorId);
    void resetPen();
    void setBrush(int colorId);
    void resetBrush();
    void setFont(QString fontFamilyName, bool isBold, bool isItalic, bool isUnderline, int pxSize);
    void setFontFamily(QString fontFamilyName);
    void setFontBold(bool isBold);
    void setFontItalic(bool isItalic);
    void setFontUnderline(bool isUnderline);
    void setFontSize(int pxSize);
    void drawText(int x, int y, QString text);
    void drawText(int x, int y, int width, int height, QString text);
    void drawRect(int x, int y, int width, int height);
    void fillRect(int x, int y, int width, int height, int colorId);
    void fillRect(int x, int y, int width, int height);

    //color helper
    int createColor(QString colorString);
    void freeColor(int colorId);

    //helper
    QSize getStringSize(QString fontFamilyName, int fontSizePx, QString text);

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

    QMutex m_paintActionMutex;

    void checkRecordingAndAdd(std::function<void(QPainter*)> action);
};

#endif // QMLNETPAINTEDITEM_H
