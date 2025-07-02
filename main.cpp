#include "calclogic.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QUrl>
#include <QtQuickControls2>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    CalcLogic calcLogic;

    engine.rootContext()->setContextProperty("calcLogic", &calcLogic);
    engine.load(QUrl(QStringLiteral("qrc:/CalcApp/Main.qml")));

    return app.exec();
}

