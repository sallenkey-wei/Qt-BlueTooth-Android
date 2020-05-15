#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtBluetooth/qbluetoothglobal.h>
#include <QtBluetooth/qbluetoothlocaldevice.h>
#include <qbluetoothaddress.h>
#include <qbluetoothdevicediscoveryagent.h>
#include <qbluetoothlocaldevice.h>
#include <qbluetoothsocket.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    localDevice = new QBluetoothLocalDevice();
    discoveryAgent =new QBluetoothDeviceDiscoveryAgent();
    initBlueTooth();
    connect(ui->pBScanDev, &QPushButton::clicked, this, &MainWindow::scanDeviceSlot);
    connect(discoveryAgent,
            &QBluetoothDeviceDiscoveryAgent::deviceDiscovered,
            this,
            &MainWindow::addBlueToothDevicesToList
            );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initBlueTooth()
{
    if( localDevice->hostMode() == QBluetoothLocalDevice::HostPoweredOff )
    {
        localDevice->powerOn();
    }
    if( localDevice->hostMode() == QBluetoothLocalDevice::HostDiscoverable )
    {
        localDevice->setHostMode( QBluetoothLocalDevice::HostDiscoverable);
    }
}

void MainWindow::addBlueToothDevicesToList( const QBluetoothDeviceInfo &info )
{
    QString label = QString("%1 %2").arg(info.address().toString()).arg(info.name());

    QList<QListWidgetItem *> items = ui->listWidgetBTMac->findItems(label, Qt::MatchExactly);

    if (items.empty()) {
        QListWidgetItem *item = new QListWidgetItem(label);
        QBluetoothLocalDevice::Pairing pairingStatus = localDevice->pairingStatus(info.address());
        if (pairingStatus == QBluetoothLocalDevice::Paired || pairingStatus == QBluetoothLocalDevice::AuthorizedPaired )
            item->setTextColor(QColor(Qt::green));
        else
            item->setTextColor(QColor(Qt::black));
        ui->listWidgetBTMac->addItem(item);
    }

}

void MainWindow::scanDeviceSlot()
{

}
