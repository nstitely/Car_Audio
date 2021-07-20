#ifndef VOLUME_H
#define VOLUME_H

class Volume
{
public:
    Volume();
    ~Volume();

    void increaseVolumes(int delta);
    void increaseVolume(int speaker, int delta);
    void setVolume(int speaker, int volume);
    void setMaxVolume(int maxVolume);
    int getMaxVolume() const;
    int getVolume(int speaker);
    void setMute(bool mute = true);
    bool muted() const;
    void toggleMute();
    void setBalance();

    static const int amps = 2;

private:
    const int address[amps] = { 0x4A, 0x4B };
    int maxVolume = 100;

    bool m_muted = false;
    int file_i2c[amps];
    int m_volume[amps] = { 0, 0 };
    void set(int speaker, int volume);
    void set(int balance);
};

#endif // VOLUME_H
