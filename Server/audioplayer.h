#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include <QIODevice>
#include <QDebug>
#include "wavfile.h"



class AudioPlayer :public QIODevice
{
    Q_OBJECT
public:
    AudioPlayer();
    bool openWavFile(const QString &fileName);
    const QAudioFormat &fileFormat() const;
    qint64 headerLength() const;
    qint64 mypos() const;
    bool myseek(qint64 pos);
    bool pause();
    bool start();
    bool isPlaying();
    bool isPaused();
    bool isFastForwarding();
    bool isFastForwarding(bool forward);
    QByteArray readHeaderData();
    QByteArray readChunkData(qint64 len, qint64 pos);
    bool addChunkData(const char *data, qint64 len);
    bool readHeader(char *data, qint64 len);
    void resetPlayer();
    qint64 bytesAvailable() const;
    qint64 audioBufferSize() const;

private:
    qint64     audio_pos;
    qint64     progress_current;
    qint64     progress_max;
    QByteArray audio_buffer;
    WavFile sourceFile;
    bool playing;
    bool fastForwarding;
    bool paused;

protected:
     qint64 readData(char *data, qint64 len);
     qint64 writeData(const char *data, qint64 len);

signals:
    void streamChunkAudio(qint64 chunk, qint64 pos);
    void progressAudio(int value);
};

#endif // AUDIOPLAYER_H
