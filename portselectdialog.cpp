#include "portselectdialog.hpp"
#include "ui_portselectdialog.h"

PortSelectDialog::PortSelectDialog(QDialog *parent) : QDialog(parent), ui(new Ui::portSelectDialog) {
    ui->setupUi(this);
    ui->lPortList->setModel(&portListModel);

    QObject::connect(ui->bSelectPort, &QPushButton::clicked, this, &PortSelectDialog::getSelection);
    QObject::connect(ui->bCancel, &QPushButton::clicked, this, &QDialog::hide);
}

PortSelectDialog::~PortSelectDialog() {
    delete ui;
}

void PortSelectDialog::selectPort() {
    ports = QSerialPortInfo::availablePorts();
    parsePortList();
    this->show();
}

void PortSelectDialog::parsePortList() {
    portListModel.removeRows(0, portListModel.rowCount());
    for(const auto& p: ports) {
        portListModel.insertRow(portListModel.rowCount());
        portListModel.setData(portListModel.index(portListModel.rowCount() - 1), QString("%1:%2 - %3, S/N: %4, %5").arg(
                            QString::number(p.vendorIdentifier(), 16), QString::number(p.productIdentifier(), 16),
                            p.portName(), p.serialNumber(), p.description()));
    }
}

void PortSelectDialog::getSelection() {
    QItemSelectionModel *selected = ui->lPortList->selectionModel();
    if (!selected->hasSelection()) return;
    QDialog::hide();
    emit portSelected(ports[selected->selectedIndexes()[0].row()]);
}
