#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class Settings: public QObject
{
    Q_OBJECT
    Q_PROPERTY( bool showModel READ showModel WRITE setShowModel NOTIFY showModelChanged )
public:
    explicit Settings( QObject* parent = Q_NULLPTR );

    bool showModel( void ) { return m_showModel; }
    void setShowModel( bool showModel );
signals:
    void showModelChanged( void );
protected:
    bool            m_showModel;
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_showModelButton_clicked();

private:
    Ui::MainWindow *ui;
    Settings        m_settings;
};

#endif // MAINWINDOW_H
