#ifndef SHIP_H
#define SHIP_H
#include <QString>
#include <QList>

class Ship
{
private:
    int type; //type of spaceship
    QString name; //name of the ship
    QList<QString> positions; //ship positions on the board

public:
    Ship();
    Ship(QString name, int type);
    int getType();
    void setType(int type);
    QString getName();
    QList<QString> getPositions();
    void deletePos(QString pos);
    void setPositions(QList<QString> positions);

    friend QDataStream &operator<<(QDataStream& out, Ship& ship);
    friend QDataStream &operator>>(QDataStream& in, Ship *ship);

};


#endif // SHIP_H
