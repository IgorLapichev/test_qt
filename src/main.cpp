#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "TestManager.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qmlRegisterType<TestManager>("TestApp", 1, 0, "TypeName");

    QQmlApplicationEngine engine;
    QQmlContext *context = engine.rootContext();

    TestManager testManager;
    context->setContextProperty("testManager", &testManager);

    engine.load(QUrl(QStringLiteral("qrc:/qml/openmedia.qml")));

    return app.exec();
}
