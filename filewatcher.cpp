#include "filewatcher.h"
#include <QDebug>
#include <iostream>

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

    QObject::connect(&mTimer, &QTimer::timeout, mCallback);
}

namespace {
    void ListDirectory(const QString &path)
    {
       QDir dir(path);
       dir.setFilter(QDir::Files | QDir::NoSymLinks);

       QFileInfoList list = dir.entryInfoList();
       std::cout << "     Bytes Filename" << std::endl;
       for (int i = 0; i < list.size(); ++i) {
           QFileInfo fileInfo = list.at(i);
           std::cout << qPrintable(QString("%1 %2").arg(fileInfo.size(), 10)
                                                   .arg(fileInfo.fileName()));
           std::cout << std::endl;
       }
    }
}

void FileWatcher::addPaths()
{
    QStringList entries = mDir.entryList(QDir::Files | QDir::NoSymLinks);
    for (int i=0; i<entries.size(); i++)
    {
        entries[i].prepend(mDir.absolutePath() + "/");
    }

    qDebug() << "Adding paths: " << entries;
    QStringList not_watched = mWatcher.addPaths(entries);

    if (!not_watched.empty())
    {
        qWarning() << "Warning - These files could not be watched: " << not_watched;
    }

    qDebug() << "files being watched: " << mWatcher.files();

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
    qDebug() << "setting directory to: " << path;

    if (!mWatcher.addPath(path))
    {
        qWarning() << "Could not add path: " << path;
    }
    else
    {
        ListDirectory(path);
        mDir.setCurrent(path);
        // add paths for each file to the watcher
        addPaths();
    }
}

void FileWatcher::directoryChanged(const QString &path)
{
    qDebug() << "FileWatcher::directoryChanged: " << path;

    // add paths for each file to the watcher
    addPaths();
}

void FileWatcher::fileChanged(const QString &path)
{
    qDebug() << "FileWatcher::fileChanged: " << path;
    qDebug() << "files being watched: " << mWatcher.files();
    mTimer.start();
}
