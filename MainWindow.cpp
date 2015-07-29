#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 创建一个3D的视图
    QWidget* view3D = new QWidget;
    view3D->setStyleSheet( "background: rgba( 0, 255, 0 )" );

    QVBoxLayout* l = qobject_cast<QVBoxLayout*>( ui->centralwidget->layout( ) );
    l->insertWidget( 0, view3D );
}

MainWindow::~MainWindow()
{
    delete ui;
}
