#ifndef __GENERAL_DEFINITION
#define __GENERAL_DEFINITION


typedef unsigned int uint;

//----BlockFile, CachedBlockFile, Cache---------------------
#define BFHEAD_LENGTH (sizeof(int)*2)    //file header size

#define TRUE 1
#define FALSE 0

#define MDOM 0
#define DOM 1 

#define SEEK_CUR 1
#define SEEK_SET 0
#define SEEK_END 2

typedef char Block[];
//-------------------All-------------------------------------
#define MAXREAL         (float)1e20
#define FLOATZERO       (float)1e-7
#define MAX_DIMENSION   (float)256

#define DIMENSION 10

#define TRUE 1
#define FALSE 0

//#define min(a, b) (((a) < (b))? (a) : (b)  )
//#define max(a, b) (((a) > (b))? (a) : (b)  )

#define MAXSKY 10000000 // by Greg
//-------------------Class and other data types--------------
class BlockFile;  //for BlockFile definition
class Cache;
class Cacheable   //inherit this class if you wish to design an external
                  //memory structure that can be cached
{
public:
	BlockFile *file;
	Cache *cache;
};
 
class CmdIntrpr{  //this is the class of command interpretor.  for a new rtree decescendent
                  //inherit this class to obtain tailored command interpretor
public:
	int cnfrm_cmd(char *_msg){
		char c = ' ';
		while (c != 'N' && c != 'Y'){
			printf("%s (y/n)?", _msg);
			c = getchar(); 
			char tmp;
			while ((tmp = getchar()) != '\n');
			c = toupper(c); 
		}
		if (c == 'N') return 0; else return 1; 
	}
  
	void get_cmd(char *_msg, char *_cmd){
		printf("%s", _msg);  
		char *c = _cmd;
		while (((*c) = getchar()) != '\n')
			c++;
		*c = '\0'; 
	} 

	virtual bool build_tree(char *_tree_fname, char *_data_fname, int _b_len, int _dim, int _csize) = 0;
	virtual void free_tree() = 0;
	virtual int qry_sngle(float *_mbr, int *_io_count) = 0;
	virtual void run() = 0;
	virtual void version() = 0;
};
  
enum SECTION {OVERLAP, INSIDE, S_NONE};
enum R_OVERFLOW {SPLIT, REINSERT, NONE};
enum R_DELETE {NOTFOUND,NORMAL,ERASED};
typedef float *floatptr;
  
struct SortMbr{
    int dimension;
    float *mbr;
    float *center;
    int index;
};

struct SortTuple{
	int id;
	int dimension;
	float score;
    float *bounces;
};

struct BranchList{
    int entry_number;
    float mindist;
    float minmaxdist;
    bool section;
};




#endif
