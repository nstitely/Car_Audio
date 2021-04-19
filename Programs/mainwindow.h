#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QMainWindow>
#include <QGridLayout>

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QLabel *time;
    class VolumeController *volume;
    class MusicPlayer *player;
    class Brightness *bright;

    QGridLayout grid;

public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    void timerEvent(QTimerEvent *ev);
};

#endif // MAINWINDOW_H
