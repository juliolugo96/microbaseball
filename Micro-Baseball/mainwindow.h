#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <iostream>
#include <fstream>
#include <string>
#include <qdatetime.h>
#include <unistd.h>
#include <stdlib.h>

using namespace std;

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
    void on_pActualizar_clicked();

private:
    Ui::MainWindow *ui;

    void Leer_Archivo();
    void Condiciones();
    void Limpiar();

    const char* URL0= "/home/abraham/Escritorio/3/ima0.png";
    const char* URL1= "/home/abraham/Escritorio/3/ima1.png";
    const char* URL2= "/home/abraham/Escritorio/3/ima2.png";
    const char* URL3= "/home/abraham/Escritorio/3/ima3.png";
    const char* URL4= "/home/abraham/Escritorio/3/ima4.png";
    const char* URL5= "/home/abraham/Escritorio/3/ima5.png";

    QPixmap img0,img1,img2,img3,img4,img5;

    int Condicional=0;
    //int A=0;

    // COLORES
    QString Amarillo="background-color:rgb(249, 209, 42)";
    QString Anaranjado="background-color:rgb(225, 117, 20)";
    QString Blanco="background-color:rgb(255, 255, 255)";
    QString Rojo="background-color:rgb(240, 44, 44)";
    QString Negro="background-color: rgb(24, 12, 12)";

    string Dato;
    string strikes="0", balls="0", outs="0", lectura1="0",lectura2="0", lectura3="0";
    // datos recien leidos
    string strikes_E, balls_E,outs_E, Hombres_E, lectura1_E,lectura2_E,lectura3_E;

    int strikes_N=0, balls_N=0, outs_N=0;  // dato interno en entero

    // Letra en HTLM
    QString Tamano="< font size=12 ";
    QString  Color= "color=black>";
    QString font= "<font>";
    QString Carrera_E1,Carrera_E2, Qlectura1, Qlectura2;
};

#endif // MAINWINDOW_H
