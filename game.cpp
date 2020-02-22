#include "game.h"
#include "status.h"
#include "ship.h"
#include <QDebug>
#include <QDateTime>


Game::Game()
{

}

Game::Game(QString user)
{
    this->user = user;
    this->steps = 0;    
    boardGenerating();
}

QString Game::getUser() {
    return this->user;
}

Status Game::getStatus(){
    return (Status("LOADGAME", "", 0, steps, QString(getBoard())));
}

int Game::getSteps() {
    return this->steps;
}

QString Game::getBoard() {
    return this->areaBoard;
}


QList<Ship> Game::getShips(){
    return shipsList;
}

void Game::setShips(QList<Ship> list){
    this->shipsList = list;
}

void Game::addSteps(){
    this->steps++;
}

    //function which generates ships on board
void Game::boardGenerating(){
        int length, orientation, pozX, pozY, number;
        int xmin, xmax, ymin, ymax;
        bool find;
        QList<QString> tmpPos;

        for (int i=0; i < 81; i++) {
            this->areaBoard[i] = ' ';
            this->boardNumbers[i/9][i%9] = 0;
        }

        qsrand(QDateTime::currentDateTime().toTime_t());

        //creating spaceships and adding them to list
        shipsList.append(Ship("Transportowiec", 4));
        shipsList.append(Ship("Transportowiec", 4));
        shipsList.append(Ship("Samolot kosmiczny", 3));
        shipsList.append(Ship("Samolot kosmiczny", 3));
        shipsList.append(Ship("Samolot kosmiczny", 3));
        shipsList.append(Ship("Wahadłowiec", 2));
        shipsList.append(Ship("Wahadłowiec", 2));
        shipsList.append(Ship("Wahadłowiec", 2));
        shipsList.append(Ship("Szturmowiec", 1));
        shipsList.append(Ship("Szturmowiec", 1));



        for (int i = 0; i < shipsList.size(); i++) {
            find = false;
            //find = true - found positions at which the ship will not go beyond the boards
            //find = false - NOT found positions at which the ship will not go beyond the boards

            while (!find) {
                orientation = (qrand() % 2);
                //orientation - 0: horizontal, 1: vertical
                pozX = (qrand() % 9);
                //generates random position X for ship on board
                pozY = (qrand() % 9);
                //generates random position Y for ship on board

                if (orientation == 0) {
                    if ((pozX + shipsList[i].getType()) < 9) {
                        tmpPos.clear();

                        find = true;
                        //find = true - found positions for the ship successfully, fits on the board
                        length = 0;
                        //temporary variable for length of ships depended on ship type
                        //for example: type = 4 (length: 0, 1, 2, 3), type = 2 (length: 0,1)
                        while ((length < shipsList[i].getType()) & find) {
                            //check if positions on board are not occupied by other ships
                            number = pozX + length;
                            if (boardNumbers[number][pozY] != 0) {
                                //boardNumbers[number][pozY] == 0 - position is not occupied
                                //boardNumbers[number][pozY] != 0 - position is occupied
                                find = false;
                            }
                            if (number - 1 >= 0){
                                //ships can't touch each others, check if position is not occupied and fits on the board
                                if (boardNumbers[number - 1][pozY] != 0){
                                    find = false;
                                }
                            }
                            if (number + 1 <9){
                                if (boardNumbers[number + 1][pozY] != 0){
                                    find = false;
                                }
                            }
                            if (pozY - 1 >=0){
                                if (boardNumbers[number][pozY - 1] != 0) {
                                    find = false;
                                }
                            }
                            if (pozY + 1 < 9){
                                if (boardNumbers[number][pozY + 1] != 0) {
                                    find = false;
                                }
                            }
                            length++;
                            //I need check the entire length of the ship depended on its type
                        }
                        if (find) {
                            //if (find) - I checked positions, positions are not occupied, ship can be placed on board
                            for (int m = 0; m < shipsList[i].getType(); m++) {
                                number = pozX + m;
                                boardNumbers[number][pozY] = (shipsList[i].getType())*(-1);
                                //multiply by (-1) because later I must know what positions are occupied by ships
                                //negative numbers represents the postions of ships
                                //positive numbers represents the number of occupied positions around
                                tmpPos.append(QString::number(number) + QString::number(pozY));
                                //every ship has own list positions which occupies on board (tmpPos)
                            }
                            shipsList[i].setPositions(tmpPos);
                            //add ships positions to list
                        }
                    }
                } else {
                    //Same operations for vertical orientation

                    if ((pozY + shipsList[i].getType()) < 9) {
                        tmpPos.clear();

                        find = true;
                        length = 0;
                        while ((length < shipsList[i].getType()) & find) {
                            number = pozY + length;
                            if (boardNumbers[pozX][number] != 0) {
                                find = false;
                            }
                            if (number - 1 >= 0 ){
                                if (boardNumbers[pozX][number - 1] != 0) {
                                    find = false;
                                }
                            }
                            if (number + 1 < 9 ){
                                if (boardNumbers[pozX][number + 1] != 0) {
                                    find = false;
                                }
                            }
                            if (pozX - 1 >= 0){
                                if (boardNumbers[pozX - 1][number] != 0) {
                                    find = false;
                                }
                            }
                            if (pozX + 1 < 9){
                                if (boardNumbers[pozX + 1][number] != 0) {
                                    find = false;
                                }
                            }
                            length++;
                        }
                        if (find) {
                            for (int m = 0; m < shipsList[i].getType(); m++) {
                                number = pozY + m;
                                boardNumbers[pozX][number] = (shipsList[i].getType())*(-1);
                                tmpPos.append(QString::number(pozX) + QString::number(number));
                            }
                            shipsList[i].setPositions(tmpPos);
                        }
                    }
                }
            }
        }


        //for each ship, calculating how many ships are around
        //xmin - xmax -> range checked for position X
        //ymin - ymax -> range checked for position Y
        for(int y=0;y<9;y++){
            for(int x=0;x<9;x++) {
                if (boardNumbers[x][y] >= 0) {
                    ymin = y - 1;
                    ymax = y + 1;
                    if (ymin < 0) {
                        ymin = 0;
                    }
                    if (ymax > 8) {
                        ymax = 8;
                    }
                    xmin = x - 1;
                    xmax = x + 1;
                    if (xmin < 0) {
                        xmin = 0;
                    }
                    if (xmax > 8) {
                        xmax = 8;
                    }

                    number = 0;
                    for (int yp = ymin; yp <= ymax; yp++) {
                        for (int xp = xmin; xp <= xmax; xp++) {
                            if (!(xp == x && yp == y)) {
                                if (boardNumbers[xp][yp] < 0) {
                                    number++;
                                }
                            }
                        }
                    }
                    //number - how many positions are occupied by ships
                    boardNumbers[x][y] = number;
                }
            }
        }

    }


