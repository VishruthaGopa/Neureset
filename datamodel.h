#ifndef DATAMODEL_H
#define DATAMODEL_H

#include <QAbstractTableModel>

class DataModel: public QAbstractTableModel
{
    Q_OBJECT

    public:

        explicit DataModel(QObject *parent = nullptr);

        // overriding functions to create unique model
        int rowCount( const QModelIndex &parent = QModelIndex() ) const override;
        int columnCount( const QModelIndex &parent = QModelIndex() ) const override;
        bool insertRows(int row, int count, const QModelIndex &parent) override;

        QVariant data( const QModelIndex &index, int role = Qt::DisplayRole) const override;
        QVariant headerData( int header, Qt::Orientation orientation, int role ) const override;

    private:
        int ROWS = 1;
        const int COLUMNS = 4;

};

#endif // DATAMODEL_H
