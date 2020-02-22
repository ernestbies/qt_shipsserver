#include <QCoreApplication>
#include "restserver.h"
#include "shipsserver.h"
#include "game.h"
#include <QDebug>
#include <QDateTime>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    RESTServer server;

    printf( "REST Serwer aplikacji SpaceShips 1.0 uruchomiony\n" );
    server.addRequestListener( new ShipsServer() );

    printf( "na porcie 8080.\n" );
    server.listen( 8080 );

    printf( "Zapytania kierowane na adres http://127.0.0.1:8080/api/.\n" );

    printf( "\n----- Logi serwera: -------\n" );

    qDebug() << QDateTime::currentDateTimeUtc().toString() +" - Start servera";


    return a.exec();
}
