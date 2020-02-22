#ifndef STATUS_H
#define STATUS_H
#include <QString>

class Status
{
private:
    int steps; //number of user steps
    QString code; //code of game (for e.g. new game, end game)
    QString shipName; //name of the spaceship
    QString board; //current board status
    int type; //type of spaceship

public:
    Status(QString code, QString shipName, int type, int steps, QString board);
    int getSteps();
    QString getCode();
    QString getShipName();
    int getType();
    QString getBoard();
    QString toString();

};

#endif // STATUS_H
