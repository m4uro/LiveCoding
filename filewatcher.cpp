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

    // configure the timer to signal the changes to the callback
    mTimer.setInterval(100);
    mTimer.setSingleShot(true);

    // configure directory filters
    mDir.setFilter(QDir::Files | QDir::NoSymLinks);
    mDir.setNameFilters(QStringList() << "*.qml");

    // connect timer to callback function
    QObject::connect(&mTimer, &QTimer::timeout, mCallback);
}

void FileWatcher::addPaths()
{
    QStringList entries = mDir.entryList();
    for (int i=0; i<entries.size(); i++)
    {
        entries[i].prepend(mDir.absolutePath() + "/");
    }

    mWatcher.addPaths(entries);
    mTimer.start();
}

/**
 * @brief FileWatcher::setDirectory
 *   Set the directory to watch for changes
 * @param path
 *   Directory path
 */
void FileWatcher::setDirectory(const QString &path)
{
    if (!mWatcher.addPath(path))
    {
        qWarning() << "Could not add path: " << path;
    }
    else
    {
        mDir.setPath(path);
        addPaths();
    }
}

void FileWatcher::directoryChanged(const QString &path)
{
    addPaths();
}

void FileWatcher::fileChanged(const QString &path)
{
    mTimer.start();
}
