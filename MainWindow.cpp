#include <QAspectEngine>
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

    // 创建一个3D的视图
    // 1
    View3D* view3D = new View3D;

    QVBoxLayout* l = qobject_cast<QVBoxLayout*>( ui->centralwidget->layout( ) );
    l->insertWidget( 0, QWidget::createWindowContainer( view3D ) );
}

MainWindow::~MainWindow()
{
    delete ui;
}
