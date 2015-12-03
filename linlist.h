#ifndef __LINLIST
#define __LINLIST

class RTree;

struct Linkable{
public:
	int son;
	int dimension;
	int level;
	float *bounces;
	float distanz;
	
	Linkable() {} // added by Greg
	Linkable(int dim){ 
		dimension = dim;
		bounces = new float[2 * dim];
    }
	Linkable(int dim, float *_bounces){ 
		dimension = dim;
		bounces = new float[2*dim];
		memcpy(bounces, _bounces, 2*dim*sizeof(float));
    }

	~Linkable(){ 
		delete [] bounces;
	}
};

struct SLink{
    Linkable *d;          
    SLink *next;          
    SLink *prev;          

    SLink();
    ~SLink();
};

//a linklist class
//why not fucking use the STL::list?
class LinList{
protected:
    SLink *first;//first on list         
    SLink *last;//last on list          
    int anz;//count number                   
    SLink *akt;//list iterator            
    int akt_index;//list iterator index              
public:
    LinList();
    virtual ~LinList();
    int get_num()               
        { return anz; }        

    void check();              
    void print();

    void insert(Linkable *f);//insert new one to the front of list       
    void insert_behind(Linkable *f);//insert new one to the end of list       
    void move_front();//move the akt pointed to the front of list
    bool erase();               
	Linkable * remove();		

    Linkable * get(int i);          
    Linkable * get_first();         
    Linkable * get_last();          
    Linkable * get_next();          
    Linkable * get_prev();          
};


class SortedLinList : public LinList{
    bool increasing;
public:
    SortedLinList();

    void set_sorting(bool _increasing);        
    void insert(Linkable *f);      
    void sort(bool _increasing);
};

#endif 
