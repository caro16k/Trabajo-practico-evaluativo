#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    //CAPACIDADES MAXIMAS
    void setcapacidadtanque0();
    void setcapacidadtanque1();
    void setcapacidadtanque2();
    void setcapacidadtanque3();

    //NIVELES
    void setniveltanque0();
    void setniveltanque1();
    void setniveltanque2();
    void setniveltanque3();

    //CAUDALES MAXIMOS
    void setcaudalIN0();
    void setcaudalIN1();
    void setcaudalmaxmedio();
    void setcaudalOUT2();
    void setcaudalOUT3();

    //ENABLES
    void enabletanque0();
    void enabletanque1();
    void enabletanque2();
    void enabletanque3();

    //CAUDALES ACTUALES entrada
    void setcauactualIN0();
    void setcauactualIN1();

    //CAUDALES ACTUALES salida
    void setcauactualmedio();
    void setcauactualOUT2();
    void setcauactualOUT3();

private:
    Ui::MainWindow *ui;
    QTimer timer;
    double capacidad0 = 0;
    double capacidad1 = 0;
    double capacidad2 = 0;
    double capacidad3 = 0;

    double nivelactual0 = 0;
    double nivelactual1 = 0;
    double nivelactual2 = 0;
    double nivelactual3 = 0;

    double caudalmaxin0 = 0;
    double caudalmaxin1 = 0;

    double cauactualout0 = 0;
    double cauactualout1 = 0;

    double caudalactualmedio = 0;
    double cauactualout2 = 0;
    double cauactualout3 = 0;

    double caudalactualIN0 = 0;
    double caudalactualIN1 = 0;
    double caudalactualIN2 = 0;
    double caudalactualIN3 = 0;

    double caudalmaxmedio = 0;
    double caudalmaxout2 = 0;
    double caudalmaxout3 = 0;
};

#endif // MAINWINDOW_H
