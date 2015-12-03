
#include "hrtree_headers.h"

int existsInList(int n, vector<int> &List){
	if (List.size()==0)
		return -1;
	for(unsigned int i=0; i<List.size(); i++)
		if(List[i]==n)
			return i;
	return -1;
}

void eraseElement(int n, vector<int> &List){
	int index = existsInList(n, List);
	if(index!=-1) // if n does exist in L
		List.erase(List.begin()+index);
}


void mergeSets(map<int, int> &S1, map<int, int> &S2){
	if(S2.size()==0) 
		return;
	for( map<int,int>::iterator ii=S2.begin(); ii!=S2.end(); ++ii)
       S1[(*ii).first] = (*ii).first;
}

//-------------------------------------------------


#ifdef UNIX
void strupr(char *_msg)
{
	int dist = 'A' - 'a';
	char *c_ptr = _msg;

	while (*c_ptr)
	{
		if (*c_ptr >= 'a')
			*c_ptr += dist;
		c_ptr ++;
	}
}
#endif

//void error(char *t, bool ex){
//    fprintf(stderr, t);
//    if (ex)
//        exit(0);
//}

void error(string msg, bool ex){
    cerr << msg;
    if (ex)
        exit(0);
}

float area(int dimension, float *mbr){
    int i;
    float sum;

    sum = 1.0;
    for (i = 0; i < dimension; i++)
	sum *= mbr[2*i+1] - mbr[2*i];

    return sum;
}

float margin(int dimension, float *mbr){
    float *ml, *mu, *m_last, sum;

    sum = 0.0;
    m_last = mbr + 2*dimension;
    ml = mbr;
    mu = ml + 1;
    while (mu < m_last){
		sum += *mu - *ml;
		ml += 2;
		mu += 2;
    }

    return sum;
}

bool inside(float &p, float &lb, float &ub){
    return (p >= lb && p <= ub);
}

bool inside(float *v, float *mbr, int dimension){
    int i;

    for (i = 0; i < dimension; i++)
	if (!inside(v[i], mbr[2*i], mbr[2*i+1]))
	    return FALSE;

    return TRUE;
}

bool mbr_inside(float *mbr1, float *mbr2, int dimension){
	int i;
	for (i = 0; i < dimension; i++)
		if (!(inside(mbr1[2*i], mbr2[2*i], mbr2[2*i+1]) && inside(mbr1[2*i+1], mbr2[2*i], mbr2[2*i+1])))
			return false;

	return true;
}

bool point_inside_mbr(float *p, float *mbr, int dimension){
	int i;
	for (i = 0; i < dimension; i++)
		if (!(inside(p[i], mbr[2*i], mbr[2*i+1])))
			return false;
	return true;
}

void printTime(long elapsed){
	int hr, min, sec, ms;
	ms = (int)elapsed%1000;
	elapsed = (elapsed - ms)/1000;
	sec = (int)elapsed%60;
	elapsed = (elapsed - sec)/60;
	min = (int)elapsed%60;
	hr = (elapsed - min)/60;
	printf("%3d hrs %2d mins %2d secs %3d millisecs\n", hr, min, sec, ms);
}

float* overlapRect(int dimension, float *r1, float *r2){
        float *overlap = new float[2*dimension];
        for (int i=0; i<dimension; i++){
            if ((r1[i*2]>r2[i*2+1]) || (r1[i*2+1]<r2[i*2])){
                delete [] overlap;
				return NULL;
			}
			overlap[2*i] = max(r1[i*2], r2[i*2]);
            overlap[2*i+1] = min(r1[i*2+1], r2[i*2+1]);
        }

        return overlap;
}

// calcutales the "bottom left corner" of the overlapping rectangle between r1 and r2
// if rects do not overlap returns null
float* overlapRectPt(int dimension, float *r1, float *r2){
        float *overlap = new float[dimension];
        for (int i=0; i<dimension; i++){
			if ((r1[i*2]>r2[i*2+1]) || (r1[i*2+1]<r2[i*2])){ // non overlapping
                delete [] overlap;
				return NULL;
			}
			overlap[i] = max(r1[i*2], r2[i*2]);
        }

        return overlap;
}

