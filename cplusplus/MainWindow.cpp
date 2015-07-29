#include <QQmlAspectEngine>
#include <QRenderAspect>
#include <QInputAspect>
#include <QQmlContext>
#include <QWindow>
#include <QColorDialog>

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
    m_ambient = QColor( 153, 51, 26 );
    m_diffuse = QColor( 51, 153, 26 );
    m_specular = QColor( 153, 230, 26 );
    m_shininess = 0.6;
}

void Settings::setShowModel( bool showModel )
{
    if ( m_showModel == showModel ) return;
    m_showModel = showModel;
    emit showModelChanged( );
}

void Settings::setAmbient( const QColor& ambient )
{
    if ( m_ambient == ambient ) return;
    m_ambient = ambient;
    emit ambientChanged( );
}

void Settings::setDiffuse( const QColor& diffuse )
{
    if ( m_diffuse == diffuse ) return;
    m_diffuse = diffuse;
    emit diffuseChanged( );
}

void Settings::setSpecular( const QColor& specular )
{
    if ( m_specular == specular ) return;
    m_specular = specular;
    emit specularChanged( );
}

void Settings::setShininess( float shininess )
{
    if ( m_shininess == shininess ) return;
    m_shininess = shininess;
    emit shininessChanged( );
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->groupBox->setVisible( false );
    m_settings.setShininess( ui->shininessEdit->text( ).toFloat( ) );

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
    ui->showModelButton->setText( show? "隐藏模型": "显示模型" );
    m_settings.setShowModel( show );
}

void MainWindow::decorateButton( QPushButton* button, const QColor& color )
{
    QString styleSheetTemplate( "background: rgb( %1, %2, %3 )" );
    QString styleSheet = styleSheetTemplate.
                         arg( color.red( ) ).arg( color.green( ) ).
                         arg( color.blue( ) );
    button->setStyleSheet( styleSheet );
}

void MainWindow::on_ambientButton_clicked()
{
    QPushButton* button = qobject_cast<QPushButton*>( sender( ) );
    QColor color, prevColor;
    prevColor = m_settings.ambient( );
    color = QColorDialog::getColor( prevColor, this, "请选择一个颜色" );
    decorateButton( button, color );
    m_settings.setAmbient( color );
}

void MainWindow::on_diffuseButton_clicked()
{
    QPushButton* button = qobject_cast<QPushButton*>( sender( ) );
    QColor color, prevColor;
    prevColor = m_settings.diffuse( );
    color = QColorDialog::getColor( prevColor, this, "请选择一个颜色" );
    decorateButton( button, color );
    m_settings.setDiffuse( color );
}

void MainWindow::on_specularButton_clicked()
{
    QPushButton* button = qobject_cast<QPushButton*>( sender( ) );
    QColor color, prevColor;
    prevColor = m_settings.specular( );
    color = QColorDialog::getColor( prevColor, this, "请选择一个颜色" );
    decorateButton( button, color );
    m_settings.setSpecular( color );
}

void MainWindow::on_shininessEdit_returnPressed( void )
{
    m_settings.setShininess( ui->shininessEdit->text( ).toFloat( ) );
}
