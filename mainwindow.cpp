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
    //QMessageBox::Question(this, "kjljhbk", "kjhhj");

    QString inputText = ui->textEditInputText->toPlainText();
    //qDebug() << inputText;

    if (inputText.isEmpty())
    {
        QMessageBox::warning(this, "Предупреждение", "Пожалуйста, введите текст для отправки в программу.");
        return;
    }

    QString programPath = ui->comboBoxProgramPath->currentText();
    QProcess process(this);
    process.startDetached(programPath);

    this->hide();

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [=, &process]() mutable {
        if (inputText.isEmpty())
        {
            timer->stop();
            QMessageBox::information(this, "Успех", "Операция успешно выполнена.");
            this->show();
            return;
        };

        qDebug() << inputText;
        QString symbol = inputText.at(0);
        qDebug() << "1";
        process.write(symbol.toUtf8());
        qDebug() << "2";
        inputText.remove(0, 1);
    });

    timer->start(1000);
}

// void MainWindow::on_pushButtonCompleteTask_clicked()
// {
//     //QMessageBox::Question(this, "kjljhbk", "kjhhj");

//     QString inputText = ui->textEditInputText->toPlainText();
//     //qDebug() << inputText;

//     if (inputText.isEmpty())
//     {
//         QMessageBox::warning(this, "Предупреждение", "Пожалуйста, введите текст для отправки в программу.");
//         return;
//     }

//     QString programPath = ui->comboBoxProgramPath->currentText();
//     QProcess process(this);
//     process.startDetached(programPath);

//     this->hide();

//     QTimer *timer = new QTimer(this);
//     timer->setInterval(1000);
//     connect(timer, &QTimer::timeout, this, [&]() {
//         qDebug() << "ПРИВЕТ!";
//         qDebug() << programPath;
//         qDebug() << inputText;
//         qDebug() << "ПРИВЕмпролждТ!";
//         //qDebug() << inputText.length() <<" " << !inputText.length();
//         if (inputText.isEmpty())
//         {
//             process.closeWriteChannel();
//             QMessageBox::information(this, "Успех", "Операция успешно выполнена.");
//             timer->stop();
//             delete timer;
//             return;
//         }

//         qDebug() << "хуй";

//         QChar symbol = inputText.at(0);
//         qDebug() << "хуй1";

//         process.write("DFGHJKL");
//         qDebug() << "хуй2";

//         inputText.erase(inputText.cbegin());
//     });

//     //timer->start(1);
//     //process.waitForFinished(-1);

//     this->show();
//     //QMessageBox::Icon(this, "kdhjh", "jhjhhjb");
// }

// void MainWindow::on_pushButtonCompleteTask_clicked()
// {
//     //QMessageBox::Question(this, "kjljhbk", "kjhhj");

//     inputText = ui->textEditInputText->toPlainText();

//     if (inputText.isEmpty())
//     {
//         QMessageBox::warning(this, "Предупреждение", "Пожалуйста, введите текст для отправки в программу.");
//         return;
//     }

//     QString programPath = ui->comboBoxProgramPath->currentText();
//     QProcess process(this);
//     process.startDetached(programPath);

//     this->hide();

//     QTimer *timer = new QTimer(this);
//     //timer->start(1000);
//     connect(timer, &QTimer::timeout, this, [&process, timer, this]() {
//         qDebug() << inputText;
//         qDebug() << inputText.length() <<" " << !inputText.length();
//         if (!inputText.length())
//         {
//             process.closeWriteChannel();
//             QMessageBox::information(this, "Успех", "Операция успешно выполнена.");
//             timer->stop();
//             delete timer;
//             return;
//         }

//         qDebug() << "хуй";

//         QString symbol = inputText.at(0);
//         qDebug() << "хуй1";

//         process.write("R");
//         qDebug() << "хуй2";

//         inputText.erase(inputText.cbegin());
//     });

//     timer->start(1);
//     //process.waitForFinished(-1);

//     this->show();


//     //QMessageBox::Icon(this, "kdhjh", "jhjhhjb");
// }

// void MainWindow::on_pushButtonCompleteTask_clicked()
// {
//     //QMessageBox::Question(this, "kjljhbk", "kjhhj");
//     try{
//     QString inputText = ui->textEditInputText->toPlainText();

//     if (inputText.isEmpty())
//     {
//         QMessageBox::warning(this, "Предупреждение", "Пожалуйста, введите текст для отправки в программу.");
//         return;
//     }

//     QString programPath = ui->comboBoxProgramPath->currentText();
//     QProcess process(this);
//     process.startDetached(programPath);

//     this->hide();

//     QTimer *timer = new QTimer(this);
//     size_t currentIndex = 0;
//     connect(timer, &QTimer::timeout, [=, &process, &timer, &currentIndex, &inputText]() {
//         if (currentIndex == inputText.length())
//         {
//             process.closeWriteChannel();
//             QMessageBox::information(this, "Успех", "Операция успешно выполнена.");
//             timer->stop();
//             delete timer;
//             return;
//         }

//         QString symbol = inputText.at(currentIndex);

//         process.write(symbol.toUtf8());

//         currentIndex += 1;
//     });

//     timer->start(1000);

//     //process.waitForFinished(-1);

//     this->show();
//     } catch (std::exception ex){
//         qDebug() << ex.what();
//     }


//     //QMessageBox::Icon(this, "kdhjh", "jhjhhjb");
// }

