#include "filewatcher.h"
#include <QDebug>

/**
 * @brief FileWatcher::FileWatcher
 *   This class can monitor file changes in a directory and calls a callback
 *   in response
 * @param callback
 *   The callback function to be executed whenever changes are detected
 */
FileWatcher::FileWatcher(std::function<void()> callback)
: mCallback(callback)
{
    QObject::connect(&mWatcher, &QFileSystemWatcher::directoryChanged, this, &FileWatcher::directoryChanged);
    QObject::connect(&mWatcher, &QFileSystemWatcher::fileChanged, this, &FileWatcher::fileChanged);
}

/**
 * @brief FileWatcher::setDirectory
 *   Set the directory to watch for changes
 * @param path
 *   Directory path
 */
void FileWatcher::setDirectory(const QString &path)
{
    qDebug() << "setting directory to: " << path;

    if (!mWatcher.addPath(path))
    {
        qWarning() << "Could not add path: " << path;
    }

    // @todo start timer
}

void FileWatcher::directoryChanged(const QString &path)
{
    qDebug() << "FileWatcher::directoryChanged: " << path;
}

void FileWatcher::fileChanged(const QString &path)
{
    qDebug() << "FileWatcher::fileChanged: " << path;
}
