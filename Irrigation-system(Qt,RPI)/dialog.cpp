#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    QTimer *timer = new QTimer(this);

    connect(timer, &QTimer::timeout, this, &Dialog::rain_sensor);
    connect(timer, &QTimer::timeout, this, &Dialog::light_sensor);
    connect(timer, &QTimer::timeout, this, &Dialog::time);
    timer -> start(1000);

     pinMode(21, OUTPUT);
     pinMode (0, OUTPUT) ;
     ui->label_3->setNum(max_rainfall);

     series_1 = new QLineSeries();
     series_2 = new QLineSeries();
     series_3 = new QLineSeries();

     QChart *chart_1 = new QChart();
     chart_1->legend()->hide();
     chart_1->addSeries(series_1);
    chart_1->createDefaultAxes();

     chart_1->axisX()->setRange(0, 360); //seconds
     chart_1->axisY()->setRange(0, 100); //rainfall intensity percentage

     chart_1->setTitle("Rainfall intensity in 5 minutes [ l/m^2 ]");

     QChartView *chartView_1 = new QChartView(chart_1);
     chartView_1->setRenderHint(QPainter::Antialiasing);

     ui->verticalLayout_1->addWidget(chartView_1);


     //counter_1 = 0;

     QChart *chart_2 = new QChart();
     chart_2->legend()->hide();
     chart_2->addSeries(series_2);
    chart_2->createDefaultAxes();

     chart_2->axisX()->setRange(0, 2);
     chart_2->axisY()->setRange(0, 100);

     chart_2->setTitle("Rainfall [ l ]"); //Rainfall total


     QChartView *chartView_2 = new QChartView(chart_2);
     chartView_2->setRenderHint(QPainter::Antialiasing);

     ui->verticalLayout_2->addWidget(chartView_2);

     QChart *chart_3 = new QChart();
     chart_3->legend()->hide();
     chart_3->addSeries(series_3);
    chart_3->createDefaultAxes();

     chart_3->axisX()->setRange(0, 2);
     chart_3->axisY()->setRange(0, 100);

     chart_3->setTitle("Light [ lux ]"); //Light total


     QChartView *chartView_3= new QChartView(chart_3);
     chartView_3->setRenderHint(QPainter::Antialiasing);

     ui->verticalLayout_3->addWidget(chartView_3);




}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::rain_sensor()
{
    wiringPiI2CReadReg8(fd, PCF8591 + 1);
    adc_val_1 = wiringPiI2CReadReg8(fd, PCF8591 + 1);
    rain =qFabs(( (adc_val_1)*100/248)-100) ;

    if( counter_1 == 0 ) {
       series_1->clear();
    }

    series_1 -> append(counter_1, rain);

    counter_1 =( counter_1+1 )%360;

    rainfall_count+=rain*0.1; //Counting the rainfall

    series_2 -> append(1, rainfall_count); //Updating the graph

    if(rainfall_count>max_rainfall)
    {
        servo();
    }

}

void Dialog::light_sensor()
{
    wiringPiI2CReadReg8(fd, PCF8591 + 0);
    adc_val_2 = wiringPiI2CReadReg8(fd, PCF8591 + 0);
   // light =qFabs(( (adc_val_2-100)*100/140)-100) ;
light=qFabs(( (adc_val_2)*100/256)-100) ;


    light_count+=light*0.1;   //Counting light
    series_3 -> append(1, light_count); //Updating the graph



}

void Dialog::servo()
{

    digitalWrite (0, HIGH) ; delay (500) ; // Turn on servo motor
    digitalWrite (0,  LOW) ; delay (500) ;


    series_1->clear();  // Clear all displayed data
    series_2->clear();
    series_3->clear();

    rainfall_count=0;   //Clear all displayed data
    light_count=0;
    counter_1=0;
    max_rainfall=help_var;



    QMessageBox msgBox;
    msgBox.setText("System irrigation is disabled. Click OK to enable irrigation again.");
    msgBox.exec();


}







void Dialog::time()
{
    QTime time = QTime::currentTime();
    QString text = time.toString("hh : mm : ss"); // Time counter

    ui->label1->setText(text);
}

void Dialog::on_pushButton_clicked()
{
max_rainfall=help_var;
 ui->label_3->setNum(max_rainfall);
}

void Dialog::on_lineEdit_textEdited(const QString &arg1)
{
    QString txt=ui->lineEdit->text();
    help_var=txt.toInt();


}
