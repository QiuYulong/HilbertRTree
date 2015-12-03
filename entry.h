#ifndef __Entry 
#define __Entry

//header files
#include "rtree.h"
#include "rtnode.h"
#include "linlist.h"
#include "gendef.h"

class Entry {
public:

	int son;
	float *bounces;
	int dimension;                      
	int level;
    RTree *my_tree;                     
    RTNode *son_ptr;                    
   
	Entry();
	Entry(int dimension, RTree *rt);
	Entry(const Entry& e);
    ~Entry();

	void del_son();
	Linkable *gen_Linkable();
	int get_size(); 
	RTNode *get_son();
	void init_entry(int _dimension, RTree *_rt);
	void read_from_buffer(char *buffer);
    SECTION section(float *mbr);
	bool section_circle(float *center, float radius);
	void set_from_Linkable(Linkable *link);
    void write_to_buffer(char *buffer);
    virtual Entry & operator = (Entry &_d);
	bool operator == (Entry &_d);
};

#endif
