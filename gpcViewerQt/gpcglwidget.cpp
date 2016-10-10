#include <QtOpenGL>
#include <GL/glu.h>
#include "gpcglwidget.h"
#include "mainwindow.h"

gpcGLWidget::gpcGLWidget(QWidget *parent) :
    QGLWidget(parent), mSubject_polygon(NULL), mClip_polygon(NULL), mResult_polygon(NULL),
    bShowSubject(true), bShowClip(true), bShowResult(true)
{
}

gpcGLWidget::~gpcGLWidget()
{
    freeAllPolygons();
}

void gpcGLWidget::setShowSubject(bool value)
{
    bShowSubject = value;
    updateGL();
}

void gpcGLWidget::setShowClip(bool value)
{
    bShowClip = value;
    updateGL();
}

void gpcGLWidget::setShowResult(bool value)
{
    bShowResult = value;
    updateGL();
}

void gpcGLWidget::freeAllPolygons()
{
    if(mSubject_polygon)
    {
        gpcWrapper::freePolygon(mSubject_polygon);
        mSubject_polygon = NULL;
    }
    if(mClip_polygon)
    {
        gpcWrapper::freePolygon(mClip_polygon);
        mClip_polygon = NULL;
    }
    if(mResult_polygon)
    {
        gpcWrapper::freePolygon(mResult_polygon);
        mResult_polygon = NULL;
    }
}

void gpcGLWidget::closeAndRedraw()
{
    freeAllPolygons();
    updateGL();
}

void gpcGLWidget::initializeGL()
{
    glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBlendFunc(GL_ONE, GL_ONE);

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);
}

void gpcGLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, (GLint)w, (GLint)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(120.0, (GLfloat)w/(GLfloat)h, 1.0, 1000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void gpcGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -100.0);

    //draw polygon
    if(mSubject_polygon && bShowSubject)
        gpcWrapper::drawPolygon(mSubject_polygon, RED);
    if(mClip_polygon && bShowClip)
        gpcWrapper::drawPolygon(mClip_polygon, GREEN);
    if(mResult_polygon && bShowResult)
        gpcWrapper::drawPolygon(mResult_polygon, BLUE);
}

void gpcGLWidget::loadGPCData()
{
    if(mSubject_polygon == NULL)
    {
        QMessageBox msgBox;
        msgBox.setText("Load geometry A");
        msgBox.exec();
    }else if (mClip_polygon == NULL)
    {
        QMessageBox msgBox;
        msgBox.setText("Load geometry B");
        msgBox.exec();
    }else
    {
        QMessageBox msgBox;
        msgBox.setText("Please select \"Close File\" than reload");
        msgBox.exec();
        return;
    }

    MainWindow* parent = dynamic_cast<MainWindow*>(parentWidget());
    QString fileName = parent->getOpenFileName();
    FILE *fp = fopen(qPrintable(fileName), "r");
    if(fp != NULL)
    {
        if(mSubject_polygon == NULL)
            mSubject_polygon = gpcWrapper::readPolygon(fp, 1);
        else if (mClip_polygon == NULL)
            mClip_polygon = gpcWrapper::readPolygon(fp, 1);
    }

    return;
}

void gpcGLWidget::writeGPCData()
{
    if(mResult_polygon == NULL)
    {
        QMessageBox msgBox;
        msgBox.setText("No result polygon to save!");
        msgBox.exec();
    }else
    {
        MainWindow* parent = dynamic_cast<MainWindow*>(parentWidget());
        QString fileName = parent->getSaveFileName();
        FILE *fp = fopen(qPrintable(fileName), "w");
        gpcWrapper::writePolygon(fp, 1, mResult_polygon);
    }

    return;
}

gpc_polygon* gpcGLWidget::operatePolygon(gpcOperType operType)
{
    if(mResult_polygon)
        gpcWrapper::freePolygon(mResult_polygon);
    mResult_polygon = gpcWrapper::clipPolygon(operType, mSubject_polygon, mClip_polygon);
    return mResult_polygon;
}

void gpcGLWidget::operPolygonAndRedraw(const QString& str)
{
    if(str == "ASubB")
        operatePolygon(ASubB);
    else if (str == "BSubA")
        operatePolygon(BSubA);
    else if (str == "XOR")
        operatePolygon(XOR);
    else if (str == "AND")
        operatePolygon(AND);
    else if (str == "(OR)")
        operatePolygon(OR);

    updateGL();
}
