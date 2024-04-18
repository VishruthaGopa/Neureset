#include "sliderwindow.h"
#include "ui_sliderwindow.h"
#include <QMessageBox>
#include <QGraphicsProxyWidget>

SliderWindow::SliderWindow(QVector<Electrode*> electrodesIN,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SliderWindow),
    currentElectrodeIndex(0),
    electrodes(electrodesIN),
    showingBeforeWaveform(true)
{
    ui->setupUi(this);
    connect(ui->nextButton, &QPushButton::clicked, this, &SliderWindow::showNextElectrode);
    connect(ui->prevButton, &QPushButton::clicked, this, &SliderWindow::showPrevElectrode);
    showElectrode(currentElectrodeIndex);
}

SliderWindow::~SliderWindow()
{
    delete ui;
}

void SliderWindow::showElectrode(int index)
{
   if (index >= 0 && index < electrodes.size()) {
       currentElectrodeIndex = index;
       QString mystring = "Electrode: " + QString::number(index + 1);
       if (showingBeforeWaveform==true) {
           mystring += " before";
       } else {
           mystring += " after";
       }
       ui->electrodeLabel->setText(mystring);

       QtCharts::QChartView* chartView = electrodes[index]->plotWaveform(showingBeforeWaveform);
       QGraphicsProxyWidget* proxy = new QGraphicsProxyWidget;
       proxy->setWidget(chartView);

       QGraphicsScene* scene = new QGraphicsScene;
       scene->addItem(proxy);
       ui->graphicsView->setScene(scene);
   }
}


void SliderWindow::showNextElectrode()
{
    if(!showingBeforeWaveform){
       if (currentElectrodeIndex < electrodes.size() - 1) {
           currentElectrodeIndex++;
       } else {
           currentElectrodeIndex = 0;
       }
    }
   showingBeforeWaveform = !showingBeforeWaveform;
   showElectrode(currentElectrodeIndex);
}

void SliderWindow::showPrevElectrode()
{
    if(showingBeforeWaveform){
       if (currentElectrodeIndex > 0) {
           currentElectrodeIndex--;
       } else {
           currentElectrodeIndex = electrodes.size() - 1;
       }
    }
   showingBeforeWaveform = !showingBeforeWaveform;
   showElectrode(currentElectrodeIndex);
}
