#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStyleFactory>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer.start(1000);
    ui->enable1->setChecked(true);
    ui->enable2->setChecked(true);
    QApplication::setStyle(QStyleFactory::create("Fusion"));
//CAPACIDADES
    connect(ui->Capacidad1, SIGNAL(editingFinished()), this, SLOT(setcapacidadtanque1()));
    connect(ui->capacidad2, SIGNAL(editingFinished()), this, SLOT(setcapacidadtanque2()));
    connect(ui->Capacidad3, SIGNAL(editingFinished()), this, SLOT(setcapacidadtanque3()));

//CAUDALES
    //conecto texto con el set y el dial con el display
    connect(ui->CaudalIN1,SIGNAL(editingFinished()),this, SLOT(setcaudalIN1()));
    connect(ui->Dial1, SIGNAL(valueChanged(int)), this, SLOT(setcauactualIN1()));
    connect(ui->caudalout1, SIGNAL(editingFinished()), this, SLOT(setcaudalOUT1()));
    connect(ui->Dial2, SIGNAL(valueChanged(int)), this, SLOT(setcauactualOUT1()));

    connect(ui->enable1, SIGNAL(clicked(bool)), this, SLOT(enabletanque2()));
    connect(ui->caudalout2, SIGNAL(editingFinished()), this, SLOT(setcaudalOUT2()));
    connect(ui->Dial3, SIGNAL(valueChanged(int)), this, SLOT(setcauactualOUT2()));

    connect(ui->enable2, SIGNAL(clicked(bool)), this, SLOT(enabletanque3()));
    connect(ui->caudalout3, SIGNAL(editingFinished()), this, SLOT(setcaudalOUT3()));
    connect(ui->dial4, SIGNAL(editingFished()), this, SLOT(setcauactualOUT3()));


