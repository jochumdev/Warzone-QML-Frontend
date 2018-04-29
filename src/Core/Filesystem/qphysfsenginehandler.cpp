#include "Core/Filesystem/qphysfsenginehandler.h"
#include "Core/Filesystem/file.h"
// #include <cstdio>

namespace FileSystem {

QPhysfsFileEngine::QPhysfsFileEngine(const QString& filename)
    : _handler(NULL)
    , _flags(0)
{
    setFileName(filename);
}

QPhysfsFileEngine::~QPhysfsFileEngine()
{
    close();
}

bool QPhysfsFileEngine::open(QIODevice::OpenMode openMode)
{
    close();

    // fprintf(stderr, qPrintable(_filename + "\n" + PHYSFS_getRealDir(_filename.toUtf8().constData()) +"\n"));

    if ((openMode & QIODevice::WriteOnly) ||
            (openMode & QIODevice::ReadWrite && !PHYSFS_exists(_filename.toUtf8().constData()))) {
        _handler = PHYSFS_openWrite(_filename.toUtf8().constData());
        _flags = QAbstractFileEngine::WriteOwnerPerm | QAbstractFileEngine::WriteUserPerm | QAbstractFileEngine::FileType;
    }

    else if (openMode & QIODevice::ReadOnly) {
        _handler = PHYSFS_openRead(_filename.toUtf8().constData());
    }

    else if (openMode & QIODevice::Append) {
        _handler = PHYSFS_openAppend(_filename.toUtf8().constData());
    }

    else {
        qWarning("Bad file open mode: %d", (int)openMode);
    }

    if (!_handler) {
        qWarning("Failed to open %s, reason: %s", _filename.toUtf8().constData(), WZ_PHYSFS_getLastError());
        return false;
    }

    return true;
}

bool QPhysfsFileEngine::close()
{
    if (isOpened()) {
        int result = PHYSFS_close(_handler);
        _handler = NULL;
        return result != 0;
    }

    return true;
}

bool QPhysfsFileEngine::flush()
{
    return PHYSFS_flush(_handler) != 0;
}

qint64 QPhysfsFileEngine::size() const
{
    return _size;
}

qint64 QPhysfsFileEngine::pos() const
{
    return PHYSFS_tell(_handler);
}

bool QPhysfsFileEngine::seek(qint64 pos)
{
    return PHYSFS_seek(_handler, pos) != 0;
}

bool QPhysfsFileEngine::isSequential() const
{
    return true;
}

bool QPhysfsFileEngine::remove()
{
    return PHYSFS_delete(_filename.toUtf8().constData()) != 0;
}

bool QPhysfsFileEngine::mkdir(const QString &dirName, bool createParentDirectories) const
{
    Q_UNUSED(createParentDirectories);
    return PHYSFS_mkdir(dirName.toUtf8().constData()) != 0;
}

bool QPhysfsFileEngine::rmdir(const QString &dirName, bool recurseParentDirectories) const
{
    Q_UNUSED(recurseParentDirectories);
    return PHYSFS_delete(dirName.toUtf8().constData()) != 0;
}

bool QPhysfsFileEngine::caseSensitive() const
{
    return true;
}

bool QPhysfsFileEngine::isRelativePath() const
{
    return true;
}

QStringList QPhysfsFileEngine::entryList(QDir::Filters filters, const QStringList &filterNames) const
{
    QString file;
    QStringList result;
    char **files = PHYSFS_enumerateFiles("");

    for (char **i = files; *i != NULL; i++) {
        file = QString::fromLatin1(*i);
        if (QDir::match(filterNames, file)) {
            result << file;
        }
    }

    PHYSFS_freeList(files);
    return result;
}

QAbstractFileEngine::FileFlags QPhysfsFileEngine::fileFlags(FileFlags type) const
{
    return type & _flags;
}

QString QPhysfsFileEngine::fileName(FileName file) const
{
    // fprintf(stderr, qPrintable(QString("%1: file is: %2\n").arg(_filename).arg(file)));

    switch(file)
    {
    case DefaultName:
    case AbsoluteName:
    case CanonicalName:
        return QPhysfsEngineHandler::scheme + _filename;
        break;

    case BaseName:
        return _filename.right(_filename.lastIndexOf("/"));
        break;

    case PathName:
    case AbsolutePathName:
    case CanonicalPathName:
        return QPhysfsEngineHandler::scheme + _filename.left(_filename.lastIndexOf("/"));
        break;

    default:
        return "";
    }
}

QDateTime QPhysfsFileEngine::fileTime(FileTime time) const
{
    switch (time)
    {
    case QAbstractFileEngine::ModificationTime:
    default:
        return _datetime;
        break;
    };
}

void QPhysfsFileEngine::setFileName(const QString &file)
{
    _filename = file;

    PHYSFS_Stat stat;
    if (PHYSFS_stat(_filename.toUtf8().constData(), &stat) != 0) {
        // Show potential until actually opened
        _flags = QAbstractFileEngine::ExistsFlag |
                QAbstractFileEngine::ReadOtherPerm |
                QAbstractFileEngine::ReadOwnerPerm |
                QAbstractFileEngine::ReadUserPerm;

        _size = stat.filesize;
        _datetime = QDateTime::fromTime_t(stat.modtime);

        switch (stat.filetype)
        {
        case PHYSFS_FILETYPE_REGULAR:
            _flags |= QAbstractFileEngine::FileType;
            break;

        case PHYSFS_FILETYPE_DIRECTORY:
            _flags |= QAbstractFileEngine::DirectoryType;
            break;
        case PHYSFS_FILETYPE_SYMLINK:
            _flags |= QAbstractFileEngine::LinkType;
            break;
        };
    }
}

bool QPhysfsFileEngine::atEnd() const
{
    return PHYSFS_eof(_handler) != 0;
}

qint64 QPhysfsFileEngine::read(char *data, qint64 maxlen)
{
    return WZ_PHYSFS_readBytes(_handler, data, (quint32)maxlen);
}

qint64 QPhysfsFileEngine::readLine(char *data, qint64 maxlen)
{
    // TODO
}

qint64 QPhysfsFileEngine::write(const char *data, qint64 len)
{
    return WZ_PHYSFS_writeBytes(_handler, data, (quint32)len);
}

bool QPhysfsFileEngine::isOpened() const
{
    return _handler != NULL;
}

QFile::FileError QPhysfsFileEngine::error() const
{
    return QFile::UnspecifiedError;
}

QString QPhysfsFileEngine::errorString() const
{
    return WZ_PHYSFS_getLastError();
}

bool QPhysfsFileEngine::supportsExtension(Extension extension) const
{
    return extension == QAbstractFileEngine::AtEndExtension;
}

QAbstractFileEngine* QPhysfsEngineHandler::create(const QString &filename) const
{
    if (filename.startsWith(scheme)) {
        QString newPath = filename;
        return new QPhysfsFileEngine(newPath.remove(0, QString(scheme).size()));
    }

    return NULL;
}


}

