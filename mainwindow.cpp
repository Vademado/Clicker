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

// void MainWindow::printTextInNotepad(const QString& text)
// {
//     // Запускаем блокнот
//     system("C:/Windows/notepad.exe");

//     // Ждем немного, чтобы убедиться, что блокнот полностью открыт
//     Sleep(1000);

//     // Преобразуем текст в последовательность символов wchar_t
//     const wchar_t* wideText = reinterpret_cast<const wchar_t*>(text.utf16());

//     // Открываем окно блокнота
//     HWND notepadWindow = FindWindow(NULL, L"Безымянный — Блокнот");
//     if (notepadWindow == NULL)
//     {
//         QMessageBox::critical(nullptr, "Ошибка", "Не удалось найти окно блокнота.");
//         return;
//     }
//     SetForegroundWindow(notepadWindow);

//     // Передаем текст в блокнот
//     for (int i = 0; i < text.size(); ++i)
//     {
//         // Печатаем символ в блокноте
//         SendMessage(notepadWindow, WM_CHAR, wideText[i], 0);
//         // Подождем немного, чтобы эмулировать реальную скорость печати
//         Sleep(50);
//     }
// }

// void MainWindow::on_pushButtonCompleteTask_clicked()
// {
//     QString inputText = ui->textEditInputText->toPlainText();

//     if (inputText.isEmpty())
//     {
//         QMessageBox::warning(this, "Предупреждение", "Пожалуйста, введите текст для отправки в программу.");
//         return;
//     }

//     printTextInNotepad(inputText);

//     QMessageBox::information(this, "Успех", "Операция успешно выполнена.");
// }

// void MainWindow::on_pushButtonCompleteTask_clicked()
// {
//     QString inputText = ui->textEditInputText->toPlainText();

//     if (inputText.isEmpty())
//     {
//         QMessageBox::warning(this, "Предупреждение", "Пожалуйста, введите текст для отправки в программу.");
//         return;
//     }

//     QString filePath = QCoreApplication::applicationDirPath() + "/example.txt"; // Путь к файлу

//     qDebug() << filePath;

//     QFile file(filePath);
//     if (!file.open(QIODevice::WriteOnly | QIODevice::Append))
//     {
//         QMessageBox::critical(this, "Ошибка", "Не удалось создать файл.");
//         return;
//     }

//     QTextStream out(&file);

//     //out << "HEY";

//     file.close();

//     QStringList arguments;
//     arguments << filePath;

//     QString programPath = ui->comboBoxProgramPath->currentText();
//     QProcess *process = new QProcess(this);
//     //process->setProcessChannelMode(QProcess::ForwardedChannels);
//     process->start(programPath, arguments);

//     this->hide();

//     QTimer *timer = new QTimer(this);
//     connect(timer, &QTimer::timeout, this, [=]() mutable {
//         if (inputText.isEmpty())
//         {
//             timer->stop();
//             //process->closeWriteChannel();
//             QMessageBox::information(this, "Успех", "Операция успешно выполнена.");
//             this->show();
//             delete timer;
//             delete process;
//             return;
//         }
//         QString symbol = inputText.at(0);
//         qDebug() << symbol;
//         out << symbol;
//         //process->waitForBytesWritten(-1);
//         inputText.remove(0, 1);
//     });

//     timer->start(1000);
// }

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

        QFile::copy(filePath, filePath); // Обновление отображения файла

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

