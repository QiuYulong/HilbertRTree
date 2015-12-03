#ifndef HEAP_H
#define HEAP_H

#define MAX_HEAP_SIZE 1000000 // modified by Greg 01-11-02

class HeapEntry{
public:
	//NOTE: for every variable you add, remember to update the following functions:
	//copy
	//init_HeapEntry

	int dim;
	int level;
	int son1;
	int son2;
	int path[5];
	float key;  //entries will be sorted according to this
	float *bounces; 

	HeapEntry();
	HeapEntry( const HeapEntry& rOtherEntry );
	~HeapEntry();
	void init_HeapEntry(int _dim);
	const HeapEntry& operator = ( const HeapEntry& rOtherEntry );
};

class SortEntry{
public:
	bool operator() ( const HeapEntry* rEntry1, const HeapEntry* rEntry2 ) const{
		return rEntry1->key > rEntry2->key;
	}
};

typedef std::priority_queue< HeapEntry*, std::vector<HeapEntry*>, SortEntry > XxkHeap;

#endif