float overlap(int dimension, float *r1, float *r2){
// calcutales the overlapping area of r1 and r2
// calculate overlap in every dimension and multiplicate the values
    float sum;
    float *r1pos, *r2pos, *r1last, r1_lb, r1_ub, r2_lb, r2_ub;

    sum = 1.0;
    r1pos = r1; r2pos = r2;
    r1last = r1 + 2 * dimension;

    while (r1pos < r1last){
		r1_lb = *(r1pos++);
		r1_ub = *(r1pos++);
		r2_lb = *(r2pos++);
		r2_ub = *(r2pos++);

		if (inside(r1_ub, r2_lb, r2_ub)){
			if (inside(r1_lb, r2_lb, r2_ub))
				sum *= (r1_ub - r1_lb);
			else
				sum *= (r1_ub - r2_lb);
		}
		else{
			if (inside(r1_lb, r2_lb, r2_ub))
				sum *= (r2_ub - r1_lb);
			else 
				if (inside(r2_lb, r1_lb, r1_ub) && inside(r2_ub, r1_lb, r1_ub))
					sum *= (r2_ub - r2_lb);
				else
					sum = 0.0;
		}
	}

    return sum;
}

void enlarge(int dimension, float **mbr, float *r1, float *r2){
// enlarge r in a way that it contains s
    int i;

    *mbr = new float[2*dimension];
    for (i = 0; i < 2*dimension; i += 2){
		(*mbr)[i]   = min(r1[i],   r2[i]);
		(*mbr)[i+1] = max(r1[i+1], r2[i+1]);
    }
}

bool section(int dimension, float *mbr1, float *mbr2){
    int i;

    for (i = 0; i < dimension; i++){
		if (mbr1[2*i] > mbr2[2*i + 1] || mbr1[2*i + 1] < mbr2[2*i]) 
			return FALSE;
    }
    return TRUE;
}

bool section_c(int dimension, float *mbr1, float *center, float radius){
	float r2;
	r2 = radius * radius;

	if ( (r2 - MINDIST(center,mbr1)) < 1.0e-8)
		return TRUE;
	else
		return FALSE;
}

int sort_lower_mbr(const void *d1, const void *d2){
    SortMbr *s1, *s2;
    float erg;
    int dimension;

    s1 = (SortMbr *) d1;
    s2 = (SortMbr *) d2;
    dimension = s1->dimension;
    erg = s1->mbr[2*dimension] - s2->mbr[2*dimension];
    if (erg < 0.0)
	return -1;
    else if (erg == 0.0)
	return 0;
    else 
	return 1;
}

int sort_upper_mbr(const void *d1, const void *d2){
    SortMbr *s1, *s2;
    float erg;
    int dimension;

    s1 = (SortMbr *) d1;
    s2 = (SortMbr *) d2;
    dimension = s1->dimension;
    erg = s1->mbr[2*dimension+1] - s2->mbr[2*dimension+1];
    if (erg < 0.0)
	return -1;
    else if (erg == 0.0)
	return 0;
    else 
	return 1;
}

int sort_center_mbr(const void *d1, const void *d2){
    SortMbr *s1, *s2;
    int i, dimension;
    float d, e1, e2;

    s1 = (SortMbr *) d1;
    s2 = (SortMbr *) d2;
    dimension = s1->dimension;

    e1 = e2 = 0.0;
    for (i = 0; i < dimension; i++){
        d = (float)((s1->mbr[2*i] + s1->mbr[2*i+1]) / 2.0) - s1->center[i];
        e1 += d*d;
        d = (float)((s2->mbr[2*i] + s2->mbr[2*i+1]) / 2.0) - s2->center[i];
        e2 += d*d;
    }

    if (e1 < e2)
	return -1;
    else if (e1 == e2)
	return 0;
    else 
	return 1;
}

int sortmindist(const void *element1, const void *element2){
	//The consequence of this sorting is that active branches are sorted
	//in acsending order of their mindist.
    BranchList *e1,*e2;

    e1 = (BranchList *) element1;
    e2 = (BranchList *) element2;
    
    if (e1->mindist < e2->mindist) 
	return(-1);
    else if (e1->mindist > e2->mindist)
	return(1);
    else
	return(0);
}

