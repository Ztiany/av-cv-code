#include "audiothread.h"

#include "ffmpegs.h"
#include <QDebug>

AudioThread::AudioThread(QObject *parent) : QThread(parent) {
  // 当监听到线程结束时（finished），就调用deleteLater回收内存
  connect(this, &AudioThread::finished, this, &AudioThread::deleteLater);
}

AudioThread::~AudioThread() {
  // 断开所有的连接
  disconnect();
  // 内存回收之前，正常结束线程
  requestInterruption();
  // 安全退出
  quit();
  wait();
  qDebug() << this << "析构（内存被回收）";
}

void AudioThread::run() {
  // 44100_s16le_2 -> 48000_f32le_1 -> 48000_s32le_1 -> 44100_s16le_2
  // test：
  // 1. ffplay -ar 44100 -ac 2 -f s16le -i 44100_s16le_2.pcm
  // 2. ffplay -ar 48000 -ac 1 -f f32le -i 48000_f32le_1.pcm
  // 3. ffplay -ar 48000 -ac 1 -f s32le -i 48000_s32le_1.pcm
  // 4. ffplay -ar 44100 -ac 2 -f s16le -i 44100_s16le_2_new.pcm

  ResampleAudioSpec ras1;
  ras1.filename = "D:/44100_s16le_2.pcm";
  ras1.sampleFmt = AV_SAMPLE_FMT_S16;
  ras1.sampleRate = 44100;
  ras1.chLayout = AV_CH_LAYOUT_STEREO;

  ResampleAudioSpec ras2;
  ras2.filename = "D:/48000_f32le_1.pcm";
  ras2.sampleFmt = AV_SAMPLE_FMT_FLT;
  ras2.sampleRate = 48000;
  ras2.chLayout = AV_CH_LAYOUT_MONO;

  ResampleAudioSpec ras3;
  ras3.filename = "D:/48000_s32le_1.pcm";
  ras3.sampleFmt = AV_SAMPLE_FMT_S32;
  ras3.sampleRate = 48000;
  ras3.chLayout = AV_CH_LAYOUT_MONO;

  ResampleAudioSpec ras4 = ras1;
  ras4.filename = "D:/44100_s16le_2_new.pcm";

  FFmpegs::resampleAudio(ras1, ras2);
  FFmpegs::resampleAudio(ras2, ras3);
  FFmpegs::resampleAudio(ras3, ras4);
}
