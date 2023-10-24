#include<iostream>
using namespace std;
template <class T>
class SLinkedList
{
public:
    class Iterator; //forward declaration
    class Node;     //forward declaration
protected:
    Node *head;
    Node *tail;
    int count;
public:
    SLinkedList() : head(nullptr), tail(nullptr), count(0){};
    ~SLinkedList();
    void add(const T e);
    void add(int index, const T e);
    T removeAt(int index);
    bool removeItem(const T removeItem);
    bool empty();
    int size();
    void clear();
    T get(int index);
    void set(int index, const T e);
    int indexOf(const T item);
    bool contains(const T item);
    void display();
    SLinkedList(const SLinkedList<T> & list)
    {
        this->count = 0;
        this->head = nullptr;
        this->tail = nullptr;
    }
    Iterator begin()
    {
        return Iterator(this, true);
    }
    Iterator end()
    {
        return Iterator(this, false);
    }
public:
    class Node
    {
    private:
        T data;
        Node *next;
        friend class SLinkedList<T>;
    public:
        Node()
        {
            next = 0;
        }
        Node(Node *next)
        {
            this->next = next;
        }
        Node(T data, Node *next = nullptr)
        {
            this->data = data;
            this->next = next;
        }
    };
    class Iterator
    {
    private:
        SLinkedList<T> *pList;
        Node *current;
        int index; // corresponding with current node
    public:
        Iterator(SLinkedList<T> *pList, bool begin);
        Iterator &operator=(const Iterator &iterator);
        void remove();
        void set(const T &e);
        T &operator*();
        bool operator!=(const Iterator &iterator);
        
        // Prefix ++ overload
        Iterator &operator++();
        
        // Postfix ++ overload
        Iterator operator++(int);
    };
};

template <class T>
void SLinkedList<T>::add(T  e)
{
    if (head) 
    {
        tail->next=new Node(e);
        tail=tail->next;
    }
    else 
    {
        head=tail=new Node(e);
    }
    count++;
}
template <class T>
void SLinkedList<T>::add(int index, T  e)
{
        if (index<0 || index >count )
        {
            throw std::out_of_range("Index out of range");
        }
        else if (index==0)
        {
            if (head)
            {
                head = new Node(e,head);
            }
            else 
            head=tail=new Node(e);
        }
        else if (index==count)
        {
            tail->next =new Node (e);
            tail=tail->next;
        }
        else 
        {
            Node * curr=head;
            for (int i=1;i<index;i++)
            {
                curr=curr->next;
            }
            curr->next=new Node(e,curr->next);
        }
        count ++;
}
template <class T>
int SLinkedList<T>::size()
{
    return count;
}
template <class T>
void SLinkedList<T>::clear()
{
    head=nullptr;
    tail=nullptr;
    count=0;
}
template <class T>
bool SLinkedList<T>::empty()
{
    /* Check if the list is empty or not. */
    return count==0;
}
template<class T>
T SLinkedList<T>::get(int index) {
    /* Give the data of the element at given index in the list. */
    Node * curr= head;
    if(index<0 || index>=count )
    {
        throw std::out_of_range("Index out of range");
    }
    else 
    {
        for (int i=0;i<index;i++)
        {
            curr=curr->next;
        }
        return curr->data;
    } 
}
template <class T>
void SLinkedList<T>::set(int index, const T  e) {
    
    /* Assign new value for element at given index in the list */
    if (index<0 || index>=count) return ;
    else 
    {
        Node* curr=head;
        for (int i=0;i<index;i++)
        {
            curr=curr->next;
        }
        curr->data=e;
    }
}
template<class T>
int SLinkedList<T>::indexOf(const T item) {
    /* Return the first index wheter item appears in list, otherwise return -1 */
    Node * curr=head;
    for (int i=0;i<count;i++)
    {
        if (curr->data==item) return i;
        else curr=curr->next;
    }
    return -1;
}
template<class T>
bool SLinkedList<T>::contains(const T  item) {
    /* Check if item appears in the list */
    return indexOf(item) != -1;
}
template <class T>
void SLinkedList<T>::display()
{
        Node * curr=head;
        while (curr!=nullptr)
        {
            cout<<curr->data<< "   ";
            curr=curr->next;
        }
}
template <class T>
T SLinkedList<T>::removeAt(int index)   
{
    T data_return;
    /* Remove element at index and return removed value */
    if (index<0 & index >=count)
    {
        throw std::out_of_range("Index out of range");
    }
    else 
    {
        if (index==0)
        {
            data_return=head->data;
            head=head->next;
        }
        else 
        {
            Node * prev=head;
            for (int i=1;i<index;i++)
            {
                prev=prev->next;
            }
            if (index==count-1) 
            {
                data_return=tail->data;
                tail=prev;
                tail->next=nullptr;
            }
            else 
            {
                Node * curr=prev->next;
                data_return=curr->data;
                prev->next=curr->next;
            }
        }
        return data_return;
    }
}
template <class T>
bool SLinkedList<T>::removeItem(T  item)
{
    int index=indexOf(item);
    if (index >=0 && index< count)
    {
        removeAt(index);
        return true;
    }
    return false;
}