Status Game::shot(QString position) {
    int p, m, pos;
    int x, y;
    bool hit = false;

    if (shipsList.isEmpty()){
        qDebug() << QDateTime::currentDateTimeUtc().toString() +" - Koniec gry";
        return Status("ENDGAME","", 0, steps, QString(getBoard()));
    }

    x = position.mid(0,1).toInt();
    y = position.mid(1,1).toInt();
    pos = 9 * y + x;

    this->steps++;
    m = 0;
    while((m < shipsList.size()) & !hit) {

        p = shipsList[m].getPositions().indexOf(position);
        if (p!=-1) {
            shipsList[m].deletePos(position);
            this->areaBoard[pos] = QChar(64 + shipsList[m].getType());

            if (shipsList[m].getPositions().isEmpty()) {
                Status status("SHOTDOWN", shipsList[m].getName(), shipsList[m].getType(), getSteps(), QString(getBoard()));
                qDebug() << QDateTime::currentDateTimeUtc().toString() +" - Zatopiony statek: "+shipsList[m].getName();

                shipsList.removeAt(m);
                if (shipsList.isEmpty()) {
                    qDebug() << QDateTime::currentDateTimeUtc().toString() +" - Koniec gry";
                    Status status("ENDGAME","", 0, getSteps(), QString(getBoard()));
                }
                return status;
            } else {
                qDebug() << QDateTime::currentDateTimeUtc().toString() +" - Trafiony statek: "+shipsList[m].getName();
                qDebug() << " * pozycje statku na mapie: ";
                qDebug() << shipsList[m].getPositions();

                return (Status("HIT", shipsList[m].getName(), shipsList[m].getType(), getSteps(), QString(getBoard())));
            }
        }

        m++;
    }


    if (this->areaBoard[pos] == ' ') {
        this->areaBoard[pos] = QString::number(boardNumbers[x][y]).at(0);
        qDebug() << QDateTime::currentDateTimeUtc().toString() +" - Brak trafienia na pozycji: "+position;
        return (Status("MISS", "", 0, getSteps(), QString(getBoard())));
    } else {
        qDebug() << QDateTime::currentDateTimeUtc().toString() +" - Pozycja sprawdzona: "+position;
        return (Status("CHECKED", "", 0, getSteps(), QString(getBoard())));
    }

}

void Game::showGame(){
    qDebug() << "User:"+ getUser()+" steps:"+QString::number(getSteps())+" board:"+QString(getBoard());
    for(int i=0;i<getShips().length();i++){
        qDebug() <<getShips()[i].getName();
        qDebug() <<getShips()[i].getPositions();
    }
}



QDataStream &operator<<(QDataStream& out, Game& game){

    out << QString::number(game.steps) << game.user << game.areaBoard;
    out << QString::number(game.shipsList.size());
    for(int i = 0; i < game.shipsList.size(); i++)
    {
        out << game.shipsList[i];
    }
    for (int i=0;i<9;i++){
        for (int j=0;j<9;j++){
            out << QString::number(game.boardNumbers[i][j]);
        }
    }
    return out;
}


QDataStream &operator>>(QDataStream& in, Game *game) {
    QString tmp;    
    int count;

    in >> tmp; game->steps = tmp.toInt();
    in >> game->user >> game->areaBoard;
    in >> tmp; count = tmp.toInt();

    QList<Ship> list;
    for(int i = 0; i < count; i++)
    {
        Ship *ship = new Ship();
        in >> ship;
        list.append(*ship);

    }    
    game->setShips(list);

    for (int i=0;i<9;i++){
        for (int j=0;j<9;j++){
            in >> tmp;
            game->boardNumbers[i][j] = tmp.toInt();
        }
    }

    return in;
}

