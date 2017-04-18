#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QMessageBox>
#include <QApplication>
#include <QFileDialog>
#include <QString>
#include <QStringListModel>
#include "waspdata.hpp"
#include "waspreader.hpp"

namespace Ui {
class CanSatWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::CanSatWindow *ui;
    QStringListModel logModel;
    QStringListModel gpsModel;
    WASP::Data data;
    WASP::Reader reader;

private slots:
    void exit();
    void parseFile();
    void connectToWASP();
    void saveData();
public slots:
    void update(const WASP::Dataset &data);
};

#endif // MAINWINDOW_HPP