int pruneBrunchList(float *nearest_distanz, const void *activebrunchList, int n){
    BranchList *bl; 
    int i,j, aktlast;

    bl = (BranchList *) activebrunchList;
    aktlast = n;
 
    for( i = 0; i < aktlast ; i++ ){
		if (bl[i].minmaxdist < bl[aktlast-1].mindist)
			//bl[aktlast-1] is the maximum mindist of all the branches 
			//if this condition holds, it implies that there exist some branches whose
			//mindists are greater than minmandist of this branch. in the sequel, all these
			//branches will be removed from further consideration. 
			for( j = 0; (j < aktlast) ; j++ )
				if ((i!=j) && (bl[j].mindist>bl[i].minmaxdist)){
				aktlast = j;				
				if (j <= i)
					error("Error in pruneBrunchList\n", true);
				break;
				}
	}

    for( i = 0; i < aktlast; i++)
		if (*nearest_distanz > bl[i].minmaxdist)
			*nearest_distanz = bl[i].minmaxdist;

    for( i = 0; (i < aktlast) && (*nearest_distanz >= bl[i].mindist) ; i++);    
    aktlast = i;

    return (aktlast);
}

int boundedpruneBrunchList(float *nearest_distanz, const void *activebrunchList, int n){
    BranchList *bl;     
    int i,j, aktlast;
    
    bl = (BranchList *) activebrunchList;
    aktlast = n;

    for( i = 0; i < aktlast ; i++ ){
		if (bl[i].minmaxdist < bl[aktlast-1].mindist)
			//bl[aktlast-1] is the maximum mindist of all the branches 
			//if this condition holds, it implies that there exist some branches whose
			//mindists are greater than minmandist of this branch. in the sequel, all these
			//branches will be removed from further consideration. 
			for( j = 0; (j < aktlast) ; j++ )
				if (bl[i].section && (i!=j) && (bl[j].mindist>bl[i].minmaxdist)){
					aktlast = j;
					if (j <= i)
						error("Error in pruneBrunchList\n", true);
					break;
				}
	}

    for( i = 0; i < aktlast; i++)
		if (bl[i].section)
			if (*nearest_distanz > bl[i].minmaxdist)
				*nearest_distanz = bl[i].minmaxdist;

    for( i = 0; (i < aktlast) && (*nearest_distanz >= bl[i].mindist) ; i++);
    aktlast = i;

    return (aktlast);   
}

bool boundedFound(float *bounces, float *bound, int dimension){
	int i;
	for (i=0; i<dimension; i++)
		if (bounces[2*i]==bound[2*i+1])
			return true;
	
	return false;
}

bool cornerFound(float *bounces, float *bound, int dimension){
	int i;
	for (i=0; i<dimension; i++)
		if (bounces[2*i]!=bound[2*i])
			return false;
	
	return true;
}

float objectDIST(float *p1, float *p2){
    float summe = 0;
    int i;
    
    for( i = 0; i < DIMENSION; i++)
	summe += pow(p1[i] - p2[i], 2 );

    return(summe);
}

/*****************************************************************
this function returns the maxdist of 2 mbrs
para:
m1: the bounces of the 1st mbr
m2: the bounces of the 2nd mbr
dim: dimensionality
*****************************************************************/

float MbrMAXDIST(float *_m1, float *_m2, int _dim){
	float dist=0;
	for (int i=0; i<_dim; i++){
		float d1=fabs(_m1[2*i]-_m2[2*i+1]);
		float d2=fabs(_m1[2*i+1]-_m2[2*i]);
		float d=max(d1, d2);
		dist+=pow(d, 2);
	}
	return dist;
}

/*****************************************************************
this function returns the mindist of 2 mbrs
para:
m1: the bounces of the 1st mbr
m2: the bounces of the 2nd mbr
dim: dimensionality
*****************************************************************/

float MbrMINDIST(float *_m1, float *_m2, int _dim){
	float dist=0;
	for (int i=0; i<_dim; i++){
		if (_m1[2*i]>_m2[2*i+1])
			dist+=pow(_m1[2*i]-_m2[2*i+1], 2);
		else if (_m1[2*i+1]<_m2[2*i])
			dist+=pow(_m1[2*i+1]-_m2[2*i], 2);
	}
	return dist;
}

