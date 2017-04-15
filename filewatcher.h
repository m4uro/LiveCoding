#ifndef FILEWATCHER_H
#define FILEWATCHER_H

#include <functional>
#include <QFileSystemWatcher>
#include <QString>
#include <QObject>

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
    std::function<void()> mCallback;
    QFileSystemWatcher    mWatcher;
};

#endif // FILEWATCHER_H
