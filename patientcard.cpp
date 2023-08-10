#include "patientcard.h"
#include "ui_patientcard.h"

PatientCard::PatientCard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PatientCard)
{
    ui->setupUi(this);
    mapper = new QDataWidgetMapper(this);

}

PatientCard::~PatientCard()
{
    delete ui;
}

void PatientCard::setModel(QSqlRelationalTableModel *model)
{
    mapper->setModel(model);

    ui->doctorBox->setModel(model->relationModel(1));
    mapper->addMapping(ui->doctorBox,1);

    ui->patientBox->setModel(model->relationModel(2));
    mapper->addMapping(ui->patientBox,2);


    mapper->addMapping(ui->resdateEdit,3);
    mapper->addMapping(ui->ifsEdit,4);
    mapper->addMapping(ui->ageEdit,5);
    mapper->addMapping(ui->diagEdit,6);
    mapper->addMapping(ui->memoEdit,7);
    mapper->addMapping(ui->istbolEdit,9);
}

void PatientCard::on_saveButton_clicked()
{
    //mapper->submit();
    mapper->submit();

}


void PatientCard::on_closeButton_clicked()
{
    close();
}

