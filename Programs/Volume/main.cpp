#include "volumecontroller.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    VolumeController w;

    w.resize(150, 740);

    w.show();

    return a.exec();
}
