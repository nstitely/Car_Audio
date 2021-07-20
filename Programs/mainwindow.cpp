#include "mainwindow.h"
#include "brightness.h"
#include "Volume/volumecontroller.h"
#include "MusicPlayer/musicplayer.h"
#include "equalizerdialog.h"

#include <QTime>
#include <QApplication>
#include <QStyleHints>
#include <QDesktopWidget>

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
    // hides help button
    QApplication::setAttribute(Qt::AA_DisableWindowContextHelpButton);

    // creates a custom dialog
    EqualizerDialog dialog;

    dialog.exec();

    // returns and changes the default balance, bass, and treble levels.
    dialog.getLevels(balance, bass, treble);


    // sends the balance to the volume object and the base / treble to the music player object
    volume->changeBalance(balance);
    player->changeBass(bass);
    player->changeTreble(treble);
}
