#ifndef PATIENTCARD_H
#define PATIENTCARD_H

#include <QWidget>
#include <QDataWidgetMapper>
#include <QSqlRelationalDelegate>

namespace Ui {
class PatientCard;
}

class PatientCard : public QWidget
{
    Q_OBJECT

public:
    explicit PatientCard(QWidget *parent = nullptr);
    ~PatientCard();
    void setModel(QSqlRelationalTableModel *model);
    QDataWidgetMapper* mapper;
private slots:
    void on_saveButton_clicked();

    void on_closeButton_clicked();

private:
    Ui::PatientCard *ui;

};

#endif // PATIENTCARD_H