//TIMER
    connect(&timer, SIGNAL(timeout()), this, SLOT(setniveltanque1()));
    connect(&timer, SIGNAL(timeout()), this, SLOT(setniveltanque2()));
    connect(&timer, SIGNAL(timeout()), this, SLOT(setniveltanque3()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow:: setcapacidadtanque1(){
    capacidad1 = ui->Capacidad1->text().toDouble();
    ui->tanque1->setMaximum(capacidad1);
}

void MainWindow:: setniveltanque1(){
    double auxiliar = nivelactual1 + (caudalactualIN1/3600.0) - (cauactualout1/3600.0);

    if(nivelactual1<((10*capacidad1)/100.0)){
        if(auxiliar<capacidad1){
            ui->tanque1->setValue(auxiliar);
            nivelactual1 = auxiliar;
        }
        if(auxiliar<((10*capacidad1)/100.0)){
            ui->Dial2->setValue(0);
        }
    } else {
        if(auxiliar >= capacidad1){
            ui->tanque1->setValue(capacidad1);
            ui->Dial1->setValue(0);
            nivelactual1 = capacidad1;
        }
        if(auxiliar<capacidad1){
            ui->tanque1->setValue(auxiliar);
            nivelactual1 = auxiliar;
        }
        if(auxiliar<((10*capacidad1)/100.0)){
            ui->Dial2->setValue(0);
            ui->tanque1->setValue(((10*capacidad1)/100.0));
            nivelactual1 = ((10*capacidad1)/100.0);
        }
    }


    if(nivelactual1==capacidad1){
        ui->Dial1->setEnabled(false);
    } else {
        ui->Dial1->setEnabled(true);
    }
    if(nivelactual1>((10*capacidad1)/100)){
        if(((nivelactual2<capacidad2) && ui->enable1->isChecked()) || ((nivelactual3<capacidad3) && ui->enable2->isChecked())){
            ui->Dial2->setEnabled(true);
        } else {
            ui->Dial2->setEnabled(false);
        }
    } else {
        ui->Dial2->setEnabled(false);
    }
}

void MainWindow:: setniveltanque2(){
    double auxiliar = nivelactual2 + caudalactualIN2 - (cauactualout2/3600.0);

    if(nivelactual2<((10*capacidad2)/100.0)){
        if(auxiliar<=capacidad2){
            ui->Tanque2->setValue(auxiliar);
            nivelactual2 = auxiliar;
        }
    } else {
        if(auxiliar >= capacidad2){
            ui->Tanque2->setValue(capacidad2);
            ui->Dial2->setValue(0);
            nivelactual2 = capacidad2;
        }
        if(auxiliar<capacidad2){
            ui->Tanque2->setValue(auxiliar);
            nivelactual2 = auxiliar;
        }
        if(auxiliar<((10*capacidad2)/100.0)){
            ui->Dial3->setValue(0);
            ui->Tanque2->setValue(((10*capacidad2)/100.0));
            nivelactual2 = ((10*capacidad2)/100.0);
        }
    }

    if(nivelactual2 == capacidad2){
        if(not(ui->enable2->isChecked()) || nivelactual3 == capacidad3){
            ui->Dial2->setEnabled(false);
            ui->Dial2->setValue(0);
        }
    }
    if(nivelactual2<((10*capacidad2)/100.0)){
        ui->Dial3->setValue(0);
        ui->Dial3->setEnabled(false);
    } else {
        ui->Dial3->setEnabled(true);
    }

}

/*void MainWindow:: enabletanque2(){
    if(ui->enable1->isChecked()){
        ui->Dial3->setEnabled(true);
        ui->Dial3->setValue(cauactualout2);
    } else {
        ui->Dial3->setValue(0);
        ui->Dial3->setEnabled(false);
    }
}*/

void MainWindow:: enabletanque3(){
    if(ui->enable2->isChecked()){
        //ui->dial4->setEnabled(true);
        if(nivelactual3<capacidad3){
            if(ui->enable1->isChecked() && nivelactual2<capacidad2){
                caudalactualIN3 = cauactualout1/2.0;
            } else {
                caudalactualIN3 = cauactualout1;
            }
        } else {
            caudalactualIN3 = 0;
        }
    } else {
        caudalactualIN3 = 0;
        if(ui->enable1->isChecked() && nivelactual2<capacidad2){
            caudalactualIN3 = cauactualout1;
        }
        ui->dial4->setValue(0);
        ui->dial4->setEnabled(false);
    }
}

void MainWindow:: setniveltanque3(){
    double auxiliar = nivelactual3 + caudalactualIN3 - (cauactualout3/3600.0);

    if(nivelactual3<((10*capacidad3)/100.0)){
        if(auxiliar<capacidad3){
            ui->Tanque3->setValue(auxiliar);
            nivelactual3 = auxiliar;
        }
        if(auxiliar<((10*capacidad3)/100.0)){
            ui->dial4->setValue(0);
        }
    } else {
        if(auxiliar >= capacidad3){
            ui->Tanque3->setValue(capacidad3);
            ui->Dial3->setValue(0);
            nivelactual3 = capacidad3;
        }
        if(auxiliar<capacidad3){
            ui->Tanque3->setValue(auxiliar);
            nivelactual3 = auxiliar;
        }
        if(auxiliar<((10*capacidad3)/100.0)){
            ui->dial4->setValue(0);
            ui->Tanque3->setValue(((10*capacidad3)/100.0));
            nivelactual3 = ((10*capacidad3)/100.0);
        }
    }


    if(nivelactual3 == capacidad3){
        if(not(ui->enable1->isChecked()) || nivelactual2 == capacidad2){
            ui->Dial2->setEnabled(false);
        }
    }
    if(nivelactual3 < ((10*capacidad3)/100.0)){
        ui->dial4->setEnabled(false);
    } else {
        ui->dial4->setEnabled(true);
    }
}


void MainWindow:: setcaudalIN1(){
    caudalin1 = ui->CaudalIN1->text().toDouble();
    ui->Dial1->setMaximum(caudalin1);
}
void MainWindow:: setcauactualIN1(){
    caudalactualIN1 = ui->Dial1->value();
    ui->Display1->display(caudalactualIN1);
}

void MainWindow::setcaudalOUT1(){
    caudalout1 = ui->caudalout1->text().toDouble();
    ui->Dial2->setMaximum(caudalout1);
}
void MainWindow:: setcauactualOUT1(){
    cauactualout1 = ui->Dial2->value();
    ui->display2->display(cauactualout1);
}



void MainWindow:: setcaudalOUT2(){
    caudalout2 = ui->caudalout1->text().toDouble();
    ui->Dial3->setMaximum(caudalout2);
}

void MainWindow:: setcaudalOUT3(){
    caudalout3 = ui->caudalout3->text().toDouble();
    ui->dial4->setMaximum(caudalout3);
}


void MainWindow:: setcapacidadtanque2(){
    capacidad2 = ui->capacidad2->text().toDouble();
    ui->Tanque2->setMaximum(capacidad2);
}


void MainWindow:: setcapacidadtanque3(){
    capacidad3 = ui->Capacidad3->text().toDouble();
    ui->Tanque3->setMaximum(capacidad3);
}


void MainWindow:: setcauactualOUT2(){
    cauactualout2 = ui->Dial3->value();
    ui->display3->display(cauactualout2);
}

void MainWindow:: setcauactualOUT3(){
    cauactualout3 = ui->dial4->value();
    ui->display4->display(cauactualout3);
}


