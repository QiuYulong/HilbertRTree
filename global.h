class RTNode;
class Entry;

int existsInList(int n, vector<int> &List);
void eraseElement(int n, vector<int> &List);
void mergeSets(map<int, int>&, map<int, int>&);



void error(string errmsg, bool _terminate);
float area(int dimension, float *mbr);
float margin(int dimension, float *mbr);
float overlap(int dimension, float *r1, float *r2);
float* overlapRect(int dimension, float *r1, float *r2);
float* overlapRect_dynamic(int dimension, float *r1, float *r2, bool *func); // by Greg
float objectDIST(float *p1, float *p2);
float MINMAXDIST(float *Point, float *bounces);
float MINDIST(float *Point, float *bounces);
float MAXDIST(float *p, float *bounces, int dim);
float MbrMINDIST(float *_m1, float *_m2, int _dim);
float MbrMAXDIST(float *_m1, float *_m2, int _dim);
float mindist(float *p, float *bounces, int dimension, float *bound); // by Greg
float mindist_dynamic(float *p, float *bounces, int dimension, float *bound, bool *func); // by Greg
float minmaxdist(float *Point, float *bounces, int dimension, float *bound); // by Greg
float minmaxdist_dynamic(float *p, float *bounces, int dimension, float *bound, bool *func); // by Greg
bool inside(float &p, float &lb, float &ub);
void enlarge(int dimension, float **mbr, float *r1, float *r2);
bool inside(float *v, float *mbr, int dimension);
bool mbr_inside(float *mbr1, float *mbr2, int dimension); // by Greg
bool mbr_inside_dynamic(float *mbr1, float *mbr2, int dimension, bool *func); // by Greg
bool point_inside_mbr(float *p, float *mbr2, int dimension); // by Greg
bool boundedFound(float *bounces, float *bound, int dimension); // by Greg
bool boundedFound_dynamic(float *bounces, float *bound, int dimension, bool *func); // by Greg
bool cornerFound(float *bounces, float *bound, int dimension); //by Greg
void printTime(long elapsed); // by Greg
int pruneBrunchList(float *nearest_distanz, const void *activebrunchList, int n);
int boundedpruneBrunchList(float *nearest_distanz, const void *activebrunchList, int n); // by Greg
float* overlapRectPt(int dimension, float *r1, float *r2); // by Greg
bool section(int dimension, float *mbr1, float *mbr2);
bool section_dynamic(int dimension, float *mbr1, float *mbr2, bool *func); // by Greg
bool section_c(int dimension, float *mbr1, float *center, float radius);
int sort_lower_mbr(const void *d1, const void *d2);
int sort_upper_mbr(const void *d1, const void *d2);
int sort_center_mbr(const void *d1, const void *d2);
int sortmindist(const void *element1, const void *element2);
int sort_tuple_score(const void *d1, const void *d2); // by Greg

#ifdef UNIX
void strupr(char *_msg);
#endif



float* mindis_point(float *p, float *bounces, int _dim);
float mindist_value(float *p, float *mbb, int dim);

