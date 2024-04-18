#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
