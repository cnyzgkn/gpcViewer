#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    glWidget = new gpcGLWidget(this);
    setCentralWidget(glWidget);

    glWidget->loadGPCData();
    glWidget->operatePolygon(GPC_DIFF);

    glWidget->updateGL();
    glWidget->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
