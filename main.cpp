#include <QGuiApplication>
#include <QQuickView>
#include <QUrl>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQuickView view;

    view.setSource(QUrl("qrc:/main.qml"));
    view.setWidth(600);
    view.setHeight(400);
    view.show();

    return app.exec();
}
