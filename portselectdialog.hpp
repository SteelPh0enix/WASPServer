#ifndef PORTSELECTDIALOG_HPP
#define PORTSELECTDIALOG_HPP

#include <QDialog>
#include <QObject>
#include <QStringList>
#include <QStringListModel>
#include <QSerialPortInfo>
#include <QList>
#include <QMessageBox>
#include <QItemSelectionModel>

namespace Ui {
class portSelectDialog;
}

class PortSelectDialog : public QDialog
{
    Q_OBJECT

    Ui::portSelectDialog *ui;
    QStringListModel portListModel;
    QList<QSerialPortInfo> ports;

    void parsePortList();
public:
    explicit PortSelectDialog(QDialog *parent = 0);
    ~PortSelectDialog();

    void selectPort();
signals:
    void portSelected(QSerialPortInfo port);
private slots:
    void getSelection();
};

#endif // PORTSELECTDIALOG_HPP
