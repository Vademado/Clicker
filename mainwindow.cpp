#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>>
#include <QProcess>
#include <QMessageBox>
#include <QTimer>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    addProgramPath("C:/Windows/notepad.exe");
}

void MainWindow::addProgramPath(const QString & path)
{
    ui->comboBoxProgramPath->addItem(path);
    if (!path.isEmpty()) ui->comboBoxProgramPath->setCurrentText(path);
    //qDebug() << ui->comboBoxProgramPath->currentText(); // Debug
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonSelectApplication_clicked()
{
    QString programPath = QFileDialog::getOpenFileName(this, "Выберите приложение", QDir::homePath(), "Приложения (*.exe)");
    addProgramPath(programPath);
    //qDebug() << programPath; // Debug
}


void MainWindow::on_pushButtonCompleteTask_clicked()
{
    QString inputText = ui->textEditInputText->toPlainText();

    if (inputText.isEmpty())
    {
        QMessageBox::warning(this, "Предупреждение", "Пожалуйста, введите текст для отправки в программу.");
        return;
    }

    QString programPath = ui->comboBoxProgramPath->currentText();
    QProcess *process = new QProcess(this);
    process->setProcessChannelMode(QProcess::ForwardedChannels);
    process->start(programPath);

    this->hide();

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [=]() mutable {
        if (inputText.isEmpty())
        {
            timer->stop();
            QMessageBox::information(this, "Успех", "Операция успешно выполнена.");
            this->show();
            return;
        }

        QString symbol = inputText.at(0);
        qDebug() << symbol;
        process->write(symbol.toUtf8());
        process->waitForBytesWritten(-1);
        inputText.remove(0, 1);
    });

    timer->start(1000);
}
