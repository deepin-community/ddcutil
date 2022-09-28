#define HELLO 123
typedef struct
{
  double x;
  double y;
  double z;
  char *label;
} point_t;

// Creation, printing and deletion
point_t* createPoint(double x, double y, double z, char *label);
void printPoint(point_t *point);
void deletePoint(point_t *point);

// Mathematical transformations
void extendPoint(point_t *point, double scalar, char mode);
void rotatePoint(point_t *point, char axis, double deg);
void translatePoint(point_t *point, char axis, double dist);