float MINDIST(float *p, float *bounces){
    float summe = 0.0;
    float r;
    int i;

    for(i = 0; i < DIMENSION; i++){
		if (p[i] < bounces[2*i])
			r = bounces[2*i];
		else{
			if (p[i] > bounces[2*i +1])
			r = bounces[2*i+1];
			else 
			r = p[i];
		}    

		summe += pow( p[i] - r , 2);
	}
    return(summe);
}

float MAXDIST(float *p, float *bounces, int dim){
    float summe = 0.0;
    float r;
    int i;

    for(i = 0; i < dim; i++){
		if (p[i] < bounces[2*i])
			r = bounces[2*i+1];
		else{
			if (p[i] > bounces[2*i+1])
			r = bounces[2*i];
			else if (p[i] - bounces[2*i] > bounces[2*i+1] -p[i])
					 r = bounces[2*i];
			     else
					 r = bounces[2*i+1];
		}    

		summe += pow(p[i]-r,2);
    }
    
	return(summe);
}

float MINMAXDIST(float *p, float *bounces){
    float summe = 0;
    float minimum = (float)1.0e20;
    float S = 0;

    float rmk, rMi;
    int k,i;

    for( i = 0; i < DIMENSION; i++) { 
		rMi = (	p[i] >= (bounces[2*i]+bounces[2*i+1])/2 ) ? bounces[2*i] : bounces[2*i+1];
		S += pow( p[i] - rMi , 2 );
    }

    for( k = 0; k < DIMENSION; k++){  
		rmk = ( p[k] <=  (bounces[2*k]+bounces[2*k+1]) / 2 ) ? bounces[2*k] : bounces[2*k+1];
		summe = pow( p[k] - rmk , 2 );	
	
		rMi = (	p[k] >= (bounces[2*k]+bounces[2*k+1]) / 2 ) ? bounces[2*k] : bounces[2*k+1];
		summe += S - pow( p[k] - rMi , 2 );
		minimum = min( minimum,summe);
	}

    return(minimum);
}

// Coded by Greg 08/10/02
float mindist(float *p, float *bounces, int dimension, float *bound){
	float *ol = overlapRect(dimension, bounces, bound);
    float summe = 0.0;
    float r;
    int i;

    for(i = 0; i < dimension; i++){
		if (p[i] < ol[2*i])
			r = ol[2*i];
		else{
			if (p[i] > ol[2*i +1])
				r = ol[2*i+1];
			else 
				r = p[i];
		}    
		summe += pow( p[i] - r , 2);
    }
	delete [] ol;
    return(summe);
}

float minmaxdist(float *p, float *bounces, int dimension, float *bound){
	float *ol = overlapRect(dimension, bounces, bound);
    float summe = 0;
    float minimum = (float)1.0e20;
    float S = 0;

    float rmk, rMi;
    int k,i;

    for( i = 0; i < dimension; i++) { 
		rMi = (	p[i] >= (ol[2*i]+ol[2*i+1])/2 )
			? ol[2*i] : ol[2*i+1];
		S += pow( p[i] - rMi , 2 );
    }

    for( k = 0; k < dimension; k++){  
		rmk = ( p[k] <=  (ol[2*k]+ol[2*k+1]) / 2 ) ? ol[2*k] : ol[2*k+1];
		summe = pow( p[k] - rmk , 2 );	
		rMi = (	p[k] >= (ol[2*k]+ol[2*k+1]) / 2 ) ? ol[2*k] : ol[2*k+1];
		summe += S - pow( p[k] - rMi , 2 );
		minimum = min( minimum,summe);
    }
	delete [] ol;
    return(minimum);
}

float* overlapRect_dynamic(int dimension, float *r1, float *r2, bool *func){
        float *overlap = new float[2*dimension];
        for (int i=0; i<dimension; i++){
			if (func[i] && (r1[i*2]>r2[i*2+1] || r1[i*2+1]<r2[i*2])){ // non overlapping
                delete [] overlap;
				return NULL;
			}
			overlap[2*i] = max(r1[i*2], r2[i*2]);
            overlap[2*i+1] = min(r1[i*2+1], r2[i*2+1]);
        }

        return overlap;
}

