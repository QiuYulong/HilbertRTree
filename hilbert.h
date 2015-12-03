#if !defined(_hilbert_h_)
#define _hilbert_h_

#ifdef __cplusplus
extern "C" {
#endif

//typedef unsigned __int64 bitmask_t;
typedef unsigned long long bitmask_t;
typedef unsigned long halfmask_t;

void hilbert_i2c(unsigned nDims, unsigned nBits, bitmask_t index, bitmask_t coord[]);
bitmask_t hilbert_c2i(unsigned nDims, unsigned nBits, bitmask_t const coord[]);
int hilbert_cmp(unsigned nDims, unsigned nBytes, unsigned nBits, void const* coord1, void const* coord2);
int hilbert_ieee_cmp(unsigned nDims, double const* coord1, double const* coord2);
unsigned hilbert_box_vtx(unsigned nDims, unsigned nBytes, unsigned nBits, int findMin, void* c1, void* c2);
unsigned hilbert_ieee_box_vtx(unsigned nDims, int findMin, double* c1, double* c2);
unsigned hilbert_box_pt(unsigned nDims, unsigned nBytes, unsigned nBits, int findMin, void* coord1, void* coord2);
unsigned hilbert_ieee_box_pt(unsigned nDims, int findMin, double* c1, double* c2);
int hilbert_nextinbox(unsigned nDims, unsigned nBytes, unsigned nBits, int findPrev, void* coord1, void* coord2, void const* point);
void hilbert_incr(unsigned nDims, unsigned nBits, bitmask_t coord[]);

#ifdef __cplusplus
}
#endif

#endif

