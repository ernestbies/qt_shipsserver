#include "ship.h"


Ship::Ship()
{

}

Ship::Ship(QString name, int type)
{
    this->name = name;
    this->type = type;
}

int Ship::getType() {

    return this->type;
}

void Ship::setType(int type) {
    this->type = type;
}

QString Ship::getName() {
    return this->name;
}

QList<QString> Ship::getPositions(){
    return this->positions;
}

void Ship::setPositions(QList<QString> positions) {
    this->positions = positions;
}

void Ship::deletePos(QString pos){
    this->positions.removeOne(pos);
}


QDataStream &operator<<(QDataStream& out, Ship& ship){

    out << QString::number(ship.type) << ship.name << QString::number(ship.positions.size());
    for(int i = 0; i < ship.positions.size(); i++)
    {
        out << ship.positions.at(i);
    }

    return out;
}

QDataStream &operator>>(QDataStream& in, Ship *ship) {
    QString tmp;
    int count;

    in >> tmp; ship->type = tmp.toInt();
    in >> ship->name;
    in >> tmp; count = tmp.toInt();

    QList<QString> list;
    for(int i = 0; i < count; i++)
    {
        in >> tmp;
        list.append(tmp);

    }    
    ship->setPositions(list);

    return in;
}


