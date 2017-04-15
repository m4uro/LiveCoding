#include <QGuiApplication>
#include <QQuickView>
#include <QUrl>
#include <QQmlEngine>

#include "filewatcher.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQuickView view;

    const QDir DIRECTORY("D:/Dev/qt projects/LiveCoding");
    const QUrl SOURCE_URL = QUrl::fromLocalFile(DIRECTORY.filePath("main.qml"));

    view.setSource(SOURCE_URL);
    view.setWidth(600);
    view.setHeight(400);
    view.show();

    FileWatcher watcher([&view, SOURCE_URL](){
        view.engine()->clearComponentCache();
        view.setSource(SOURCE_URL);
    });

    watcher.setDirectory(DIRECTORY.absolutePath());

    return app.exec();
}
