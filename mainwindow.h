#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class QBluetoothDeviceDiscoveryAgent;
class QBluetoothLocalDevice;
class QBluetoothSocket;
class QBluetoothDeviceInfo;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    void initBlueTooth();
    void addBlueToothDevicesToList( const QBluetoothDeviceInfo &info );

private slots:
    void scanDeviceSlot();

private:
    Ui::MainWindow *ui;
    QBluetoothDeviceDiscoveryAgent *discoveryAgent;
    QBluetoothLocalDevice *localDevice;
    QBluetoothSocket *socket;
};

#endif // MAINWINDOW_H
