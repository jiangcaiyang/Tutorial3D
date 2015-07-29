#include <QQmlAspectEngine>
#include <QRenderAspect>
#include <QInputAspect>
#include <QWindow>

#include "MainWindow.h"
#include "ui_MainWindow.h"

class View3D: public QWindow
{
public:
    View3D( QScreen* targetScreen = Q_NULLPTR ): QWindow( targetScreen )
    {
        setSurfaceType( QSurface::OpenGLSurface );

        QSurfaceFormat format;
        format.setSamples( 4 );
        setFormat( format );

        create( );
    }
};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    using namespace Qt3D;
    using namespace Qt3D::Quick;
    // 创建一个3D的视图
    // 1
    View3D* view3D = new View3D;

    // 2
    QQmlAspectEngine* engine = new QQmlAspectEngine;
    engine->aspectEngine( )->registerAspect( new QRenderAspect );
    engine->aspectEngine( )->registerAspect( new QInputAspect );

    // 3
    QVariantMap data;
    data.insert( QStringLiteral( "surface" ),
                 QVariant::fromValue( static_cast<QSurface*>( view3D ) ) );
    data.insert( QStringLiteral( "eventSource" ),
                 QVariant::fromValue( view3D ) );
    engine->aspectEngine( )->setData( data );

    // 4
    engine->aspectEngine( )->initialize( );
    engine->setSource( QUrl( "qrc:/qml/main.qml" ) );

    QVBoxLayout* l = qobject_cast<QVBoxLayout*>( ui->centralwidget->layout( ) );
    l->insertWidget( 0, QWidget::createWindowContainer( view3D ) );
}

MainWindow::~MainWindow()
{
    delete ui;
}
