#include <lib/Imagemap/loader.h>

#include <QtCore/QDebug>
#include <QApplication>
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QStringList>
#include <QtGui/QPixmap>

#include <QtGui/QPainter>
#include <QtSvg/QSvgRenderer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QStringList args = QApplication::instance()->arguments();
    args.takeFirst();

    if (args.isEmpty() || args.count() < 3)
    {
        printf("USAGE: extractmap <input-map.js> <factor> <output-directory>.\n");
        return 1;
    }

    QDir dir(QDir::current());
    if (!dir.exists(args[2]))
    {
        if (!dir.mkdir(args[2]))
        {
            qFatal("Failed to create directory %s", qPrintable(args[2]));
        }
    }
    dir.cd(args[2]);

    if (!Imagemap::Loader::instance().addImagemap(args[0]))
    {
        qFatal("%s", qPrintable(Imagemap::Loader::instance().errorString()));
    }

    int factor = QString(args[1]).toInt();
    QStringList imageList = Imagemap::Loader::instance().imageList();
    foreach(QString name, imageList)
    {
        QPixmap pixmap = Imagemap::Loader::instance().pixmap(name, factor);
        qDebug() << name << "size:" << pixmap.size();

        pixmap.save(QString("%1/%2.png").arg(dir.path()).arg(name));
    }

    a.quit();
}
