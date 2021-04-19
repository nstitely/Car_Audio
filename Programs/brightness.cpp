#include "brightness.h"

#include <QMouseEvent>

#include <QFile>
#include <QTextStream>

#include <QDebug>

Brightness::Brightness()
    : QSlider(Qt::Vertical)
{
    setRange(0,100);

    setPageStep(1);
    setSingleStep(1);

    setTracking(false);

    setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );

    setStyleSheet(R"(

    .Brightness {
    }

    .Brightness::groove:vertical {
        border: 1px solid #262626;
        width: 5px;
        background: #393939;
        margin: 24px 12px;
    }

    .Brightness::handle:vertical {
        background: #22B14C;
        border: 5px solid #B5E61D;
        height: 23px;
        margin: -24px -12px;
    }

    )");

    connect(this, &QSlider::valueChanged, this, &Brightness::setBrightness);

    setMinimumWidth(50);
}

void Brightness::mouseReleaseEvent(QMouseEvent *ev)
{
    QSlider::mouseReleaseEvent(ev);

    ev->accept();
    double percent = double(height() - ev->y()) / double(height());
    int newPos = double(maximum() - minimum()) * percent + minimum();
    setValue(newPos);
}

void Brightness::setBrightness(int vol)
{
    QFile f("/sys/class/pwm/pwmchip0/pwm0/duty_cycle");
    if(!f.open(QIODevice::WriteOnly))
    {
        qWarning() << "Could not open screen brightness file!";
    }

    // vol = 0 to 100
    // out = 100 to 50000;
    // meh. close enough.
    int out = std::max(100, 500 * vol);
    QTextStream o(&f);
    o << out << endl;
}
