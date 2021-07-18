#include <QApplication>
#include "logviewer.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    LogViewer w;
    w.show();

    return app.exec();
}
