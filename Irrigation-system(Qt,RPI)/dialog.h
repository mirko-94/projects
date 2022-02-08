#ifndef DIALOG_H
#define DIALOG_H

#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QBarSeries>
#include <QBarSet>
#include <QtMath>
#include <QDialog>
#include <QtCharts/QLineSeries>
#include <QWidget>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <stdio.h>
#include <QtGlobal>
#include <stdlib.h>
#include <QtCharts/QChartView>
#include <QTimer>
#include <QTime>
#include <QDateTime>
#include <QProgressBar>
#include <QSpinBox>
#include <QDebug>
#include <QMessageBox>

using namespace QtCharts;



namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    const char PCF8591 = 0x48; // adress
    int fd = wiringPiI2CSetup(PCF8591);

    int counter_1=1, counter_2=0;
    int adc_val_1=0,adc_val_2, rain, light, light_count=0;
    int rainfall_count=0, max_rainfall=90, help_var=0;

    QLineSeries *series_1;
    QLineSeries *series_2;
    QLineSeries *series_3;


    ~Dialog();

    private slots:
    void rain_sensor();
    void light_sensor();
    void servo();
    void time();

    void on_pushButton_clicked();

    void on_lineEdit_textEdited(const QString &arg1);

private:
    Ui::Dialog *ui;
     QTimer *timer1;
};

#endif // DIALOG_H
