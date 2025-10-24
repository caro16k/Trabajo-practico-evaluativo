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
    //CAPACIDADES
    void setcapacidadtanque1();
    void setcapacidadtanque2();
    void setcapacidadtanque3();

    //NIVELES
    void setniveltanque1();
    void setniveltanque2();
    void setniveltanque3();

    //CAUDALES
    void setcaudalIN1();
    void setcaudalOUT1();
    void setcaudalOUT2();
    void setcaudalOUT3();

    //CAUDALES ACTUALES entrada
    void setcauactualIN1();
    void enabletanque2();
    void enabletanque3();

    //CAUDALES ACTUALES salida
    void setcauactualOUT1();
    void setcauactualOUT2();
    void setcauactualOUT3();

private:
    Ui::MainWindow *ui;
    QTimer timer;
    double capacidad1 = 0;
    double capacidad2 = 0;
    double capacidad3 = 0;

    double nivelactual1 = 0;
    double nivelactual2 = 0;
    double nivelactual3 = 0;

    double caudalin1 = 0;

    double cauactualout1 = 0;
    double cauactualout2 = 0;
    double cauactualout3 = 0;

    double caudalactualIN1 = 0;
    double caudalactualIN2 = 0;
    double caudalactualIN3 = 0;

    double caudalout1 = 0;
    double caudalout2 = 0;
    double caudalout3 = 0;
};

#endif // MAINWINDOW_H
