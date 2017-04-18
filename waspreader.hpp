#ifndef WASPREADER_HPP
#define WASPREADER_HPP

#include <QObject>

namespace WASP {
    class Reader : public QObject
    {
        Q_OBJECT
    public:
        explicit Reader(QObject *parent = 0);

    signals:

    public slots:
    };
}

#endif // WASPREADER_HPP
