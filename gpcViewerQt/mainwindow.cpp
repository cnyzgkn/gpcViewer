#include <QFileDialog>
#include <QSignalMapper>
#include <QCheckBox>
#include <QWidgetAction>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //add checkboxes to menu
    //geometry A
    QCheckBox* checkboxA = new QCheckBox("Show Geometry A (Red)", ui->menuView_V);
    checkboxA->setChecked(true);
    QWidgetAction *checkBoxActionA= new QWidgetAction(ui->menuView_V);
    checkBoxActionA->setDefaultWidget(checkboxA);
    ui->menuView_V->addAction(checkBoxActionA);
    //geometry B
    QCheckBox* checkboxB = new QCheckBox("Show Geometry B (Green)", ui->menuView_V);
    checkboxB->setChecked(true);
    QWidgetAction *checkBoxActionB= new QWidgetAction(ui->menuView_V);
    checkBoxActionB->setDefaultWidget(checkboxB);
    ui->menuView_V->addAction(checkBoxActionB);
    //geometry Result
    QCheckBox* checkboxResult = new QCheckBox("Show Geometry Result (Blue)", ui->menuView_V);
    checkboxResult->setChecked(true);
    QWidgetAction *checkBoxActionResult= new QWidgetAction(ui->menuView_V);
    checkBoxActionResult->setDefaultWidget(checkboxResult);
    ui->menuView_V->addAction(checkBoxActionResult);

    //openGL
    glWidget = new gpcGLWidget(this);
    setCentralWidget(glWidget);

    //connect signals
    //File
    QObject::connect(ui->actionFileOpen_O, SIGNAL(triggered()), glWidget, SLOT(loadGPCData()));
    QObject::connect(ui->actionSave_File_S, SIGNAL(triggered()), glWidget, SLOT(writeGPCData()));
    QObject::connect(ui->actionFileClose_W, SIGNAL(triggered()), glWidget, SLOT(closeAndRedraw()));

    //checkbox
    QObject::connect(checkboxA, SIGNAL(toggled(bool)), glWidget, SLOT(setShowSubject(bool)));
    QObject::connect(checkboxB, SIGNAL(toggled(bool)), glWidget, SLOT(setShowClip(bool)));
    QObject::connect(checkboxResult, SIGNAL(toggled(bool)), glWidget, SLOT(setShowResult(bool)));

    //geoemtry operation
    //use a map for enum
    qRegisterMetaType<gpcOperType>("gpcOperType");
    QSignalMapper* signalMapper = new QSignalMapper(this);
    QObject::connect(ui->actionA_B, SIGNAL(triggered()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->actionA_B, "ASubB");
    QObject::connect(ui->actionB_A, SIGNAL(triggered()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->actionB_A, "BSubA");
    QObject::connect(ui->actionXOR, SIGNAL(triggered()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->actionXOR, "XOR");
    QObject::connect(ui->actionAND, SIGNAL(triggered()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->actionAND, "AND");
    QObject::connect(ui->actionOR,  SIGNAL(triggered()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->actionOR, "OR");
    QObject::connect(signalMapper, SIGNAL(mapped(const QString&)), glWidget, SLOT(operPolygonAndRedraw(const QString&)));

    glWidget->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::getOpenFileName()
{
    return QFileDialog::getOpenFileName(this, "open file", QDir::currentPath(),"Files (*.gpf *.txt)");
}

QString MainWindow::getSaveFileName()
{
    return QFileDialog::getSaveFileName(this, "save file", QDir::currentPath(),"Files (*.gpf)");
}
