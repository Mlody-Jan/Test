#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPainter>
#include <QDebug>
#include <QWidget>
#include <QProgressBar>
#include <QTime>
#include <QPixmap>
#include <QTransform>
#include <QPicture>


//---------------zmienne beng beng----------

//flaoty
float angle = 0;
float angle2 = 0;

//inty
int i=0;
int speed =0;
int zadajnik=0;
int moc=0;

//ból głowy
bool flaga =false;
bool flaga2 =false;
bool flaga3 =false;
bool flaga4=false;
bool zap=false;         //zapłon
bool odpal=false;       //odpalanie w sensie gotowość do odpalenia?
bool ruszanie=false;    //gotowość do ruszenia?
bool D=false;           //do przodu
bool P=false;           //postój Parking etc
bool R=false;           //do tyłu
bool gotowy=false;      //gotów do jazdy

//double
double kat=45; //not use

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{

    //rysowanie kółka od prędkościomierza
    QPainter p(this);                               //tworze obiekt p klasy Qpainter
    p.setRenderHint(QPainter::Antialiasing);        //coś tu jest ale nie wiem co z neta wziołem, działa tak czy działa bez nie wiem boje się sprawdzić
    QRectF rect = QRectF(300, 200, 200, 200);       //tu jest jakaś zmienna która trzyma współrzędne(x,y) i wielkość(x,y)
    p.drawEllipse(rect);                            //Rysu rysu kółko małe

    //rysowanie kółka od obrotomierza
    QPainter r(this);
    r.setRenderHint(QPainter::Antialiasing);
    QRectF circ = QRectF(700, 200, 200, 200);
    r.drawEllipse(circ);

    QPainter r1(this);
    r1.setRenderHint(QPainter::Antialiasing);
    QRectF circ1 = QRectF(796, 296, 8, 8);
    r1.drawEllipse(circ1);

    QPainter r2(this);
    r2.setRenderHint(QPainter::Antialiasing);
    QRectF circ2 = QRectF(396, 296, 8, 8);
    r2.drawEllipse(circ2);


    QPainter l(this);
    l.setRenderHint(QPainter::Antialiasing);
    QTransform transform;                    //Robimy obiekt klasy transfor, bo musi się kręcić jak bęben w pralce
    transform.translate(400, 300);           //tu dajemy początkowy punkt obrotu
    transform.rotate(angle);                 //typ ruchu i argument, tutaj jest obróT i kąt-tłumaczone za pomocą google trnaslator
    transform.translate(-400, -300);         //tu jest odwrotnoć punktu początkowego, czemu nie wiem, lecz linia jest w jednej orientacji Dobrej B)
    l.setTransform(transform);               // i tu uruchamiamy jazde, jazda jazda biała gwiazdaaaaaa
    QLine line = QLine(400, 300, 400, 375);  // Końcowy punkt linii
    l.drawLine(line);

    QPainter l2(this);
    l2.setRenderHint(QPainter::Antialiasing);
    QTransform transform1;
    transform1.translate(800,300);
    transform1.rotate(angle2);
    transform1.translate(-800,-300);
    l2.setTransform(transform1);
    QLine linia = QLine(800,300,800,375);
    l2.drawLine(linia);

    QPainter pro(this);                         //linia 25 procent
    pro.setRenderHint(QPainter::Antialiasing);
    QLine linika= QLine(743,243,729,229);
    pro.drawLine(linika);

    QPainter pro1(this);                         //linia 75 procent
    pro1.setRenderHint(QPainter::Antialiasing);
    QLine linika1= QLine(871,229,857,243);
    pro1.drawLine(linika1);

    QPainter pro2(this);                         //linia 50 procent
    pro1.setRenderHint(QPainter::Antialiasing);
    QLine linika2= QLine(800,220,800,200);
    pro1.drawLine(linika2);

    QPainter pro3(this);                         //linia 0 procent
    pro3.setRenderHint(QPainter::Antialiasing);
    QLine linika3= QLine(700,300,720,300);
    pro3.drawLine(linika3);

    QPainter pro4(this);                         //linia 100 procent
    pro4.setRenderHint(QPainter::Antialiasing);
    QLine linika4= QLine(900,300,880,300);
    pro4.drawLine(linika4);


    if (flaga == true && !flaga3 && odpal==false) {                        //ruszanie wskazówkami na początku
        ruszanie=true;
        if (!flaga2 && angle < 270) {
            angle += 1;
            angle2 +=1;
        } else if (!flaga2 && angle == 270) {
            flaga2 = true;
        } else if (flaga2 && angle > 60) {
            angle -= 1;
            angle2-=1;
        } else if (flaga2 && angle == 60) {
            flaga = false;
            flaga2 = false;
            ruszanie= false;
            odpal=true;
        }
    }

    if (flaga3==true && !flaga4){       //start animacja
        if(angle2<89){
            angle2+=0.25;
        }
        else if(angle>90 && zadajnik==0 && gotowy && !D || !R ){
            angle2=90;

        }
        gotowy=true;
    }
    else if(flaga4==true && !flaga3){ //stop animacja
        if(angle2>60){
            angle2-=0.25;
        }
        else{
            angle2=60;


        }
        gotowy=false;
    }
    if(D && !flaga4) ui->lcdNumber->display("d");
    else if(R && !flaga4) ui->lcdNumber->display("r");
    else ui->lcdNumber->display("P");



    if(!zap) ui->lcdNumber_2->display(" ");     //prędkościomierz
    else
        ui->lcdNumber_2->display("0");


    if (gotowy && D || R){
    ui->lcdNumber_2->display(zadajnik);
        if(angle<zadajnik*3/4+60){
        angle+=0.5;
        }
        else if (angle>zadajnik*3/4+60){
            angle-=0.5;}
        else if (angle==zadajnik*3/4+60){
            angle=zadajnik*3/4+60;
        }

        if(angle2<zadajnik*3/5+90)angle2+=1;
        else if(angle2>zadajnik*3/5+90)angle2-=1;
        else if(angle2==zadajnik*3/5+90)angle2=zadajnik*3/5+90;

    }

    this->update();                      //-------------------------uaktualnienie programu i animacji -------------------------------------------
}


void MainWindow::on_pushButton_clicked()
{
    zap=true;
    flaga=true;
    flaga4=false;
    //flaga3=false;
}


void MainWindow::on_pushButton_2_clicked() //start
{
    if(zap==true && !ruszanie){
        flaga3=true;
        flaga4=false;
    }
}


void MainWindow::on_pushButton_3_clicked() //stop
{
    if(zap==true && !ruszanie){
        flaga4=true;
        flaga3=false;
        P=true;
        D=false;
        R=false;
    }
}


void MainWindow::on_pushButton_4_clicked() //do przodu
{
    if(flaga3 && !R){
    D=true;
    P=false;
    R=false;
    }

}


void MainWindow::on_pushButton_5_clicked()
{
    if(flaga3 || flaga4){
        D=false;
        P=true;
        R=false;
    }
}


void MainWindow::on_pushButton_6_clicked()
{
    if(flaga3 && !D){
        D=false;
        P=false;
        R=true;
    }
}



void MainWindow::on_verticalSlider_valueChanged(int value)
{
    zadajnik=value;
}

