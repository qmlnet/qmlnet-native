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


Q_DECL_EXPORT void inetqpainter_drawArc(INetQPainter* painter, int x, int y, int width, int height, int startAngle, int spanAngle) {
    painter->drawArc(x, y, width, height, startAngle, spanAngle);
}

Q_DECL_EXPORT void inetqpainter_drawChord(INetQPainter* painter, int x, int y, int width, int height, int startAngle, int spanAngle) {
    painter->drawChord(x, y, width, height, startAngle, spanAngle);
}

struct INetQPainter_Point {
    int x;
    int y;
};

struct INetQPainter_Rect {
    int x;
    int y;
    int width;
    int height;
};

Q_DECL_EXPORT void inetqpainter_drawConvexPolygon(INetQPainter* painter, INetQPainter_Point* points, int pointCount) {
    std::vector<QPoint> pointVector(pointCount);
    for(int i=0; i<pointCount; i++) {
        pointVector.push_back(QPoint(points[i].x, points[i].y));
    }
    painter->drawConvexPolygon(&pointVector[0], pointVector.size());
}

Q_DECL_EXPORT void inetqpainter_drawEllipse(INetQPainter* painter, int x, int y, int width, int height) {
    painter->drawEllipse(x, y, width, height);
}

Q_DECL_EXPORT void inetqpainter_drawImage(INetQPainter* painter, INetQPainter_Point point, uchar* imgData, int imgDataSize, INetQPainter_Rect sourceRect, int flags) {
    QImage img;
    img.loadFromData(imgData, imgDataSize);
    QPoint p(point.x, point.y);
    QRect sr(sourceRect.x, sourceRect.y, sourceRect.width, sourceRect.height);

    painter->drawImage(p, img, sr, (Qt::ImageConversionFlags)flags);
}

Q_DECL_EXPORT void inetqpainter_drawLine(INetQPainter* painter, int x1, int y1, int x2, int y2) {
    painter->drawLine(x1, y1, x2, y2);
}

//void drawPath(const QPainterPath &path) override;
//void fillPath(const QPainterPath &path, int colorId) override;
//void strokePath(const QPainterPath &path, int colorId) override;

Q_DECL_EXPORT void inetqpainter_drawPie(INetQPainter* painter, int x, int y, int width, int height, int startAngle, int spanAngle) {
    painter->drawPie(x, y, width, height, startAngle, spanAngle);
}

Q_DECL_EXPORT void inetqpainter_drawPoint(INetQPainter* painter, int x, int y) {
    painter->drawPoint(x, y);
}

Q_DECL_EXPORT void inetqpainter_drawPolygon(INetQPainter* painter, INetQPainter_Point* points, int pointCount, bool oddFill) {
    std::vector<QPoint> pointVector(pointCount);
    for(int i=0; i<pointCount; i++) {
        pointVector.push_back(QPoint(points[i].x, points[i].y));
    }

    Qt::FillRule fillRule = oddFill ? Qt::FillRule::OddEvenFill : Qt::FillRule::WindingFill;
    painter->drawPolygon(&pointVector[0], pointVector.size(), fillRule);
}

Q_DECL_EXPORT void inetqpainter_drawPolyline(INetQPainter* painter, INetQPainter_Point* points, int pointCount) {
    std::vector<QPoint> pointVector(pointCount);
    for(int i=0; i<pointCount; i++) {
        pointVector.push_back(QPoint(points[i].x, points[i].y));
    }

    painter->drawPolyline(&pointVector[0], pointVector.size());
}

Q_DECL_EXPORT void inetqpainter_drawRoundedRect(INetQPainter* painter, int x, int y, int w, int h, qreal xRadius, qreal yRadius, bool absoluteSize) {
    painter->drawRoundedRect(x, y, w, h, xRadius, yRadius, absoluteSize ? Qt::SizeMode::AbsoluteSize : Qt::SizeMode::RelativeSize);
}

Q_DECL_EXPORT void inetqpainter_eraseRect(INetQPainter* painter, int x, int y, int width, int height) {
    painter->eraseRect(x, y, width, height);
}

Q_DECL_EXPORT void inetqpainter_setBackground(INetQPainter* painter, int colorId) {
    painter->setBackground(colorId);
}

Q_DECL_EXPORT void inetqpainter_setBackgroundMode(INetQPainter* painter, bool opaque) {
    painter->setBackgroundMode(opaque ? Qt::BGMode::OpaqueMode : Qt::BGMode::TransparentMode);
}

//void setClipPath(const QPainterPath &path, Qt::ClipOperation operation = Qt::ReplaceClip) override;

enum INetQPainter_ClipOperation {
    NoClip = 1,
    ReplaceClip,
    IntersectClip
};

