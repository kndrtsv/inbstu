#include <QApplication>
#include "painter_window.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    PainterWindow window;
    window.show();
    return app.exec();
}