template <class T>
SLinkedList<T>::Iterator::Iterator(SLinkedList<T>* pList, bool begin)
{
    /*
        Constructor of iterator
        * Set pList to pList
        * begin = true: 
        * * Set current (index = 0) to pList's head if pList is not NULL
        * * Otherwise set to NULL (index = -1)
        * begin = false: 
        * * Always set current to NULL
        * * Set index to pList's size if pList is not NULL, otherwise 0
    */
    this->pList=pList;
    if (begin)
    {
        if (this->pList->head)  
        {
            this ->current =this->pList->head;
            this->index=0;
        }
        else
        {
            this->current=nullptr;
            this->index=-1;
        }     
    }
   else 
    {
        this->current=nullptr;
        if (pList->head)    this->index=this->pList->size();
        else this->index=0;
    }

}

template <class T>
typename SLinkedList<T>::Iterator& SLinkedList<T>::Iterator::operator=(const Iterator& iterator)
{
    /*
        Assignment operator
        * Set this current, index, pList to iterator corresponding elements.
    */
    this->current=iterator.current;
    this->index=iterator.index;
    this->pList=iterator.pList;
}

template <class T>
void SLinkedList<T>::Iterator::remove()
{
    /*
        Remove a node which is pointed by current
        * After remove current points to the previous node of this position (or node with index - 1)
        * If remove at front, current points to previous "node" of head (current = NULL, index = -1)
        * Exception: throw std::out_of_range("Segmentation fault!") if remove when current is NULL
    */
    if (current==nullptr)
    {
        throw std::out_of_range("Segmentation fault!");
    }
    if(current==this->pList->head)
    {
        current=nullptr;
        index=-1;
    }
    else 
    {
        Node * prev=pList->head;
        while(prev->next!=current)
        {
            prev=prev->next;
        }
        prev->next=current->next;
        current=prev;
        index--;
    }
    pList->count--;
}


template <class T>
void SLinkedList<T>::Iterator::set(const T& e)
{
    /*
        Set the new value for current node
        * Exception: throw std::out_of_range("Segmentation fault!") if current is NULL
    */
   if (this->current==nullptr)
   {
    throw std::out_of_range("Segmentation fault!");
   }
   else 
   {
    this->current->data=e;
   }
}

template <class T>
T& SLinkedList<T>::Iterator::operator*()
{
    /*
        Get data stored in current node
        * Exception: throw std::out_of_range("Segmentation fault!") if current is NULL
    */
   if (this->current)
   {
    return current->data;
   }
   else 
   {
    throw std::out_of_range("Segmentation fault!");
   }
}

template <class T>
bool SLinkedList<T>::Iterator::operator!=(const Iterator& iterator)
{
    /*
        Operator not equals
        * Returns false if two iterators points the same node and index
    */
    return this->pList==iterator.pList && this->index==iterator.index && this->current==iterator.current;
}
// Prefix ++ overload
template <class T>
typename SLinkedList<T>::Iterator& SLinkedList<T>::Iterator::operator++()
{
    /*
        Prefix ++ overload
        * Set current to the next node
        * If iterator corresponds to the previous "node" of head, set it to head
        * Exception: throw std::out_of_range("Segmentation fault!") if iterator corresponds to the end
    */
    if (this->current==pList->tail)
    {
        throw std::out_of_range("Segmentation fault!");
    }
    else if (this->current==nullptr && this->index=-1)
    {
        current=pList.head;
        index=0;
    }
    else 
    {
        current=current->next;
    }
    index++;
    return *this;
}
// Postfix ++ overload
template <class T>
typename SLinkedList<T>::Iterator SLinkedList<T>::Iterator::operator++(int)
{
    /*
        Postfix ++ overload
        * Set current to the next node
        * If iterator corresponds to the previous "node" of head, set it to head
        * Exception: throw std::out_of_range("Segmentation fault!") if iterator corresponds to the end
    */
    Iterator temp = *this;
    if (current->next == nullptr && index==-1)
    {
        current = pList->head;
    }
    else  if (current == pList->tail)
    {
        throw std::out_of_range("Segmentation fault!");
    }
    else
    {
        current = current->next;
    }
    return temp;
}

int main()
{
	
SLinkedList<int> list;
 list.size() == 0 ;

int size = 10;
for(int idx=0; idx < size; idx++){
    list.add(idx);
}
 list.size() == size ;

int values[]   = {10,  15,  2,   6,  4,  7,   40,  8};
//                0    1    2    3   4   5    6    7
int index[]    = {0,   1,   5,   3,  2,  1,   1,   0};

/*                10,  15,  2,   6,  4,  7,   40,  8 //initial list
    *                15,  2,   6,   4,  7,  40,  8      //after removeAt 0
    *                15,  6,   4,   7,  40, 8      //after removeAt 1
    *                15,  6,   4,   7,  40   //after removeAt 5
    *                15,  6,   4,   40   //after removeAt 3
    *                15,  6,   40   //after removeAt 2
    *                15,  40   //after removeAt 1
    *                15,   //after removeAt 1
    *                {}  //after removeAt 0
    */
int expvalues[][8]= {
    {15,  2,   6,   4,  7,  40,  8},
    {15,  6,   4,   7,  40, 8},
    {15,  6,   4,   7,  40},
    {15,  6,   4,   40 },
    {15,  6,   40},
    {15,  40},
    {15},
    {}
};

list.clear();
 list.size() == 0 ;
 list.empty() == true ;
//
for(int idx=0; idx < 8; idx++)
    list.add(values[idx]);
 list.size() == 8 ;

//removeAt:
int count = 8;
for(int idx=0; idx < 8; idx++){
    int idxRemoved = index[idx];
    list.removeAt(idxRemoved);
     list.size() == (count - idx -1) ;
    //check expected values
    for(int c=0; c < (count - idx -1); c++ ){
        int exp = expvalues[idx][c];
        exp == list.get(c);
    }
}
list.display();
}

