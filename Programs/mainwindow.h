#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QMainWindow>
#include <QGridLayout>
#include <QDialog>

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QLabel *time;
    class VolumeController *volume;
    class MusicPlayer *player;
    class Brightness *bright;

    QGridLayout grid;

    void getEqualizer();
    void setLevels();

public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    void timerEvent(QTimerEvent *ev);
    int balance = 50;
    int bass = 50;
    int treble = 50;
};

#endif // MAINWINDOW_H
