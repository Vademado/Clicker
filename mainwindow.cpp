#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QProcess>
#include <QMessageBox>
#include <QTimer>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Clicker");
    this->setWindowIcon(QIcon("E:/LaboratoryWorks_IU8/HomeWork_2_02/Clicker/icon.png"));
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
    QString filePath = ui->lineEditFilePath->text();
    QString programPath = ui->comboBoxProgramPath->currentText();

    if (inputText.isEmpty() || filePath.isEmpty())
    {
        QMessageBox::warning(this, "Предупреждение", inputText.isEmpty() ? "Пожалуйста, введите текст для отправки в программу." : "Пожалуйста, выберете файл для записи.");
        return;
    }

    this->hide();

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [=]() mutable {
        if (inputText.isEmpty())
        {
            timer->stop();
            QMessageBox::information(this, "Успех", "Операция успешно выполнена.");
            this->show();
            delete timer;
            return;
        }

        QString symbol = inputText.at(0);

        QFile file(filePath);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Append))
        {
            QMessageBox::critical(this, "Ошибка", "Не удалось открыть файл для дозаписи.");
            return;
        }

        QTextStream out(&file);
        out << symbol;
        file.close();
        QProcess *process = new QProcess(this);
        process->setProcessChannelMode(QProcess::ForwardedChannels);
        process->start(programPath, {filePath});

        connect(process, &QProcess::finished, process, &QProcess::deleteLater);

        QFile::copy(filePath, filePath);

        inputText.remove(0, 1);
    });

    timer->start(1000);
}


void MainWindow::on_pushButtonSelectFile_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Выберите приложение", QDir::homePath(), "Текстовые файлы (*.txt)");
    ui->lineEditFilePath->setText(filePath);
}


void MainWindow::on_pushButton_clicked()
{
    QMessageBox::information(this, "Справка", "Инструкция:\n"
                                              "1) Выберете приложение в котором будет открыт текстовый файл.\n"
                                              "2) Нажмите кнопку \"Выбрать приложение\"\n"
                                              "3) В поле для ввода текста введите текст. Нажмите кнопку \"Выполнить задачу\"\n"
                                              "4) Выберите файл в который будет записываться текст, "
                                              "для этого пропишите абсолюный путь к файлу или нажмите на кнопку \"Выбрать файл\"");
}












































// MainWindow::MainWindow(QWidget *parent)
//     : QMainWindow(parent)
//     , ui(new Ui::MainWindow)
// {
//     ui->setupUi(this);
//     this->setWindowTitle("Clicker");
//     this->setWindowIcon(QIcon("E:/LaboratoryWorks_IU8/HomeWork_2_02/Clicker/icon.png"));
//     addProgramPath("C:/Windows/notepad.exe");
//     timer = new QTimer(this);
//     previousProcess = new QProcess(this);
// }

// void MainWindow::addProgramPath(const QString & path)
// {
//     ui->comboBoxProgramPath->addItem(path);
//     if (!path.isEmpty()) ui->comboBoxProgramPath->setCurrentText(path);
//     //qDebug() << ui->comboBoxProgramPath->currentText(); // Debug
// }

// MainWindow::~MainWindow()
// {
//     delete ui;
//     delete timer;
//     delete previousProcess;
// }

// void MainWindow::on_pushButtonSelectApplication_clicked()
// {
//     QString programPath = QFileDialog::getOpenFileName(this, "Выберите приложение", QDir::homePath(), "Приложения (*.exe)");
//     addProgramPath(programPath);
//     //qDebug() << programPath; // Debug
// }

// void MainWindow::on_pushButtonCompleteTask_clicked()
// {
//     inputText = ui->textEditInputText->toPlainText();
//     filePath = ui->lineEditFilePath->text();
//     programPath = ui->comboBoxProgramPath->currentText();

//     if (inputText.isEmpty() || filePath.isEmpty())
//     {
//         QMessageBox::warning(this, "Предупреждение", inputText.isEmpty() ? "Пожалуйста, введите текст для отправки в программу." : "Пожалуйста, выберете файл для записи.");
//         return;
//     }

//     if (timer->isActive())
//         timer->stop();
//     if (previousProcess->state() == QProcess::Running)
//         previousProcess->kill();

//     this->hide();

//     connect(timer, &QTimer::timeout, this, &MainWindow::onTimerTimeout);
//     timer->start(1000);
// }

// void MainWindow::onTimerTimeout()
// {
//     if (inputText.isEmpty())
//     {
//         timer->stop();
//         QMessageBox::information(this, "Успех", "Операция успешно выполнена.");
//         this->show();
//         return;
//     }

//     QString symbol = inputText.at(0);

//     QFile file(filePath);
//     if (!file.open(QIODevice::WriteOnly | QIODevice::Append))
//     {
//         QMessageBox::critical(this, "Ошибка", "Не удалось открыть файл для дозаписи.");
//         return;
//     }

//     QTextStream out(&file);
//     out << symbol;
//     qDebug() << symbol;
//     file.close();

//     QProcess *process = new QProcess(this);
//     process->setProcessChannelMode(QProcess::ForwardedChannels);
//     connect(process, &QProcess::started, this, &MainWindow::onProcessStarted);
//     process->start(programPath, {filePath});
// }

// void MainWindow::onProcessStarted()
// {
//     if (previousProcess->state() == QProcess::Running)
//     {
//         previousProcess->kill();
//         delete previousProcess;
//     }
//     previousProcess = qobject_cast<QProcess*>(sender());
// }



// void MainWindow::on_pushButtonSelectFile_clicked()
// {
//     QString filePath = QFileDialog::getOpenFileName(this, "Выберите приложение", QDir::homePath(), "Текстовые файлы (*.txt)");
//     ui->lineEditFilePath->setText(filePath);
// }


// void MainWindow::on_pushButton_clicked()
// {
//     QMessageBox::information(this, "Справка", "Инструкция:\n"
//                                               "1) Выберете приложение в котором будет открыт текстовый файл.\n"
//                                               "2) Нажмите кнопку \"Выбрать приложение\"\n"
//                                               "3) В поле для ввода текста введите текст. Нажмите кнопку \"Выполнить задачу\"\n"
//                                               "4) Выберите файл в который будет записываться текст, "
//                                               "для этого пропишите абсолюный путь к файлу или нажмите на кнопку \"Выбрать файл\"");
// }
