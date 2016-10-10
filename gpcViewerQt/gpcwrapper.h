#ifndef GPCWRAPPER_H
#define GPCWRAPPER_H

extern "C"
{
    #include <../gpcCore/gpc.h>
}

typedef const float gpcColor[];
const float WHITE[] = {0.0f, 0.0f, 0.0f};
const float BLACK[] = {1.0f, 1.0f, 1.0f};
const float RED[]   = {1.0f, 0.0f, 0.0f};
const float GREEN[] = {0.0f, 1.0f, 0.0f};
const float BLUE[]  = {0.0f, 0.0f, 1.0f};

enum gpcOperType
{
    ASubB = 0,
    BSubA = 1,
    XOR = 2,
    AND = 3,
    OR = 4
};

class gpcWrapper
{
public:
    gpcWrapper();

    static gpc_polygon* readPolygon(FILE *infile_ptr, int read_hole_flags);
    static FILE* writePolygon(FILE* outfile_ptr, int write_hole_flags, gpc_polygon *polygon);
    static gpc_polygon* addContour(gpc_polygon *polygon, gpc_vertex_list *contour, int hole);
    static gpc_polygon* clipPolygon(gpcOperType operType, gpc_polygon *subject_polygon, gpc_polygon *clip_polygon);
    static gpc_tristrip* clipTristrip(gpc_op set_operation, gpc_polygon *subject_polygon, gpc_polygon *clip_polygon);
    static gpc_tristrip* Polygon2Tristrip(gpc_polygon *polygon);
    static void freePolygon(gpc_polygon *polygon);
    static void freeTristrip(gpc_tristrip* tristrip);

    static void drawVertices(gpc_polygon* polygon, double offset, gpcColor color);
    static void drawTristrip(gpc_tristrip* tristrip, bool showStrips, gpcColor stripsColor, bool showTriangles, gpcColor tiangleColor);
    static void drawPolygon(gpc_polygon* polygon, gpcColor color);
};

#endif // GPCWRAPPER_H
