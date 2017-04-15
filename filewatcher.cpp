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

    // @todo: remove. Testing the callback function
    mCallback();
}
