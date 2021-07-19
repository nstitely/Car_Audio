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

    // const char *saveFile = "/home/pi/saved_volumes";
    const char *saveFile = "saved_volumes";

signals:
    void setEqualizer();

public:
    VolumeController(QWidget *parent = nullptr);
};
#endif // VOLUMECONTROLLER_H
