#ifndef GAMEDATA_H
#define GAMEDATA_H

#include "game.h"
#include "status.h"
#include <QList>


class GameData
{
private:
    QList<Game> games;    
    void saveFile();
    void readFile();

public:
    GameData();
    Status getGame(QString user);
    Status newGame(QString user);
    Status shotGame(QString user, QString shot);
    void showGame(Game g);    

};

#endif // GAMEDATA_H

