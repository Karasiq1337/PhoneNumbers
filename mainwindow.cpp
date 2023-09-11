#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./phoneNumbers.db");
    if(db.open()){qDebug("Connected to DB");}
    query = new QSqlQuery(db);
    query -> exec("CREATE TABLE PhoneNumbers('Имя' TEXT, 'Фамилия' TEXT, 'Номер телефона' INT8)");

    tableModel = new QSqlTableModel(this, db);
    tableModel -> setTable("PhoneNumbers");
    tableModel -> select();

    ui->tableView->setModel(tableModel);


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    tableModel -> insertRow(tableModel -> rowCount());
}

void MainWindow::on_pushButton_2_clicked()
{
    tableModel -> removeRow(clicedRow);
    tableModel -> select();
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    clicedRow = index.row();
}
