struct HE_vert
{
  float x,y,z;//×ø±ê
  float nx,ny,nz;//·¨Ïß
  struct HE_edge *edge;
};
struct HE_edge
{
   struct HE_vert* vert;
   struct HE_edge* pair;
   struct HE_face* face;
   struct HE_edge* prev;
   struct HE_edge* next;
};
struct HE_face
{
   struct HE_edge* edge;
};