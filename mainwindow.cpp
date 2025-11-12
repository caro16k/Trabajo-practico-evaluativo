#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStyleFactory>
#include <iostream>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer.start(1000);
    ui->enbprinc0->setChecked(true);
    ui->enbprinc1->setChecked(true);
    ui->enable1->setChecked(true);
    ui->enable2->setChecked(true);
    QApplication::setStyle(QStyleFactory::create("Fusion"));

//CAPACIDADES
    connect(ui->Capacidad0, SIGNAL(editingFinished()), this, SLOT(setcapacidadtanque0()));
    connect(ui->Capacidad1, SIGNAL(editingFinished()), this, SLOT(setcapacidadtanque1()));
    connect(ui->capacidad2, SIGNAL(editingFinished()), this, SLOT(setcapacidadtanque2()));
    connect(ui->Capacidad3, SIGNAL(editingFinished()), this, SLOT(setcapacidadtanque3()));

//DIALES
    connect(ui->Dial0, SIGNAL(valueChanged(int)), this,SLOT(setcauactualIN0()));
    connect(ui->Dial1, SIGNAL(valueChanged(int)), this, SLOT(setcauactualIN1()));
    connect(ui->Dial2, SIGNAL(valueChanged(int)), this, SLOT(setcauactualmedio()));
    connect(ui->Dial3, SIGNAL(valueChanged(int)), this, SLOT(setcauactualOUT2()));
    connect(ui->dial4, SIGNAL(valueChanged(int)), this, SLOT(setcauactualOUT3()));

//ENABLES
    connect(ui->enbprinc0, SIGNAL(clicked(bool)), this, SLOT(enabletanque0()));
    connect(ui->enbprinc1, SIGNAL(clicked(bool)), this, SLOT(enabletanque1()));
    connect(ui->enable1, SIGNAL(clicked(bool)), this, SLOT(enabletanque2()));
    connect(ui->enable2, SIGNAL(clicked(bool)), this, SLOT(enabletanque3()));

//CAUDALES MAXIMOS
    connect(ui->CaudalIN0, SIGNAL(editingFinished()), this, SLOT(setcaudalIN0()));
    connect(ui->CaudalIN1, SIGNAL(editingFinished()), this, SLOT(setcaudalIN1()));
    connect(ui->caudalout1, SIGNAL(editingFinished()), this, SLOT(setcaudalmaxmedio()));
    connect(ui->caudalout2, SIGNAL(editingFinished()), this, SLOT(setcaudalOUT2()));
    connect(ui->caudalout3, SIGNAL(editingFinished()), this, SLOT(setcaudalOUT3()));

