#include "datamodel.h"
#include <QTime>
#include <QDate>

DataModel::DataModel(QObject *parent): QAbstractTableModel(parent) {}

int DataModel::rowCount(const QModelIndex & /*parent*/ ) const{ return ROWS; }

int DataModel::columnCount(const QModelIndex & /*parent*/ ) const { return COLUMNS; }

QVariant DataModel::data( const QModelIndex &index, int role) const {


    switch(role){
        case Qt::DisplayRole:
//            return QString("Row%1, Column%2").arg(index.row() + 1).arg(index.column()+1);

            return QString(" ");
        case Qt::TextAlignmentRole:
            return int(Qt::AlignLeft | Qt::AlignVCenter);
    }

    return QVariant();
}

QVariant DataModel::headerData(int header, Qt::Orientation orientation, int role) const {
    if( role == Qt::DisplayRole && orientation == Qt::Horizontal ){
        switch ( header ){
            case 0:
                return QString("Date");
            case 1:
                return QString("Time");
            case 2:
                return QString("Before Baseline");
            case 3:
                return QString("After Baseline");
        }
    }

    return QVariant();
}

bool DataModel::insertRows(int row, int count, const QModelIndex &parent){

    beginInsertRows(parent, row, row + count - 1);
    ROWS += count;
    endInsertRows();

    return true;
}
