#include <utility>
#include <cmath>
#include <list>

typedef unsigned long long int l_int;

struct EmptyHeap: public std::exception {};

struct task
{
    l_int id;
    l_int p;
    task(l_int a, l_int b): id(a), p(b){}
    friend bool operator < (const task &a, const task &b)
    {
        if(a.p!=b.p) return a.p  < b.p;
        else         return a.id > b.id;
    }
    friend bool operator > (const task &a, const task &b)
    {
        if(a.p!=b.p) return a.p  > b.p;
        else         return a.id < b.id;
    }
};


template<class T>
class BinomialHeap {
    private:
        /* inner class: binomial tree */
        struct BinomialTree {
            //l_int _size;
            T element; //id p
            std::list<BinomialTree*> children;

            BinomialTree(T _ele):  element(_ele) {
                children.clear();
            }

            int get_degree()
            {
                return this->children.size();
            }

            /* return the size of BinomialTree
             * #note that nullptr->size() == 0
             * (nullptr is a null pointer (like NULL in C))
             */
            //    int size() {
            //        return (this!=nullptr)?this->_size:0;
            //    }
        };
        /* some definition for convinience
         */
        typedef BinomialTree BT;
        typedef BinomialHeap<T> BH;
        typedef std::pair<BT*, BT*> CarrySum;
        typedef std::pair<T, BH> MaxRemainder;

        /* Merge three binomial trees which have the same sizes
         *
         * INPUT:   a: operand a, b: operand b, c: carry in
         *          (each of them are either nullptr or a pointer of BinomialTree with size 2^n)
         *
         * OUTPUT:  a pair consist of two variables.
         *          second: carry out (nullptr or a pointer of BinomialTree with size 2^(n+1))
         *          first: sum (nullptr or a pointer of BinomialTree with size 2^n)
         *
         * (just as a full adder: http://en.wikipedia.org/wiki/Adder_%28electronics%29#Full_adder )
         */
        CarrySum merge_tree(BT *a, BT *b, BT *c) 
        {
            CarrySum result;
            BT* tmp;
            if(a==nullptr && b== nullptr && c==nullptr)
            {
                //printf("1~~~\n");
                result = std::make_pair(nullptr, nullptr);
            }
                
            else if((a!=nullptr && b==nullptr && c==nullptr) ||
                    (b!=nullptr && c==nullptr && a==nullptr) ||
                    (c!=nullptr && a==nullptr && b==nullptr)  )
            { 
                //printf("2~~~\n");
                if(a==nullptr) { if(b==nullptr) tmp=c; else tmp=b;}
                else             tmp = a;
                result = std::make_pair(tmp, nullptr);                 
            }
            else if((a!=nullptr && b!=nullptr && c==nullptr) ||
                    (b!=nullptr && c!=nullptr && a==nullptr) ||
                    (c!=nullptr && a!=nullptr && b==nullptr)  )
            { 
                //printf("3~~~\n");
                if(a==nullptr)
                {
                    if(c->element < b->element) { b->children.push_front(c); result=std::make_pair(nullptr,b); }
                    else                        { c->children.push_front(b); result=std::make_pair(nullptr,c); }
                }
                else
                {
                    tmp = (b!=nullptr)?b:c;
                    if(a->element < tmp->element) { tmp->children.push_front(a); result=std::make_pair(nullptr,tmp); }
                    else                          { a->children.push_front(tmp); result=std::make_pair(nullptr,a  ); }                    
                } 
            }                
            else
            {
                //printf("4~~~\n");
                if(a->element < b->element) { b->children.push_front(a); result=std::make_pair(c,b); }
                else                        { a->children.push_front(b); result=std::make_pair(c,a);}
            }
            return result;
        };

        /* Pop the maximum element of a binomial tree and make other elements a binomial heap.
         *
         * INPUT:   a: a pointer of BinomialTree
         *
         * OUTPUT:  a pair consist of two variables.
         *          first: the maximum element
         *          second: a binomial heap consists of other elements
         */
        MaxRemainder pop_max(BT *a) 
        {
            BH tmp;
            T pop_element(a->element.id, a->element.p);
            //printf("pop_element.id= %llu, p=%llu\n", a->element.id, a->element.p);
            
            while(!a->children.empty())
            {
               BT* fraction = a->children.front();
               int degree = fraction->get_degree();
               tmp.trees[degree] = fraction;
               //pop掉已經計算的children
               a->children.pop_front();
            }
            
            //debug
            //for(int i=0; i<32; i++)
            //{
            //    if(tmp.trees[i]==nullptr)
            //    {
            //        printf("tmp[%d] is 0\n", i );
            //    }
            //}

            MaxRemainder r = std::make_pair(pop_element,tmp);
            delete a;
            return r;
        }