bool section_dynamic(int dimension, float *mbr1, float *mbr2, bool *func){
    for (int i = 0; i < dimension; i++)
		if (func[i])
			if (mbr1[2*i] > mbr2[2*i + 1] || mbr1[2*i + 1] < mbr2[2*i]) 
				return FALSE;
    return TRUE;
}

float minmaxdist_dynamic(float *p, float *bounces, int dimension, float *bound, bool *func){
	float *ol = overlapRect_dynamic(dimension, bounces, bound, func);
    float summe = 0;
    float minimum = (float)1.0e20;
    float S = 0;

    float rmk, rMi;
    int k,i;

    for( i = 0; i < dimension; i++) { 
		if (func[i]){
			rMi = (	p[i] >= (ol[2*i]+ol[2*i+1])/2 ) ? ol[2*i] : ol[2*i+1];
			S += pow( p[i] - rMi , 2 );
		}
    }

    for( k = 0; k < dimension; k++){  
		if (func[i]){
			rmk = ( p[k] <=  (ol[2*k]+ol[2*k+1]) / 2 ) ? ol[2*k] : ol[2*k+1];
			summe = pow( p[k] - rmk , 2 );	
			rMi = (	p[k] >= (ol[2*k]+ol[2*k+1]) / 2 ) ? ol[2*k] : ol[2*k+1];
			summe += S - pow( p[k] - rMi , 2 );
			minimum = min( minimum,summe);
		}
    }
	delete [] ol;
    return(minimum);
}

float mindist_dynamic(float *p, float *bounces, int dimension, float *bound, bool *func){
	float *ol = overlapRect_dynamic(dimension, bounces, bound, func);
    float summe = 0.0;
    float r;
    int i;

    for(i = 0; i < dimension; i++){
		if (func[i]){
			if (p[i] < ol[2*i])
				r = ol[2*i];
			else{
				if (p[i] > ol[2*i +1])
					r = ol[2*i+1];
				else 
					r = p[i];
			}    
			summe += pow( p[i] - r , 2);
		}
    }
	delete [] ol;
    return(summe);
}

bool mbr_inside_dynamic(float *mbr1, float *mbr2, int dimension, bool *func){
	int i;
	for (i = 0; i < dimension; i++)
		if (func[i])
			if (!(inside(mbr1[2*i], mbr2[2*i], mbr2[2*i+1]) && inside(mbr1[2*i+1], mbr2[2*i], mbr2[2*i+1])))
				return false;
	return true;
}

bool boundedFound_dynamic(float *bounces, float *bound, int dimension, bool *func){
	int i;
	for (i=0; i<dimension; i++)
		if (func[i])
			if (bounces[2*i]==bound[2*i+1])
				return true;
	return false;
}

int sort_tuple_score(const void *d1, const void *d2){
    SortTuple *s1, *s2;
    float erg;
    int dimension;

	s1 = (SortTuple *) d1;
	s2 = (SortTuple *) d2;
    dimension = s1->dimension;
    erg = s1->score - s2->score;
    if (erg < 0.0)
		return -1;
    else if (erg == 0.0)
		return 0;
    else 
		return 1;
}

//returns the point inside mbb with the shortest distance to p
/**************************************************************************************************************/
float* mindis_point(float *p, float *mbb, int dim) {

	float *r = new float [dim];
	int i;

	for (i = 0; i<dim; i++) {
		if (p[i] < mbb[2*i]) {
			r[i] = mbb[2*i];
		} else {
			if (p[i] > mbb[2*i+1]) {
				r[i] = mbb[2*i+1];
			} else {
				r[i] = p[i];
			}
		}
	}
	return r;
}


float mindist_value(float *p, float *mbb, int dim){

	float *mindis = mindis_point(p, mbb, dim);

	float value = 0;
	for (int i=0; i<dim; i++){
		value += fabs(mindis[i] - p[i]);
	}

	delete mindis;

	return value;
}
