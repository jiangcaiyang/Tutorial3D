#include <QApplication>
#include "MainWindow.h"

int main( int argc, char** argv )
{
    QApplication app( argc, argv );

    MainWindow m;
    m.show( );

    return app.exec( );
}
