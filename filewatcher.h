#ifndef FILEWATCHER_H
#define FILEWATCHER_H

#include <functional>
#include <QFileSystemWatcher>
#include <QObject>
#include <QDir>
#include <QTimer>

class QString;

class FileWatcher : public QObject
{
    Q_OBJECT
public:
    FileWatcher(std::function<void()> callback);

    void setDirectory(const QString &path);

public slots:
    void directoryChanged(const QString &path);
    void fileChanged(const QString &path);

private:
    void addPaths();

private:
    std::function<void()> mCallback;
    QFileSystemWatcher    mWatcher;
    QDir                  mDir;
    QTimer                mTimer;
};

#endif // FILEWATCHER_H
