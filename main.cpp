#include <QGuiApplication>
#include <QQuickView>
#include <QUrl>

#include <QDebug>
#include "filewatcher.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQuickView view;

    view.setSource(QUrl("qrc:/main.qml"));
    view.setWidth(600);
    view.setHeight(400);
    view.show();

    FileWatcher watcher([](){ qDebug() << "executing callback function";});
    watcher.setDirectory("some/directory/path");

    return app.exec();
}
