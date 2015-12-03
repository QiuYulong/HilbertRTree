/*
header files set.
include this header file to include all Hilbert RTree related headers.
*/
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include <map>
#include <queue>
#include <bitset>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <climits>
#include <cfloat>


#include <stdint.h>
#include <memory.h>

#include <boost/filesystem/operations.hpp>
#include <boost/program_options.hpp>

using namespace std;

using namespace boost::filesystem;
namespace po = boost::program_options;

// rtree
#include "global.h"
#include "gendef.h"
#include "linlist.h"
#include "heap.h"
#include "rand.h"
#include "myhilbert.h"
#include "hilbert.h"
#include "blk_file.h"
#include "cache.h"
#include "rtree.h"
#include "rtnode.h"
#include "entry.h"
