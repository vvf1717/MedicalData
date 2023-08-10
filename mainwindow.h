#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QSqlRelationalTableModel>
#include <QSqlRelationalDelegate>
#include <QSqlRelation>
#include "dbconnection.h"
#include "patientcard.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    DbConnection DBConn;
    void udateView();
    void showError(const QSqlError &err);
    QSqlRelationalTableModel* model;

private slots:
    void on_actionConnect_triggered();

    void on_ViewList_doubleClicked(const QModelIndex &index);

    void on_ViewList_clicked(const QModelIndex &index);

    void on_addButton_clicked();

    void on_delButton_clicked();

private:
    Ui::MainWindow *ui;
    PatientCard *patientCard;
    QGraphicsScene *scene;
    int currentRow;
};
#endif // MAINWINDOW_H
