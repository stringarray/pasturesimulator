#include "mainwindow.h"

#include <QApplication>
#include <QTimer>
#include <QTime>


int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(resources);
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));

    QApplication app(argc, argv);
    app.setAttribute(Qt::AA_DontCreateNativeWidgetSiblings);

    MainWindow window;
    window.show();



    return app.exec();
}
