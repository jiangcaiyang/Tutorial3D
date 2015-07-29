#include <QQmlAspectEngine>
#include <QRenderAspect>
#include <QInputAspect>
#include <QQmlContext>
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


Settings::Settings( QObject* parent ): QObject( parent )
{
    m_showModel = true;
}

void Settings::setShowModel( bool showModel )
{
    if ( m_showModel == showModel ) return;
    m_showModel = showModel;
    emit showModelChanged( );
}

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
    QQmlAspectEngine* engine = new QQmlAspectEngine( this );
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
    engine->qmlEngine( )->rootContext( )->setContextProperty( "_settings", &m_settings );

    // 5
    engine->aspectEngine( )->initialize( );
    engine->setSource( QUrl( "qrc:/qml/main.qml" ) );

    QVBoxLayout* l = qobject_cast<QVBoxLayout*>( ui->centralwidget->layout( ) );
    l->insertWidget( 0, QWidget::createWindowContainer( view3D ) );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_showModelButton_clicked()
{
    bool show = m_settings.showModel( );
    show = !show;
    ui->showModelButton->setText( show? "显示模型": "隐藏模型" );
    m_settings.setShowModel( show );
}
