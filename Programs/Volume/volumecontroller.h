#ifndef VOLUMECONTROLLER_H
#define VOLUMECONTROLLER_H

#include <QWidget>
#include <QSlider>
#include <QPushButton>

#include "volume.h"

class VolumeSlider : public QSlider
{
    Q_OBJECT
public:
    VolumeSlider();

protected:
    void mouseReleaseEvent(QMouseEvent *ev);
};

class VolumeController : public QWidget
{
    Q_OBJECT
    VolumeSlider front, rear;
    QPushButton mute, btnUp, btnDn, equalizer;
    Volume volume;

    void load();
    void save() const;
    void set(int newBalance);

    // const char *saveFile = "/home/pi/saved_volumes";
    const char *saveFile = "saved_volumes";

public slots:
    void changeBalance(int balance);

signals:
    void setEqualizer(int newBalance);

public:
    VolumeController(QWidget *parent = nullptr);

private:
    int m_balance = 50;
};
#endif // VOLUMECONTROLLER_H
