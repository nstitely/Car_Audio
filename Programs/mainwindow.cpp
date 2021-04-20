#include "mainwindow.h"
#include "brightness.h"
#include "Volume/volumecontroller.h"
#include "MusicPlayer/musicplayer.h"

#include <QTime>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , time(new QLabel)
    , volume(new VolumeController)
    , player(new MusicPlayer)
    , bright(new Brightness)
{
    grid.addWidget(             bright, 0, 0, 2, 1);
    grid.addItem(new QSpacerItem(25,0), 0, 1, 2, 1);
    grid.addWidget(             player, 0, 2, 2, 1);
    grid.addItem(new QSpacerItem(25,0), 0, 3, 2, 1);
    grid.addWidget(               time, 0, 4, 1, 1);
    grid.addWidget(             volume, 1, 4, 1, 1);

    grid.setMargin(50);

    startTimer(100, Qt::PreciseTimer);

    setCentralWidget(new QWidget);
    centralWidget()->setLayout(&grid);

    QFont f = QApplication::font();
    f.setPointSize(48);
    time->setFont(f);

    bright->setValue(100);

    connect(volume, &VolumeController::setEqualizer, this, &MainWindow::getEqualizer);
}

void MainWindow::timerEvent(QTimerEvent *)
{
    time->setText(QTime::currentTime().toString("H:mm:ss"));
}

void MainWindow::getEqualizer()
{
    // TODO: Add a custom QDialog which returns a 0 - 100% for bass, treble , and balance
    // TODO: Send the balance to the volume object, and the bass/treble to the music player.
}
