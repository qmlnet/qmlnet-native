#include "INetQPainter.h"

extern "C" {

Q_DECL_EXPORT void inetqpainter_setPen(INetQPainter* painter, int colorId) {
    painter->setPen(colorId);
}

Q_DECL_EXPORT void inetqpainter_resetPen(INetQPainter* painter) {
    painter->resetPen();
}

Q_DECL_EXPORT void inetqpainter_setBrush(INetQPainter* painter, int colorId) {
    painter->setBrush(colorId);
}

Q_DECL_EXPORT void inetqpainter_resetBrush(INetQPainter* painter) {
    painter->resetBrush();
}

Q_DECL_EXPORT void inetqpainter_setFont(INetQPainter* painter, int fontFamilyId, bool isBold, bool isItalic, bool isUnderline, int pxSize) {
    painter->setFont(fontFamilyId, isBold, isItalic, isUnderline, pxSize);
}

Q_DECL_EXPORT void inetqpainter_setFontFamily(INetQPainter* painter, int fontFamilyId) {
    painter->setFontFamily(fontFamilyId);
}

Q_DECL_EXPORT void inetqpainter_setFontBold(INetQPainter* painter, bool isBold) {
    painter->setFontBold(isBold);
}

Q_DECL_EXPORT void inetqpainter_setFontItalic(INetQPainter* painter, bool isItalic) {
    painter->setFontItalic(isItalic);
}

Q_DECL_EXPORT void inetqpainter_setFontUnderline(INetQPainter* painter, bool isUnderline) {
    painter->setFontUnderline(isUnderline);
}

Q_DECL_EXPORT void inetqpainter_setFontSize(INetQPainter* painter, int pxSize) {
    painter->setFontSize(pxSize);
}

Q_DECL_EXPORT void inetqpainter_drawText(INetQPainter* painter, int x, int y, QChar* text) {
    painter->drawText(x, y, QString(text));
}

Q_DECL_EXPORT void inetqpainter_drawTextRect(INetQPainter* painter, int x, int y, int width, int height, int flags, QChar* text) {
    painter->drawText(x, y, width, height, flags, QString(text));
}

Q_DECL_EXPORT void inetqpainter_drawRect(INetQPainter* painter, int x, int y, int width, int height) {
    painter->drawRect(x, y, width, height);
}

Q_DECL_EXPORT void inetqpainter_fillRectColor(INetQPainter* painter, int x, int y, int width, int height, int colorId) {
    painter->fillRect(x, y, width, height, colorId);
}

Q_DECL_EXPORT void inetqpainter_fillRect(INetQPainter* painter, int x, int y, int width, int height) {
    painter->fillRect(x, y, width, height);
}

Q_DECL_EXPORT int inetqpainter_registerColor(INetQPainter* painter, QChar* colorString) {
    return painter->registerColor(QString(colorString));
}

Q_DECL_EXPORT void inetqpainter_freeColor(INetQPainter* painter, int colorId) {
    painter->freeColor(colorId);
}

Q_DECL_EXPORT int inetqpainter_registerFontFamily(INetQPainter* painter, QChar* fontFamilyString) {
    return painter->registerFontFamily(QString(fontFamilyString));
}

Q_DECL_EXPORT void inetqpainter_freeFontFamily(INetQPainter* painter, int fontId) {
    painter->freeFontFamily(fontId);
}

struct StringSizeResult {
    int width;
    int height;
};

Q_DECL_EXPORT StringSizeResult inetqpainter_getStringSize(INetQPainter* painter, int fontFamilyId, int fontSizePx, QChar* text) {
    auto size = painter->getStringSize(fontFamilyId, fontSizePx, QString(text));
    StringSizeResult result;
    result.width = size.width();
    result.height = size.height();
    return result;
}

}
