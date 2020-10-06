#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets/QTableWidgetItem>
#include <QtWidgets/QDialog>
#include <QtWidgets/QStyleFactory>
#include <QLineEdit>
#include <QFileSystemModel>
#include <QFileDialog>

#include "ui_mainwindow.h"
#include "texteditor.h"
#include "emptywidget.h"
#include "Connecter.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
 Q_OBJECT

 public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_actionOpen_File_triggered();

    void on_actionOpen_Folder_triggered();

private:
    Ui::MainWindow *ui;
    QFileSystemModel *m_dirmodel;
};
#endif // MAINWINDOW_H
