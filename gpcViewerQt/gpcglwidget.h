#ifndef GPCGLWIDGET_H
#define GPCGLWIDGET_H

#include <QtOpenGL/QGLWidget>
#include "gpcwrapper.h"

class gpcGLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit gpcGLWidget(QWidget *parent = 0);
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void loadGPCData();
    gpc_polygon* operatePolygon(gpc_op set_operation);

signals:

public slots:

private:
    gpc_polygon* mSubject_polygon;
    gpc_polygon* mClip_polygon;
    gpc_polygon* mResult_polygon;
};

#endif // GPCGLWIDGET_H
