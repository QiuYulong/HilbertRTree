#ifndef __RTNODE
#define __RTNODE

#include "gendef.h"
class SortedLinList;
class Entry;
class RTree;
class Heap;

class RTNode{
public:
	char level;
	int block;//RTNode block number on disk
	int num_entries;
	Entry *entries;

	bool dirty;
	int capacity;
    int dimension;
	RTree *my_tree;  

	RTNode(RTree *rt);
    RTNode(RTree *rt, int _block);
    ~RTNode();

    int choose_subtree(float *brm);
	R_DELETE delete_entry(Entry *e); //enum R_DELETE {NOTFOUND,NORMAL,ERASED};
	void enter(Entry *de);
	bool FindLeaf(Entry *e);
	float *get_mbr();
	int get_num_of_data();
	R_OVERFLOW insert(Entry *d, RTNode **sn);//enum R_OVERFLOW {SPLIT, REINSERT, NONE};
	bool is_data_node() { return (level==0) ? TRUE : FALSE ;};
	void NNSearch(float *QueryPoint, SortedLinList *res, float *nearest_distanz);
	void boundedNNSearch(float *QueryPoint, SortedLinList *res, float *bound, float *nearest_distanz);
	void print();
	int rangeQuery(float *mbr);
    void read_from_buffer(char *buffer);
	int split(float **mbr, int **distribution);
	void split(RTNode *sn);
	void write_to_buffer(char *buffer); 
	void rank_qry_inquiry(float *_weight, float _qscore, int *_rslt);
	bool skyline_mbr_inside_tree(float *mbr, int *dc);
	int countQuery(float *mbr);
	void boundedNNSearch_dynamic(float *QueryPoint, SortedLinList *res, float *bound, float *nearest_distanz, bool *func);
	void traverse(float *_skyarray, float *_skydomcnt, int _skyarrayused);
	bool main_memory_dom_check(int _k, float *_pt, int &_domcnt); 
};

#endif
