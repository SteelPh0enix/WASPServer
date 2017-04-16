#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QMessageBox>
#include <QApplication>
#include <QStringListModel>
#include "waspdata.hpp"
#include "waspreader.hpp"

namespace Ui {
class CanSatWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QStringListModel logModel;
    WASPData data;
    WASPReader reader;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::CanSatWindow *ui;

private slots:
    void exit();
    void parseFile();
    void connectToWASP();
    void saveData();
};

#endif // MAINWINDOW_HPP
