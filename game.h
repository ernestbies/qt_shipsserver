#ifndef GAME_H
#define GAME_H

#include "ship.h"
#include "status.h"
#include <QString>
#include <QChar>


class Game
{
private:
   int steps; //number of steps
   QString user; //username
   QString areaBoard;
   QList<Ship> shipsList; //list of user's ships
   int boardNumbers[9][9]; //number of fields occupied by ships around the selected position

public:
    Game();
    Game(QString user);
    QString getUser();
    Status getStatus();
    int getSteps();
    QString getBoard();
    void boardGenerating();
    Status shot(QString position);
    QList<Ship> getShips();
    void showGame();
    void addSteps();
    void setShips(QList<Ship> list);

    friend QDataStream &operator<<(QDataStream& out, Game& game);
    friend QDataStream &operator>>(QDataStream& in, Game *game);


};


#endif // GAME_H
