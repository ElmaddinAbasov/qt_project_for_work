#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void MainWindow::run_program()
{
 //   qDebug() << "void MainWindow::run_program()";
   // f_xor_mod.rrun();
}

MainWindow::~MainWindow()
{
    delete ui;
    f_xor_mod.~file_xor_mod();
}

void MainWindow::on_pushButton_clicked()
{
    QString file_ext = ui->lineEdit->text();
    f_xor_mod.set_file_name(file_ext);
}


void MainWindow::on_pushButton_2_clicked()
{
    QString flag = ui->lineEdit_2->text();
    f_xor_mod.set_delete_input_files_flag(flag == "yes" ? 1 : 0);
}


void MainWindow::on_pushButton_3_clicked()
{
    QString path = ui->lineEdit_3->text();
    f_xor_mod.set_path(path);
}


void MainWindow::on_pushButton_4_clicked()
{
    QString act = ui->lineEdit_4->text();
    f_xor_mod.set_action(act);
}


void MainWindow::on_pushButton_5_clicked()
{   
    QString timer = ui->lineEdit_5->text();
#if 0
    f_xor_mod.set_timer(QTime::fromString(timer));
#else
    f_xor_mod.set_timer(timer.toInt());
#endif
}


void MainWindow::on_pushButton_6_clicked()
{
    QString p_t = ui->lineEdit_6->text();
    f_xor_mod.set_poll_timer(p_t.toInt());
}


void MainWindow::on_pushButton_7_clicked()
{
    QString var = ui->lineEdit_7->text();
    f_xor_mod.set_variable(var);
}


void MainWindow::on_pushButton_8_clicked()
{
    f_xor_mod.rrun();
    hide();
    sleep(f_xor_mod.get_poll_seconds());
    show();
}



void MainWindow::on_pushButton_9_clicked()
{
    close();
}

