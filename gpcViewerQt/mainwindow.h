#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <stdio.h>
#include <QMainWindow>
#include <QtOpenGL/QGLWidget>
#include "gpcglwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    gpcGLWidget* glWidget;
};

#endif // MAINWINDOW_H
