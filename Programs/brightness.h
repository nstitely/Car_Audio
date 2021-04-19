#ifndef BRIGHTNESS_H
#define BRIGHTNESS_H

#include <QSlider>

class Brightness : public QSlider
{
    Q_OBJECT
public:
    Brightness();
protected:
    void mouseReleaseEvent(QMouseEvent *ev);
protected slots:
    void setBrightness(int vol);
};

#endif // BRIGHTNESS_H
