#ifndef __MYHILBERT
#define __MYHILBERT

typedef unsigned long long bitmask_t;

bitmask_t cal_hilbert(int _num_bit, int _dim, float *_coord, float _umax);
bitmask_t cal_hilbert_mbr(int _num_bit, int _dim, float *_mbr, float _umax);

#endif