Q_DECL_EXPORT void inetqpainter_setClipRect(INetQPainter* painter, int x, int y, int width, int height, INetQPainter_ClipOperation operation) {
    Qt::ClipOperation cop = Qt::ClipOperation::NoClip;
    switch(operation) {
    case INetQPainter_ClipOperation::NoClip:
        cop = Qt::ClipOperation::NoClip;
        break;
    case INetQPainter_ClipOperation::ReplaceClip:
        cop = Qt::ClipOperation::ReplaceClip;
        break;
    case INetQPainter_ClipOperation::IntersectClip:
        cop = Qt::ClipOperation::IntersectClip;
        break;
    }

    painter->setClipRect(x, y, width, height, cop);
}

Q_DECL_EXPORT void inetqpainter_setClipping(INetQPainter* painter, bool enable) {
    painter->setClipping(enable);
}

enum INetQPainter_CompositionMode {
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

Q_DECL_EXPORT void inetqpainter_setCompositionMode(INetQPainter* painter, INetQPainter_CompositionMode mode) {
    QPainter::CompositionMode cmode;
    switch(mode)
    {
    case INetQPainter_CompositionMode::CompositionMode_SourceOver:
        cmode = QPainter::CompositionMode::CompositionMode_SourceOver;
        break;
    case INetQPainter_CompositionMode::CompositionMode_DestinationOver:
        cmode = QPainter::CompositionMode::CompositionMode_DestinationOver;
        break;
    case INetQPainter_CompositionMode::CompositionMode_Clear:
        cmode = QPainter::CompositionMode::CompositionMode_Clear;
        break;
    case INetQPainter_CompositionMode::CompositionMode_Source:
        cmode = QPainter::CompositionMode::CompositionMode_Source;
        break;
    case INetQPainter_CompositionMode::CompositionMode_Destination:
        cmode = QPainter::CompositionMode::CompositionMode_Destination;
        break;
    case INetQPainter_CompositionMode::CompositionMode_SourceIn:
        cmode = QPainter::CompositionMode::CompositionMode_SourceIn;
        break;
    case INetQPainter_CompositionMode::CompositionMode_DestinationIn:
        cmode = QPainter::CompositionMode::CompositionMode_DestinationIn;
        break;
    case INetQPainter_CompositionMode::CompositionMode_SourceOut:
        cmode = QPainter::CompositionMode::CompositionMode_SourceOut;
        break;
    case INetQPainter_CompositionMode::CompositionMode_DestinationOut:
        cmode = QPainter::CompositionMode::CompositionMode_DestinationOut;
        break;
    case INetQPainter_CompositionMode::CompositionMode_SourceAtop:
        cmode = QPainter::CompositionMode::CompositionMode_SourceAtop;
        break;
    case INetQPainter_CompositionMode::CompositionMode_DestinationAtop:
        cmode = QPainter::CompositionMode::CompositionMode_DestinationAtop;
        break;
    case INetQPainter_CompositionMode::CompositionMode_Xor:
        cmode = QPainter::CompositionMode::CompositionMode_Xor;
        break;
    case INetQPainter_CompositionMode::CompositionMode_Plus:
        cmode = QPainter::CompositionMode::CompositionMode_Plus;
        break;
    case INetQPainter_CompositionMode::CompositionMode_Multiply:
        cmode = QPainter::CompositionMode::CompositionMode_Multiply;
        break;
    case INetQPainter_CompositionMode::CompositionMode_Screen:
        cmode = QPainter::CompositionMode::CompositionMode_Screen;
        break;
    case INetQPainter_CompositionMode::CompositionMode_Overlay:
        cmode = QPainter::CompositionMode::CompositionMode_Overlay;
        break;
    case INetQPainter_CompositionMode::CompositionMode_Darken:
        cmode = QPainter::CompositionMode::CompositionMode_Darken;
        break;
    case INetQPainter_CompositionMode::CompositionMode_Lighten:
        cmode = QPainter::CompositionMode::CompositionMode_Lighten;
        break;
    case INetQPainter_CompositionMode::CompositionMode_ColorDodge:
        cmode = QPainter::CompositionMode::CompositionMode_ColorDodge;
        break;
    case INetQPainter_CompositionMode::CompositionMode_ColorBurn:
        cmode = QPainter::CompositionMode::CompositionMode_ColorBurn;
        break;
    case INetQPainter_CompositionMode::CompositionMode_HardLight:
        cmode = QPainter::CompositionMode::CompositionMode_HardLight;
        break;
    case INetQPainter_CompositionMode::CompositionMode_SoftLight:
        cmode = QPainter::CompositionMode::CompositionMode_SoftLight;
        break;
    case INetQPainter_CompositionMode::CompositionMode_Difference:
        cmode = QPainter::CompositionMode::CompositionMode_Difference;
        break;
    case INetQPainter_CompositionMode::CompositionMode_Exclusion:
        cmode = QPainter::CompositionMode::CompositionMode_Exclusion;
        break;
    case INetQPainter_CompositionMode::RasterOp_SourceOrDestination:
        cmode = QPainter::CompositionMode::RasterOp_SourceOrDestination;
        break;
    case INetQPainter_CompositionMode::RasterOp_SourceAndDestination:
        cmode = QPainter::CompositionMode::RasterOp_SourceAndDestination;
        break;
    case INetQPainter_CompositionMode::RasterOp_SourceXorDestination:
        cmode = QPainter::CompositionMode::RasterOp_SourceXorDestination;
        break;
    case INetQPainter_CompositionMode::RasterOp_NotSourceAndNotDestination:
        cmode = QPainter::CompositionMode::RasterOp_NotSourceAndNotDestination;
        break;
    case INetQPainter_CompositionMode::RasterOp_NotSourceOrNotDestination:
        cmode = QPainter::CompositionMode::RasterOp_NotSourceOrNotDestination;
        break;
    case INetQPainter_CompositionMode::RasterOp_NotSourceXorDestination:
        cmode = QPainter::CompositionMode::RasterOp_NotSourceXorDestination;
        break;
    case INetQPainter_CompositionMode::RasterOp_NotSource:
        cmode = QPainter::CompositionMode::RasterOp_NotSource;
        break;
    case INetQPainter_CompositionMode::RasterOp_NotSourceAndDestination:
        cmode = QPainter::CompositionMode::RasterOp_NotSourceAndDestination;
        break;
    case INetQPainter_CompositionMode::RasterOp_SourceAndNotDestination:
        cmode = QPainter::CompositionMode::RasterOp_SourceAndNotDestination;
        break;
    case INetQPainter_CompositionMode::RasterOp_NotSourceOrDestination:
        cmode = QPainter::CompositionMode::RasterOp_NotSourceOrDestination;
        break;
    case INetQPainter_CompositionMode::RasterOp_SourceOrNotDestination:
        cmode = QPainter::CompositionMode::RasterOp_SourceOrNotDestination;
        break;
    case INetQPainter_CompositionMode::RasterOp_ClearDestination:
        cmode = QPainter::CompositionMode::RasterOp_ClearDestination;
        break;
    case INetQPainter_CompositionMode::RasterOp_SetDestination:
        cmode = QPainter::CompositionMode::RasterOp_SetDestination;
        break;
    case INetQPainter_CompositionMode::RasterOp_NotDestination:
        cmode = QPainter::CompositionMode::RasterOp_NotDestination;
        break;
    }

    painter->setCompositionMode(cmode);
}

enum INetQPainter_LayoutDirection {
    LeftToRight = 1,
    RightToLeft,
    LayoutDirectionAuto
};


Q_DECL_EXPORT void inetqpainter_setLayoutDirection(INetQPainter* painter, INetQPainter_LayoutDirection dir) {
    Qt::LayoutDirection lDir = Qt::LayoutDirection::LeftToRight;
    switch(dir)
    {
    case INetQPainter_LayoutDirection::LeftToRight:
        lDir = Qt::LayoutDirection::LeftToRight;
        break;
    case INetQPainter_LayoutDirection::RightToLeft:
        lDir = Qt::LayoutDirection::RightToLeft;
        break;
    case INetQPainter_LayoutDirection::LayoutDirectionAuto:
        lDir = Qt::LayoutDirection::LayoutDirectionAuto;
        break;
    }

    painter->setLayoutDirection(lDir);
}

Q_DECL_EXPORT void inetqpainter_setOpacity(INetQPainter* painter, double opacity) {
    painter->setOpacity(opacity);
}

Q_DECL_EXPORT void inetqpainter_setRenderHint(INetQPainter* painter, QPainter::RenderHint hint, bool on) {
    painter->setRenderHint(hint, on);
}

Q_DECL_EXPORT void inetqpainter_setTransform(INetQPainter* painter, double h11, double h12, double h13, double h21, double h22, double h23, double h31, double h32, double h33, bool combine) {
    QTransform transform(h11, h12, h13, h21, h22, h23, h31, h32, h33);
    painter->setTransform(transform, combine);
}

Q_DECL_EXPORT void inetqpainter_setViewTransformEnabled(INetQPainter* painter, bool enabled) {
    painter->setViewTransformEnabled(enabled);
}

Q_DECL_EXPORT void inetqpainter_setWorldTransform(INetQPainter* painter, double h11, double h12, double h13, double h21, double h22, double h23, double h31, double h32, double h33, bool combine) {
    QTransform transform(h11, h12, h13, h21, h22, h23, h31, h32, h33);
    painter->setWorldTransform(transform, combine);
}

Q_DECL_EXPORT void inetqpainter_setWorldMatrixEnabled(INetQPainter* painter, bool enabled) {
    painter->setWorldMatrixEnabled(enabled);
}

Q_DECL_EXPORT void inetqpainter_shear(INetQPainter* painter, double sh, double sv) {
    painter->shear(sh, sv);
}

Q_DECL_EXPORT void inetqpainter_translate(INetQPainter* painter, double dx, double dy) {
    painter->translate(dx, dy);
}

}
