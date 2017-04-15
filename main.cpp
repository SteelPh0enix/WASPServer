#include "mainwindow.hpp"
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include "xyz.hpp"
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile f(":qdarkstyle/style.qss");
    if (f.exists()) {
        f.open(QFile::ReadOnly | QFile::Text);
        QTextStream ts(&f);
        a.setStyleSheet(ts.readAll());
    }

    //standard c-tor
    XYZ<int> test(1, 2, 3);
    qDebug() << test.x << test.y << test.z << '\n';

    //copy c-tor
    XYZ<int> test2(test);
    qDebug() << test2.x << test2.y << test2.z << '\n';

    //casting
    XYZ<float> test_f = static_cast<XYZ<float>>(test);
    test_f.x += 3.14;
    qDebug() << test_f.x << test_f.y << test_f.z << '\n';

    MainWindow w;
    w.show();

    return a.exec();
}
