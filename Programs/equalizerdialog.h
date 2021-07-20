#ifndef EQUALIZERDIALOG_H
#define EQUALIZERDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QGridLayout>


class EqualizerDialog : public QDialog
{
    Q_OBJECT

    QLabel *balance;
    QLabel *bass;
    QLabel *treble;

    QGridLayout grid;

public:
    explicit EqualizerDialog(QWidget *parent = nullptr);
    void getLevels(int &balance, int &bass, int &treble);

private slots:
    void setBalance();
    void setBass();
    void setTreble();
    int getBalance();
    int getBass();
    int getTreble();

private:
    // values for balance, bass and treble respectively. (e.g. x is balance, y is bass, z is treble)
    int x, y, z;
    QLabel *balanceLabel;
    QLabel *bassLabel;
    QLabel *trebleLabel;


signals:

};

#endif // EQUALIZERDIALOG_H
