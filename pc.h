#ifndef PC_H
#define PC_H

#include <QObject>

class PC : public QObject
{
    Q_OBJECT
    public:
        explicit PC(QObject *parent = nullptr);

        // functions
        void saveSession();
        void setConnect(bool);
        bool getConnect();

    private:
        bool isConnected;

    signals:

};

#endif // PC_H
