#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    img0.load(URL0);
    img0= img0.scaled(QSize(130,100) , Qt::KeepAspectRatio);

    img1.load(URL1);
    img1= img1.scaled(QSize(130,100) , Qt::KeepAspectRatio);

    img2.load(URL2);
    img2= img2.scaled(QSize(130,100) , Qt::KeepAspectRatio);

    img3.load(URL3);
    img3= img3.scaled(QSize(130,100) , Qt::KeepAspectRatio);

    img4.load(URL4);
    img4= img4.scaled(QSize(130,100) , Qt::KeepAspectRatio);

    img5.load(URL5);
    img5= img5.scaled(QSize(130,100) , Qt::KeepAspectRatio);

    ui->label_2->setPixmap(img0);
    ui->linea1->setStyleSheet(Negro);
    ui->linea2->setStyleSheet(Negro);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Leer_Archivo()
{
    string File_string="/home/abraham/Escritorio/micro_16/final_memory.txt";
    ifstream Archivo(File_string.c_str());

    for(int i=0; i<6; i++)
    {
        getline(Archivo, Dato);

        switch(i)
        {
            case 0:
                outs_E=Dato;
                if(outs_E != outs)
                {
                   outs=outs_E;
                    outs_N++;
                    Condicional=1;
                    Limpiar();
                    strikes_N=0;
                    balls_N=0;
                }
                break;

            case 1:
                  strikes_E=Dato;
                  if(strikes_E != strikes)
                  {
                      strikes=strikes_E;
                      strikes_N++;
                  }
            break;

            case 2:
                balls_E=Dato;
                if(balls_E != balls)
                {
                    balls=balls_E;
                    balls_N++;
                }
            break;

            case 3:
                lectura1_E=Dato;
                Qlectura1 = QString::fromStdString(lectura1_E);
                Carrera_E1=Tamano+Color+Qlectura1+font;
            break;

            case 4:
                lectura2_E=Dato;
                Qlectura2 = QString::fromStdString(lectura2_E);
                Carrera_E2=Tamano+Color+Qlectura2+font;
            break;

            case 5:
                lectura3_E=Dato;
            break;
        }
    }
     Archivo.close();
     Condiciones();
}

void MainWindow::Condiciones()
{
   //sleep(1);


    switch(outs_N)
    {

    case 1:
        ui->out1->setStyleSheet(Rojo);
       // Limpiar();

        break;

    case 2:
        ui->out2->setStyleSheet(Rojo);
      // Limpiar();
    break;

    case 3:
        ui->out2->setStyleSheet(Blanco);
        ui->out1->setStyleSheet(Blanco);
        Limpiar();
        outs_N=0;
        strikes_N=0;
        balls_N=0;
        return;
        break;
    }

    if(lectura1_E != lectura1)
    {
        lectura1 = lectura1_E;
        strikes_N=0;
        balls_N=0;
        Limpiar();
        Condicional=1;
    }

    if(lectura2_E != lectura2)
    {
        lectura2 = lectura2_E;
        strikes_N=0;
        balls_N=0;
        Limpiar();
        Condicional=1;
    }

    if(Condicional==0)
    {
        switch(strikes_N)
        {
            break;

            case 1:
                ui->strike1->setStyleSheet(Anaranjado);
            break;

            case 2:
                ui->strike2->setStyleSheet(Anaranjado);
            break;

            case 3:
                Limpiar();
                outs_N++;

            switch(outs_N)
            {
                case 1:
                    ui->out1->setStyleSheet(Rojo);
                    break;

                case 2:
                    ui->out2->setStyleSheet(Rojo);
                break;

                case 3:
                    ui->out2->setStyleSheet(Blanco);
                    ui->out1->setStyleSheet(Blanco);
                    Limpiar();
                    outs_N=0;
                break;
            }
            strikes_N=0;
            balls_N=0;
            return;
        }

        switch(balls_N)
        {
            case 1:
                ui->ball1->setStyleSheet(Anaranjado);
            break;

            case 2:
                ui->ball2->setStyleSheet(Anaranjado);
            break;

            case 3:
                ui->ball3->setStyleSheet(Anaranjado);
            break;

            case 4:
                Limpiar();
                strikes_N=0;
                balls_N=0;
            return;
            break;
        }
    }
    ui->Equipo1->setText(Carrera_E1);
    ui->Equipo2->setText(Carrera_E2);

    if(lectura3_E != lectura3)
    {

        lectura3 = lectura3_E;

        if(lectura3 =="0")
        ui->label_2->setPixmap(img0);

        if(lectura3 =="1")
        ui->label_2->setPixmap(img1);

        if(lectura3 =="2")
        ui->label_2->setPixmap(img2);

        if(lectura3 =="3")
        ui->label_2->setPixmap(img3);

        if(lectura3 =="4")
        ui->label_2->setPixmap(img4);

        if(lectura3 =="5")
        ui->label_2->setPixmap(img5);

    }

    Condicional=0;
}

void MainWindow::on_pActualizar_clicked()
{
    QPixmap img1;
    img1.load(URL2);
    img1= img1.scaled(QSize(130,100) , Qt::KeepAspectRatio);

    Leer_Archivo();
}

void MainWindow::Limpiar()
{
    ui->strike1->setStyleSheet(Blanco);
    ui->strike2->setStyleSheet(Blanco);
    ui->ball1->setStyleSheet(Blanco);
    ui->ball2->setStyleSheet(Blanco);
    ui->ball3->setStyleSheet(Blanco);
}