//TIMER
    connect(&timer, SIGNAL(timeout()), this, SLOT(setniveltanque0()));
    connect(&timer, SIGNAL(timeout()), this, SLOT(setniveltanque1()));
    connect(&timer, SIGNAL(timeout()), this, SLOT(setniveltanque2()));
   // connect(&timer, SIGNAL(timeout()), this, SLOT(enabletanque2()));
    connect(&timer, SIGNAL(timeout()), this, SLOT(setniveltanque3()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Set capacidad maxima de los tanques
void MainWindow:: setcapacidadtanque0(){
    capacidad0 = ui->Capacidad0->text().toDouble();
    ui->Tanque0->setMaximum(capacidad0);
}
void MainWindow:: setcapacidadtanque1(){
    capacidad1 = ui->Capacidad1->text().toDouble();
    ui->tanque1->setMaximum(capacidad1);
}
void MainWindow:: setcapacidadtanque2(){
    capacidad2 = ui->capacidad2->text().toDouble();
    ui->Tanque2->setMaximum(capacidad2);
}
void MainWindow:: setcapacidadtanque3(){
    capacidad3 = ui->Capacidad3->text().toDouble();
    ui->Tanque3->setMaximum(capacidad3);
}

//Set caudales maximos de entrada
void MainWindow:: setcaudalIN0(){
    caudalmaxin0 = ui->CaudalIN0->text().toDouble();
    ui->Dial0->setMaximum(caudalmaxin0);
}
void MainWindow:: setcaudalIN1(){
    caudalmaxin1 = ui->CaudalIN1->text().toDouble();
    ui->Dial1->setMaximum(caudalmaxin1);
}

//Set caudales actuales de entrada
void MainWindow:: setcauactualIN0(){
    caudalactualIN0 = ui->Dial0->value();
    ui->display0->display(caudalactualIN0);
}
void MainWindow:: setcauactualIN1(){
    caudalactualIN1 = ui->Dial1->value();
    ui->Display1->display(caudalactualIN1);
}

//Set caudales maximos de salida
void MainWindow::setcaudalmaxmedio(){
    caudalmaxmedio = ui->caudalout1->text().toDouble();
    ui->Dial2->setMaximum(caudalmaxmedio);
}
void MainWindow:: setcaudalOUT2(){
    caudalmaxout2 = ui->caudalout2->text().toDouble();
    ui->Dial3->setMaximum(caudalmaxout2);
}
void MainWindow:: setcaudalOUT3(){
    caudalmaxout3 = ui->caudalout3->text().toDouble();
    ui->dial4->setMaximum(caudalmaxout3);
}

//Set caudales actuales de salida
void MainWindow:: setcauactualmedio(){
    caudalactualmedio = ui->Dial2->value();
    ui->display2->display(caudalactualmedio);
    enabletanque0();
    enabletanque1();
    enabletanque2();
    enabletanque3();
}
void MainWindow:: setcauactualOUT2(){
    cauactualout2 = ui->Dial3->value();
    ui->display3->display(cauactualout2);
}
void MainWindow:: setcauactualOUT3(){
    cauactualout3 = ui->dial4->value();
    ui->display4->display(cauactualout3);
}

//Enables
void MainWindow:: enabletanque0(){
    if(ui->enbprinc0->isChecked() && (nivelactual0 >= (10*capacidad0)/100.0)){
        ui->Dial0->setEnabled(true);
        if(ui->enbprinc1->isChecked() && (nivelactual1>(10*capacidad1)/100.0)){
            cauactualout0 = (caudalactualmedio/3600.0)/2.0;
        } else {
            cauactualout0 = caudalactualmedio/3600.0;
            ui->Dial1->setValue(0);
            ui->Dial1->setEnabled(false);
        }
    } else {
        cauactualout0 = 0.0;
        ui->Dial0->setValue(0);
        ui->Dial0->setEnabled(false);
    }
}
void MainWindow:: enabletanque1(){
    if(ui->enbprinc1->isChecked() && (nivelactual1 >= (10*capacidad1)/100.0)){
        ui->Dial1->setEnabled(true);
        if(ui->enbprinc0->isChecked() && (nivelactual0>(10*capacidad0)/100.0)){
            cauactualout1 = (caudalactualmedio/3600.0)/2.0;
        } else {
            cauactualout1 = caudalactualmedio/3600.0;
            ui->Dial0->setValue(0);
            ui->Dial0->setEnabled(false);
        }
    } else {
        cauactualout1 = 0.0;
        ui->Dial1->setValue(0);
        ui->Dial1->setEnabled(false);
    }
}

void MainWindow:: enabletanque2(){
    if(ui->enable1->isChecked()){
        if(nivelactual2<capacidad2){
            if((ui->enable2->isChecked()) && (nivelactual3<capacidad3)){
                caudalactualIN2 = (caudalactualmedio/3600.0)/2.0;
            } else {
                caudalactualIN2 = caudalactualmedio/3600.0;
            }
        } else {
            caudalactualIN2 = 0.0;
        }
    } else {
        caudalactualIN2 = 0.0;
        ui->Dial3->setValue(0);
        ui->Dial3->setEnabled(false);
    }
}
void MainWindow:: enabletanque3(){
    if(ui->enable2->isChecked()){
        if(nivelactual3<capacidad3){
            if((ui->enable1->isChecked()) && (nivelactual2<capacidad2)){
                caudalactualIN3 = (caudalactualmedio/3600.0)/2.0;
            } else {
                caudalactualIN3 = caudalactualmedio/3600.0;
            }
        } else {
            caudalactualIN3 = 0.0;
        }
    } else {
        caudalactualIN3 = 0.0;
        ui->dial4->setValue(0);
        ui->dial4->setEnabled(false);
    }
}

//Set niveles
void MainWindow:: setniveltanque0(){
    double auxiliar = nivelactual0 + (caudalactualIN0/3600.0) - cauactualout0;

    if(nivelactual0<((10*capacidad0)/100.0)){
        if(auxiliar<capacidad0){
            nivelactual0 = auxiliar;
        } else {
            nivelactual0 = capacidad0;
        }
    } else {
        if((auxiliar < capacidad0) && (auxiliar > (10*capacidad0)/100.0)){
            nivelactual0 = auxiliar;
        } else {
            if(auxiliar >= capacidad0){
                nivelactual0 = capacidad0;
            }
            if(auxiliar <= (10*capacidad0)/100.0) {
                nivelactual0 = (10*capacidad0)/100.0;
            }
        }
    }
    ui->Tanque0->setValue(nivelactual0);

    if((nivelactual0 < capacidad0) && ui->enbprinc0->isChecked()){
        ui->Dial0->setEnabled(true);
    } else {
        ui->Dial0->setValue(0);
        ui->Dial0->setEnabled(false);
    }
    if(((nivelactual1>((10*capacidad1)/100)) && ui->enbprinc1->isChecked()) || ((nivelactual0>((10*capacidad0)/100)) && ui->enbprinc0->isChecked())){
        if(((nivelactual2<capacidad2) && ui->enable1->isChecked()) || (((nivelactual3<capacidad3) && ui->enable2->isChecked()))){
            ui->Dial2->setEnabled(true);
        } else {
            ui->Dial2->setValue(0);
            ui->Dial2->setEnabled(false);
        }
    } else {
        ui->Dial2->setValue(0);
        ui->Dial2->setEnabled(false);
    }
}

void MainWindow:: setniveltanque1(){
    double auxiliar = nivelactual1 + (caudalactualIN1/3600.0) - cauactualout1;

    if(nivelactual1<((10*capacidad1)/100.0)){
        if(auxiliar<capacidad1){
            nivelactual1 = auxiliar;
        } else {
            nivelactual1 = capacidad1;
        }
    } else {
        if((auxiliar < capacidad1) && (auxiliar > (10*capacidad1)/100.0)){
            nivelactual1 = auxiliar;
        } else {
            if(auxiliar >= capacidad1){
                nivelactual1 = capacidad1;
            }
            if(auxiliar <= (10*capacidad1)/100.0) {
                nivelactual1 = (10*capacidad1)/100.0;
            }
        }
    }
    ui->tanque1->setValue(nivelactual1);

    if((nivelactual1 < capacidad1) && ui->enbprinc1->isChecked()){
        ui->Dial1->setEnabled(true);
    } else {
        ui->Dial1->setValue(0);
        ui->Dial1->setEnabled(false);
    }
    if(((nivelactual1>((10*capacidad1)/100)) && ui->enbprinc1->isChecked()) || ((nivelactual0>((10*capacidad0)/100)) && ui->enbprinc0->isChecked())){
        if(((nivelactual2<capacidad2) && ui->enable1->isChecked()) || (((nivelactual3<capacidad3) && ui->enable2->isChecked()))){
            ui->Dial2->setEnabled(true);
        } else {
            ui->Dial2->setValue(0);
            ui->Dial2->setEnabled(false);
        }
    } else {
        ui->Dial2->setValue(0);
        ui->Dial2->setEnabled(false);
    }
}

void MainWindow:: setniveltanque2(){
    if(ui->enable1->isChecked()){
        if(nivelactual2<capacidad2){
            if((ui->enable2->isChecked()) && (nivelactual3<capacidad3)){
                caudalactualIN2 = (caudalactualmedio/3600.0)/2.0;
            } else {
                caudalactualIN2 = caudalactualmedio/3600.0;
            }
        } else {
            caudalactualIN2 = 0.0;
        }
    } else {
        caudalactualIN2 = 0.0;
        ui->Dial3->setValue(0);
        ui->Dial3->setEnabled(false);
    }
    double auxiliar = nivelactual2 + caudalactualIN2 - (cauactualout2/3600.0);

    if(nivelactual2<((10*capacidad2)/100.0)){
        if(auxiliar<capacidad2){
            nivelactual2 = auxiliar;
        } else {
            nivelactual2 = capacidad2;
        }
    } else {
        if((auxiliar <= capacidad2) && (auxiliar>= (10*capacidad2)/100.0)){
            nivelactual2 = auxiliar;
        } else {
            if(auxiliar> capacidad2){
                nivelactual2 = capacidad2;
            }
            if(auxiliar < (10*capacidad2)/100.0) {
                nivelactual2 = (10*capacidad2)/100.0;
            }
        }
    }
    ui->Tanque2->setValue(nivelactual2);

    if(nivelactual2 == capacidad2){
        if((ui->enable2->isChecked() || nivelactual3<capacidad3) && (nivelactual1>((10*capacidad1)/100))){
            if(nivelactual1>((10*capacidad1)/100)){
                ui->Dial2->setEnabled(true);
            } else {
                ui->Dial2->setEnabled(false);
                ui->Dial2->setValue(0);
            }
        }
    }
    if(nivelactual2 > ((10*capacidad2)/100.0)){
        if(ui->enable1->isCheckable()){
            ui->Dial3->setEnabled(true);
        }
    } else {
        ui->Dial3->setValue(0);
        ui->Dial3->setEnabled(false);
    }
}

void MainWindow:: setniveltanque3(){
    double auxiliar = nivelactual3 + caudalactualIN3 - (cauactualout3/3600.0);

    if(nivelactual3<((10*capacidad3)/100.0)){
        if(auxiliar<capacidad3){
            nivelactual3 = auxiliar;
        } else {
            nivelactual3 = capacidad3;
        }
    } else {
        if((auxiliar <= capacidad3) && (auxiliar>= (10*capacidad3)/100.0)){
            nivelactual3 = auxiliar;
        } else {
            if(auxiliar> capacidad3){
                nivelactual3 = capacidad3;
            }
            if(auxiliar < (10*capacidad3)/100.0) {
                nivelactual3 = (10*capacidad3)/100.0;
            }
        }
    }
    ui->Tanque3->setValue(nivelactual3);

    if(nivelactual3 == capacidad3){
        if((ui->enable1->isChecked() || nivelactual2 < capacidad2) && (nivelactual1>((10*capacidad1)/100))){
            ui->Dial2->setEnabled(true);
        } else {
            ui->Dial2->setValue(0);
            ui->Dial2->setEnabled(false);
        }
    }
    if(nivelactual3 > ((10*capacidad3)/100.0)){
        if(ui->enable2->isCheckable()){
            ui->dial4->setEnabled(true);
        }
    } else {
        ui->dial4->setValue(0);
        ui->dial4->setEnabled(false);
    }
}
