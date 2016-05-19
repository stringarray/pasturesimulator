#include "mainwindow.h"

#include <QApplication>
#include <QTimer>
#include <QTime>
#include <QtDebug>
#include <QFile>
#include <QTextStream>


void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{

    QDateTime dateTime(QDateTime::currentDateTime());

    QString timeStr(dateTime.toString("yyyy-MM-dd HH:mm:ss"));
   // QString contextString(QString("(%1, %2)").arg(context.file).arg(context.line));

    QFile outFile("file.log");
    outFile.open(QIODevice::WriteOnly | QIODevice::Append);

    QTextStream stream(&outFile);
    stream << timeStr << " " <<  ": " << msg << endl;

}



int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(resources);
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));

//    qInstallMessageHandler(myMessageOutput);

    QApplication app(argc, argv);
    //app.setAttribute(Qt::AA_DontCreateNativeWidgetSiblings);

    MainWindow window;


    return app.exec();
}
