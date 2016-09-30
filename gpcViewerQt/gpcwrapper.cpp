#include <Windows.h>
#include <gl/GLU.h>
#include "gpcwrapper.h"

gpcWrapper::gpcWrapper()
{
}

gpc_polygon* gpcWrapper::readPolygon(FILE *infile_ptr, int read_hole_flags)
{
    gpc_polygon* polygon = NULL;
    gpc_read_polygon(infile_ptr, read_hole_flags, polygon);
    return polygon;
}

FILE* gpcWrapper::writePolygon(FILE* outfile_ptr, int write_hole_flags, gpc_polygon *polygon)
{
    gpc_write_polygon(outfile_ptr, write_hole_flags, polygon);
    return outfile_ptr;
}

gpc_polygon* gpcWrapper::addContour(gpc_polygon *polygon, gpc_vertex_list *contour, int hole)
{
    gpc_add_contour(polygon, contour, hole);
    return polygon;
}

gpc_polygon* gpcWrapper::clipPolygon(gpc_op set_operation, gpc_polygon *subject_polygon, gpc_polygon *clip_polygon)
{
    gpc_polygon *result_polygon = NULL;
    gpc_polygon_clip(set_operation, subject_polygon, clip_polygon, result_polygon);
    return result_polygon;
}

gpc_tristrip* gpcWrapper::clipTristrip(gpc_op set_operation, gpc_polygon *subject_polygon, gpc_polygon *clip_polygon)
{
    gpc_tristrip* result_tristrip = NULL;
    gpc_tristrip_clip(set_operation, subject_polygon, clip_polygon, result_tristrip);
    return result_tristrip;
}

gpc_tristrip* gpcWrapper::Polygon2Tristrip(gpc_polygon *polygon)
{
    gpc_tristrip* result_tristrip = NULL;
    gpc_polygon_to_tristrip(polygon, result_tristrip);
    return result_tristrip;
}

void gpcWrapper::freePolygon(gpc_polygon *polygon)
{
    gpc_free_polygon(polygon);
}

void gpcWrapper::freeTristrip(gpc_tristrip* tristrip)
{
    gpc_free_tristrip(tristrip);
}

void gpcWrapper::drawVertices(gpc_polygon* polygon, double offset, gpcColor color)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3fv(color);
    glLineWidth(2.0);
    for (int c= 0; c < polygon->num_contours; c++)
    {
        for (int v= 0; v < polygon->contour[c].num_vertices; v++)
        {
            glBegin(GL_LINE_LOOP);
            glVertex2d(polygon->contour[c].vertex[v].x + offset,
                       polygon->contour[c].vertex[v].y);
            glVertex2d(polygon->contour[c].vertex[v].x,
                       polygon->contour[c].vertex[v].y + offset);
            glVertex2d(polygon->contour[c].vertex[v].x - offset,
                       polygon->contour[c].vertex[v].y);
            glVertex2d(polygon->contour[c].vertex[v].x,
                       polygon->contour[c].vertex[v].y - offset);
            glEnd();
        }
    }
    glLineWidth(1.0);
}

void gpcWrapper::drawTristrip(gpc_tristrip* tristrip, bool showStrips, gpcColor stripsColor, bool showTriangles, gpcColor tiangleColor)
{
    glClear(GL_COLOR_BUFFER_BIT);

    for (int s= 0; s < tristrip->num_strips; s++)
    {
        if (showStrips)
            glColor3fv(stripsColor);

        glBegin(GL_TRIANGLE_STRIP);
        for (int v= 0; v < tristrip->strip[s].num_vertices; v++)
            glVertex2d(tristrip->strip[s].vertex[v].x, tristrip->strip[s].vertex[v].y);
        glEnd();

        if (showTriangles)
        {
            glLineWidth(1.0);
            glColor3fv(tiangleColor);
            glBegin(GL_LINE_STRIP);
            for (int v= 0; v < tristrip->strip[s].num_vertices; v++)
                glVertex2d(tristrip->strip[s].vertex[v].x, tristrip->strip[s].vertex[v].y);
            glEnd();
        }
    }
}

void gpcWrapper::drawPolygon(gpc_polygon* polygon, gpcColor color)
{
    glColor3fv(color);

    for (int c= 0; c < polygon->num_contours; c++)
    {
        /* Draw holes using dashed lines */
        if (polygon->hole[c])
        {
            glLineStipple(1, 0x00FF);
            glEnable(GL_LINE_STIPPLE);
        }
        glBegin(GL_LINE_LOOP);
        for (int v= 0; v < polygon->contour[c].num_vertices; v++)
        {
            glVertex2d(polygon->contour[c].vertex[v].x,
                       polygon->contour[c].vertex[v].y);
        }
        glEnd();
        glDisable(GL_LINE_STIPPLE);
    }
}
