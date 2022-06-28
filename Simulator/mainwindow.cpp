#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: lightblue");
    this->setWindowTitle("UDC SIMULATOR");
    this->ignStateInitialization();
    this->geoStateInitialization();   
    ui->IgnStates->setStyleSheet("background-color: red");
    ui->IGNTRIGERSENDER->setStyleSheet("background-color: green");
    ui->Geostates->setStyleSheet("background-color: red");
    ui->GEOTRIGERSENDER->setStyleSheet("background-color: green");
    ui->lineEdit->setVisible(false);
    connect(&commnObj, SIGNAL(serverCustomSignals(QString)), \
               this, SLOT( serverCustomSlots(QString ) ) );
    ui->listWidget->addItem("Log");
    ///ui->listWidget->clear();
  }



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::serverCustomSlots(QString arg)
{   
    //qDebug() << ui->listWidget->count();
    ui->listWidget->addItem(arg);
}

void MainWindow::on_pushButton_clicked()
{
}

void MainWindow::ignStateInitialization()
{

    ui->IgnStates->addItem("IGN_OFF");
    ui->IgnStates->addItem("IGN_ON");
    ui->IgnStates->addItem("IGN_ACC");
    ui->IgnStates->addItem("IGN_LOCK");
}

void MainWindow::geoStateInitialization()
{
    ui->Geostates->addItem("India");
    ui->Geostates->addItem("Germany");
    ui->Geostates->addItem("Kerala");
    ui->Geostates->addItem("Goa");
    ui->Geostates->addItem("Delhi");
}

void MainWindow::on_IGNTRIGERSENDER_clicked()
{
    qDebug() << ui->IgnStates->currentText();
    commnObj.vectCommand.push_back(ui-> \
                    IgnStates->currentText());
    this->currIgnState =
                 ui->IgnStates->currentText();
}

void MainWindow::on_radioOK_clicked()
{
    if ( ui->connect->isChecked() ) {
    bool ret = commnObj.connect();
        if (ret == true){
            commnObj.startThread();
        }
        else{
            qDebug() << "Socket creation failed";
        }
    }
    if ( ui->disconnect->isChecked() ){
        QString termMsge = QString::number(TERM_MSGE);
        commnObj.vectCommand.push_back(termMsge);
        commnObj.stopConnection();
        this->close();
    }
}

void MainWindow::on_GEOTRIGERSENDER_clicked()
{
 commnObj.vectCommand.push_back(ui->Geostates->currentText() );
 this->currGeoState = ui->Geostates->currentText();
}


void MainWindow::on_IgnStates_currentTextChanged \
                              (const QString &arg1)
{
    this->currIgnState = arg1;   
}


void MainWindow::on_Geostates_currentTextChanged \
                              (const QString &arg1)
{
    this->currGeoState = arg1;    
}

