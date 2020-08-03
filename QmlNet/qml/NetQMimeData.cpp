#include "NetQMimeData.h"

extern "C" {

Deleter(QMimeData, qmimedata)
SideEffecter(QMimeData, qmimedata, clear)
// todo: QVariant colorData() const
// todo: QByteArray data(const QString &mimeType) const
// todo: virtual QStringList formats() const
SimpleGetter(QMimeData, qmimedata, hasColor, bool)
// todo: virtual bool hasFormat(const QString &mimeType) const
SimpleGetter(QMimeData, qmimedata, hasHtml, bool)
SimpleGetter(QMimeData, qmimedata, hasImage, bool)
SimpleGetter(QMimeData, qmimedata, hasText, bool)
SimpleGetter(QMimeData, qmimedata, hasUrls, bool)
QStringGetter(QMimeData, qmimedata, html)
// todo: QVariant imageData() const
// todo: void removeFormat(const QString &mimeType)
// todo: void setColorData(const QVariant &color)
// todo: void setData(const QString &mimeType, const QByteArray &data)
// todo: void setHtml(const QString &html)
// todo: void setImageData(const QVariant &image)
// todo: void setText(const QString &text)
// todo: void setUrls(const QList<QUrl> &urls)
QStringGetter(QMimeData, qmimedata, text)
// todo: QList<QUrl> urls() const

}