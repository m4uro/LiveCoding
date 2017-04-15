#ifndef FILEWATCHER_H
#define FILEWATCHER_H

#include <functional>
#include <QString>

class FileWatcher
{
public:
    FileWatcher(std::function<void()> callback);

    void setDirectory(const QString &path);

private:
    std::function<void()> mCallback;
};

#endif // FILEWATCHER_H
