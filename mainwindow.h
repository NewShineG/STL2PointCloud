#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QProgressDialog>
#include <QSettings>

#include "stl2pointCloud.h"

#define SETTINGSPATH "./settings.ini"

#if defined(_MSC_VER) && (_MSC_VER >= 1600)
# pragma execution_character_set("utf-8")
#endif

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

	QSettings settings;
	QString filePath;

    Stl2pointCould s2pd = Stl2pointCould();
    int BMPwidth = 1080;
    int BMPlength= 1920;
    double BMPpitchX = 0.114;
    double BMPpitchY = 0.114;
private slots:
    void on_readSTLButton_clicked();

    void on_toPointCloudButton_clicked();

    void on_toTXTButton_clicked();

    void on_toBMPButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
