#ifndef FRONTEND_IMAGEPROVIDER_H
#define FRONTEND_IMAGEPROVIDER_H

#include <QtCore/QHash>
#include <QtDeclarative/QDeclarativeImageProvider>

namespace Imagemap {
    class Map;
}
class QPixmap;

namespace Frontend {

class QMLImagemapProvider : public QDeclarativeImageProvider
{
public:
    QMLImagemapProvider()
        : QDeclarativeImageProvider(QDeclarativeImageProvider::Pixmap)
    {
    }

    QPixmap requestPixmap(const QString &id,
                          QSize *size,
                          const QSize &requestedSize);

private:
    QHash<QString, Imagemap::Map*> m_maps;
    QString m_basepath;
};

} // namespace Frontend

#endif // #ifndef FRONTEND_IMAGEPROVIDER_H