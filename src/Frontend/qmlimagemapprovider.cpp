#include "qmlimagemapprovider.h"

#include <lib/Imagemap/loader.h>

#include <QtGui/QPixmap>
#include <QtCore/QFile>
#include <QtCore/QFileInfo>
#include <QtCore/QDebug>

QPixmap QMLImagemapProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
    QStringList path = id.split(':');

    QPixmap image;
    if (path.count() == 2 && path[1].toLower() == "width")
    {
        image = Imagemap::Loader::instance().pixmap(path[1], requestedSize, Imagemap::ResizeToWith);
    }
    else if (path.count() == 2 && path[1].toLower() == "height")
    {
        image = Imagemap::Loader::instance().pixmap(path[0], requestedSize, Imagemap::ResizeToHeight);
    }
    else
    {
        image = Imagemap::Loader::instance().pixmap(path[0], requestedSize);
    }
    *size = image.size();

    return image;
}

void QMLImagemapProvider::setBasePath(const QString &basepath)
{
    m_basepath = basepath;
}