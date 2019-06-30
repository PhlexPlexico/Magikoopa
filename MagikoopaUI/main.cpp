#include "mainwindow.h"
#include <QApplication>
#include <QCommandLineParser>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCommandLineParser parser;
    parser.addHelpOption();
    QCommandLineOption workDirOption("workdir", QCoreApplication::translate("main", "[Build] Set working directory"), "workdir");
    parser.addOption(workDirOption);
    QCommandLineOption buildOption("build", QCoreApplication::translate("main", "[Build] Build in CLI mode"));
    parser.addOption(buildOption);

    parser.process(a);

    MainWindow w;
    const QString workDir = parser.value(workDirOption);
    if (parser.isSet(buildOption) && !workDir.isEmpty()) {
        w.setWorkingDirectory(workDir);
        w.build();
        QObject::connect(&w, &MainWindow::on_finished, [&a] {
            a.quit();
        });
    } else {
        w.loadLastWorkingDirectory();
        w.show();
    }
    return a.exec();
}
