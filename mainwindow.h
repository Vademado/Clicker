#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void addProgramPath(const QString &);
    ~MainWindow();

private slots:
    void on_pushButtonSelectApplication_clicked();

    void on_pushButtonCompleteTask_clicked();

    void on_pushButtonSelectFile_clicked();

    void on_pushButton_clicked();

    // void onTimerTimeout();

    // void onProcessStarted();

private:
    Ui::MainWindow *ui;
    // QTimer *timer;
    // QProcess *previousProcess;
    // QString inputText;
    // QString filePath;
    // QString programPath;

};
#endif // MAINWINDOW_H
