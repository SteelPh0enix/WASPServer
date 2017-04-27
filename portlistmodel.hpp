#ifndef PORTLISTMODEL_HPP
#define PORTLISTMODEL_HPP

#include <QAbstractTableModel>

class portListModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit portListModel(QObject *parent = 0);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
};

#endif // PORTLISTMODEL_HPP
