#include<QtDebug>
#include<QChar>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    patientCard = new PatientCard();
    patientCard->setParent(this,Qt::Window);
    scene = new QGraphicsScene(ui->graphicsView);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::udateView()
{
    model = new QSqlRelationalTableModel(this,DBConn.db);
    model->setTable("RESEARCH");
    model->setRelation(1, QSqlRelation("DOCTORS", "NAME", "NAME"));
    model->setRelation(2, QSqlRelation("PATIENTS", "NAME", "NAME"));

    if (!model->select()) {
        showError(model->lastError());
        return;
    }

    ui->ViewList->setModel(model);
    ui->ViewList->setColumnHidden(0, true);
    ui->ViewList->setColumnHidden(4, true);
    ui->ViewList->setColumnHidden(5, true);
    ui->ViewList->setColumnHidden(6, true);
    ui->ViewList->setColumnHidden(7, true);
    ui->ViewList->setColumnHidden(8, true);


    patientCard->setModel(model);
    ui->graphicsView->setScene(scene);
}

void MainWindow::showError(const QSqlError &err)
{
    QMessageBox::critical(this, "Unable to initialize Database",
                "Error initializing database: " + err.text());
}

void MainWindow::on_actionConnect_triggered()
{
    QSqlError err = DBConn.openDB();
    if (err.type() != QSqlError::NoError)
        statusBar()->showMessage(err.text());
    else
    {
        statusBar()->showMessage("Connected");
        udateView();
    }
}

void MainWindow::on_ViewList_doubleClicked(const QModelIndex &index)
{
   patientCard->mapper->setCurrentModelIndex(index);
   patientCard->show();
}


void MainWindow::on_ViewList_clicked(const QModelIndex &index)
{
    currentRow = index.row();
    scene->clear();

   QPen pen(Qt::green);
   scene->addLine(0,0,0,255,pen);
   scene->addLine(0,255,510,255,pen);

   QPen pen2(Qt::red);
   int x1 = 0, y1= 0, y2= 0;
   QByteArray arr = model->data(model->index(index.row(), 8), Qt::DisplayRole).toByteArray();
       for (int i = 0; i < arr.size(); ++i) {

           unsigned char sim = arr.at(i);
           y2 = sim;
           if(i>0){
               scene->addLine(x1,255-y1,i*5,255-y2,pen2);
           }
           x1=i*5; y1=y2;
   }
}

void MainWindow::on_addButton_clicked()
{
    model->insertRows(model->rowCount(),1);
    currentRow = model->rowCount()-1;
    patientCard->mapper->setCurrentModelIndex(model->index(currentRow,2));
    patientCard->mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    patientCard->show();
}


void MainWindow::on_delButton_clicked()
{
    model->removeRow(currentRow);
    model->select();
}

