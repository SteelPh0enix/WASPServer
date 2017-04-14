#ifndef WASPREADER_HPP
#define WASPREADER_HPP

#include <QObject>

class WASPReader : public QObject
{
    Q_OBJECT
public:
    explicit WASPReader(QObject *parent = 0);

signals:

public slots:
};

#endif // WASPREADER_HPP