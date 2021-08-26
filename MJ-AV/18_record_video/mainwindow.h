#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "videothread.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  void startRecord();

  void stopRecord();

private slots:
  void on_audioButton_clicked();

private:
  Ui::MainWindow *ui;
  VideoThread *_audioThread = nullptr;
};
#endif // MAINWINDOW_H
