#include <QtOpenGL>
#include <GL/glu.h>
#include "gpcglwidget.h"

gpcGLWidget::gpcGLWidget(QWidget *parent) :
    QGLWidget(parent)
{
}

void gpcGLWidget::initializeGL()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);
}

void gpcGLWidget::resizeGL(int w, int h)
{
   glViewport(0, 0, w, h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(45.0, w/h, 0.1, 100.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

void gpcGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(-2.0, 0.0, -6.0);

    //draw polygon
    gpcWrapper::drawPolygon(mSubject_polygon, RED);
    gpcWrapper::drawPolygon(mClip_polygon, GREEN);
    gpcWrapper::drawPolygon(mResult_polygon, BLUE);
}

void gpcGLWidget::loadGPCData()
{
    FILE *sfp = fopen("D:\\git\\gpcViewer\\gpcFile\\britain.gpf", "r");
    FILE *cfp = fopen("D:\\git\\gpcViewer\\gpcFile\\arrows.gpf", "r");
    if(sfp != NULL)
        mSubject_polygon = gpcWrapper::readPolygon(sfp, 1);
    if(cfp != NULL)
        mClip_polygon = gpcWrapper::readPolygon(cfp, 1);
}

gpc_polygon* gpcGLWidget::operatePolygon(gpc_op set_operation)
{
    mResult_polygon = gpcWrapper::clipPolygon(set_operation, mSubject_polygon, mClip_polygon);
    return mResult_polygon;
}
