#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qdebug.h>
#include "commn.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);    
    ~MainWindow();
    QString currIgnState;
    QString currGeoState;

public slots:
    void serverCustomSlots(QString arg);
private slots:
    void on_pushButton_clicked();
    void on_IGNTRIGERSENDER_clicked();
    void on_GEOTRIGERSENDER_clicked();
    void on_radioOK_clicked();
    void on_IgnStates_currentTextChanged(const QString &arg1);
    void on_Geostates_currentTextChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    Server commnObj;
    void ignStateInitialization();
    void geoStateInitialization();
};
#endif // MAINWINDOW_H
