
#include "hrtree_headers.h"

HeapEntry::HeapEntry(){
	bounces=NULL;
	dim=-1;
};

HeapEntry::HeapEntry( const HeapEntry& rOtherEntry ){
	dim = rOtherEntry.dim;
	bounces = new float[2 * dim];
	memcpy( bounces, rOtherEntry.bounces, 2 * dim * sizeof( float ) );
}
HeapEntry::~HeapEntry(){
	if (bounces != NULL)
		delete[] bounces;	
}
void HeapEntry::init_HeapEntry(int _dim){
	if (_dim < 0)
		error("The dimensionality of the entry is negative.\n", true);
	dim = _dim;
	bounces=new float[2 * _dim];
}

const HeapEntry& HeapEntry::operator = ( const HeapEntry& rOtherEntry ){
	if (dim != rOtherEntry.dim){
		if (bounces != NULL)
			delete []bounces;
		dim = rOtherEntry.dim;
		bounces = new float[2 * dim];
		}
	memcpy( bounces, rOtherEntry.bounces, 2 * dim * sizeof( float ) );
	return *this;
}