        BT* trees[32]; //binomial trees of the binomial heap, where trees[i] is a tree with size 2^i.

    public:
        l_int size;

        BinomialHeap(): size(0) {
            for(int i=0; i<32; ++i) trees[i] = nullptr;
        }
        BinomialHeap(T element): size(1) {
            for(int i=0; i<32; ++i) trees[i] = nullptr;
            trees[0] = new BT(element);
        }

        /* merge all elements in the binomial heap b into *this, and clear the binomial heap b.
         *
         * INPUT:   b: a reference of BinomialHeap
         */
        void merge(BH &b) 
        {
            //printf("merge function start!\n");
            //if(this->trees[0]!=nullptr && b.trees[0]==nullptr)
            //    printf("this->trees[0]->element.id=%llu, p=%llu\n", this->trees[0]->element.id, this->trees[0]->element.p);
            //else if(this->trees[0]==nullptr && b.trees[0]!=nullptr)
            //    printf("b->trees[0]->element.id=%llu, p=%llu\n", b.trees[0]->element.id, b.trees[0]->element.p);
            //else if(this->trees[0]!=nullptr && b.trees[0]!=nullptr)
            //    printf("this->trees[0]->element.id=%llu, p=%llu, b->trees[0]->element.id=%llu, p=%llu\n", this->trees[0]->element.id, this->trees[0]->element.p, b.trees[0]->element.id, b.trees[0]->element.p);
            
            CarrySum s = merge_tree(this->trees[0], b.trees[0], nullptr);
            trees[0] = s.first;
            //if(s.first!=nullptr)
            //    printf("id= %llu, p=%llu\n", s.first->element.id, s.first->element.p);
            //else
            //    printf("tree[0] is nullptr\n");
            BT* c_r    = s.second;
            //printf("get tree[1]'s carryin\n");
            //if(c_r==nullptr)
            //    printf("function well, tree[1]'s carryin is nullptr\n");
            //else
            //    printf("id= %llu, p=%llu\n", s.second->element.id, s.second->element.p);
            for(int i=1; i<32; i++)
            {
                //printf("tree[%d] merging~~\n", i);
                //if(this->trees[i]!=nullptr)
                //    printf("tree's id= %llu, p=%llu\n", trees[i]->element.id, trees[i]->element.p);
                //else
                //    printf("tree[%d] is nullptr\n", i);
                //if(b.trees[i]!=nullptr)
                //    printf("tree's id= %llu, p=%llu\n", b.trees[i]->element.id, b.trees[i]->element.p);
                //else
                //    printf("b.tree[%d] is nullptr\n", i);
                //printf("run for loop in merge, %d times\n", i);
                s = merge_tree(this->trees[i], b.trees[i], c_r);
                //printf("tree[%d] merged~~\n", i);
                this->trees[i] = s.first;
                //if(this->trees[i]==nullptr)
                //    printf("tree[%d] is nullptr\n", i);
                //else
                //    printf("tree[%d] exist!\n", i);
                c_r = s.second;
                //if(c_r==nullptr)
                //    printf("tree[%d]'s c_r is nullptr\n", i+1);
                //else
                //    printf("tree[%d]'s c_r exist!\n", i+1);

           }
           //printf("_______________________________\n");
           this->size += b.size;
           b.size =0;
           //printf("this->size= %llu\n", this->size);
           for(int i=0; i<32; i++)  b.trees[i] = nullptr;
           //for(int i=0; i<32; i++) if(this->trees[i]!=nullptr) printf("%d is 1  \n", i);
            //printf("merge function over\n");
        }

        void insert(const T &element) {
            BH tmp = BH(element);
            merge(tmp);
            
        }
        T pop() {
            if(size==0) throw EmptyHeap();
            else 
            {
                //find the tree contains maximum element
                int max_tree = -1;
                for(int i=0; i<32; ++i)
                    if(trees[i]!=nullptr && (max_tree == -1 || trees[i]->element > trees[max_tree]->element))
                        max_tree = i;
                //printf("max_tree is tree[%i]\n", max_tree);

                MaxRemainder m_r = pop_max(trees[max_tree]);
                T &max_element = m_r.first;
                BH &remainder = m_r.second;

                int tree_max_s = pow(2, trees[max_tree]->get_degree());
                size -= tree_max_s;
                trees[max_tree] = nullptr;
                //printf("pop merging\n");
                merge(remainder);
                //printf("succedd!\n");
                return max_element;
            }
        }

         T show_max_e()
         {
            int max_tree = -1;
            for(int i=0; i<32; ++i)
                if(trees[i]!=nullptr && (max_tree == -1 || trees[i]->element > trees[max_tree]->element))  max_tree=i;
            return this->trees[max_tree]->element;
        }
};