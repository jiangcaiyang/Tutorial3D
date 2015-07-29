#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

class Settings: public QObject
{
    Q_OBJECT
    Q_PROPERTY( bool showModel READ showModel WRITE setShowModel NOTIFY showModelChanged )
    Q_PROPERTY( QColor ambient READ ambient WRITE setAmbient NOTIFY ambientChanged )
    Q_PROPERTY( QColor diffuse READ diffuse WRITE setDiffuse NOTIFY diffuseChanged )
    Q_PROPERTY( QColor specular READ specular WRITE setSpecular NOTIFY specularChanged )
    Q_PROPERTY( float shininess READ shininess WRITE setShininess NOTIFY shininessChanged )
public:
    explicit Settings( QObject* parent = Q_NULLPTR );

    bool showModel( void ) { return m_showModel; }
    void setShowModel( bool showModel );

    QColor ambient( void ) { return m_ambient; }
    void setAmbient( const QColor& ambient );

    QColor diffuse( void ) { return m_diffuse; }
    void setDiffuse( const QColor& diffuse );

    QColor specular( void ) { return m_specular; }
    void setSpecular( const QColor& specular );

    float shininess( void ) { return m_shininess; }
    void setShininess( float shininess );
signals:
    void showModelChanged( void );
    void ambientChanged( void );
    void diffuseChanged( void );
    void specularChanged( void );
    void shininessChanged( void );
protected:
    bool            m_showModel;
    QColor          m_ambient, m_diffuse, m_specular;
    float           m_shininess;
};

namespace Ui {
class MainWindow;
class QPushButton;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_showModelButton_clicked();
    void on_ambientButton_clicked();
    void on_diffuseButton_clicked();
    void on_specularButton_clicked();
    void on_shininessEdit_returnPressed();

private:
    void decorateButton( QPushButton* button, const QColor& color );

    Ui::MainWindow *ui;
    Settings        m_settings;
};

#endif // MAINWINDOW_H
