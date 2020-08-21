#ifndef NETQPAINTER_H
#define NETQPAINTER_H

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

    //color management
    virtual int registerColor(QString colorString) = 0;
    virtual void freeColor(int colorId) = 0;

    //font management
    virtual int registerFontFamily(QString fontFamilyName) = 0;
    virtual void freeFontFamily(int fontId) = 0;

    virtual QSize getStringSize(int fontFamilyId, int fontSizePx, QString text) = 0;
};

#endif // NETQPAINTER_H
