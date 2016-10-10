#ifndef GPCGLWIDGET_H
#define GPCGLWIDGET_H

#include <QtOpenGL/QGLWidget>
#include "gpcwrapper.h"

enum poly_type
{
    A_subj,
    B_clip,
    C_result
};

class gpcGLWidget : public QGLWidget
{
    Q_OBJECT
    Q_ENUMS(gpcOperType)

public:
    explicit gpcGLWidget(QWidget *parent = 0);
    ~gpcGLWidget();

    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

signals:

public slots:
    void loadGPCData();
    void writeGPCData();
    void closeAndRedraw();
    void operPolygonAndRedraw(const QString&);

    void setShowSubject(bool value);
    void setShowClip(bool value);
    void setShowResult(bool value);

private:
    void freeAllPolygons();
    gpc_polygon* operatePolygon(gpcOperType operType);

private:
    gpc_polygon* mSubject_polygon;
    gpc_polygon* mClip_polygon;
    gpc_polygon* mResult_polygon;

    bool bShowSubject;
    bool bShowClip;
    bool bShowResult;
};

#endif // GPCGLWIDGET_H
