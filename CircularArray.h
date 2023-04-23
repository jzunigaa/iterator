#include <iostream>

using namespace std;

template<class T>
class CircularArrayIterator{
    int current; //posición actual
    T* array;
    int capacity;
public:
    CircularArrayIterator(){
        this->current = -1;
        this->capacity = 0;
        this->array = nullptr;
    } 

    CircularArrayIterator(int index, int capacity, T* array = nullptr){
        this->current = index;
        this->array = array;
        this->capacity = capacity;
    }

    bool operator!=(const CircularArrayIterator &other){
        return this->current != other.current;
    }

    CircularArrayIterator operator++(){
        this->current = this->next(this->current);
        return *this;
    }
/*
    CircularArrayIterator operator--(){
        this->current = this->prev(current);
        return *this;
    }
*/
    T operator*(){
        return array[current];
    }

    private:
    int next(int pos){
        if (pos == this->capacity-1){
            return 0;
        } else{
            return pos + 1;
        }
    }

    int prev(int pos){
        if (pos == 0){
            return this->capacity-1;
        } else{
            return pos - 1;
        }
    }
};

template <class T>
class CircularArray
{
private:
    T *array;
    int capacity;
    int back, front;

public:
    typedef CircularArrayIterator<T> iterator;

public:
    CircularArray(int _capacity = 10);
    virtual ~CircularArray();
    void push_front(T data);
    void push_back(T data);
    void insert(T data, int pos);
    T pop_front();
    T pop_back();
    bool is_full();
    bool is_empty();
    int size();
    void clear();
    T& operator[](int);
    void sort();
    bool is_sorted();
    void reverse();
    //string to_string(string sep=" ");
    void redimensionar();
    void display();
    CircularArrayIterator<T> begin();
    CircularArrayIterator<T> end();

private:
    int next(int);
    int prev(int);
};

template <class T>
CircularArray<T>::CircularArray(int _capacity)
{
    this->capacity = _capacity;
    this->array = new T[_capacity];
    this->front = this->back = -1;//empty
}

template <class T>
void CircularArray<T>::clear(){
    this->front = this->back = -1;
}

template <class T>
void CircularArray<T>::push_front(T data){
    int pos;
    if (this->is_full()){
        //mandar mensaje de error por superación de capacidad
       // cout<<"El arreglo esta lleno"<<endl;
       this->redimensionar();
       this->push_front(data);
    }
    else if (this->is_empty()){
        this->array[0] = data;
        this->front = this->back = 0;
    }
    else {
        if (this->back == (this->capacity-1)){
            pos = 0;
        }
        else {pos = this->back + 1;}

        this->array[pos] = data;
        this->back = pos;
    }
}

template <class T>
void CircularArray<T>::push_back(T data){
    int pos;
    if (this->is_full()){
        //mandar mensaje de error por superación de capacidad
        //cout<<"El arreglo esta lleno"<<endl;
        this->redimensionar();
        this->push_back(data);
    }
    else if(this->is_empty()){
        this->array[0] = data;
        this->front = this->back = 0;
    }
    else{
        if (this->front == 0){
                pos = this->capacity - 1;
            }
        else{
            pos = front-1;
        }

        this->array[pos] = data;
        this->front = pos;
    }
}

template <class T>
T& CircularArray<T>::operator[](int _pos){
    int _posn = this->front+_pos;
    if (_posn > this->capacity-1){
        _posn = _posn - this->capacity;
        return this->array[_posn];
    } else{
        return this->array[_posn];
    }
}

template <class T>
bool CircularArray<T>::is_empty(){
    if (this->front == -1 && this->back ==-1){
        return true;
    } else { return false;}
}

template <class T>
int CircularArray<T>::size(){
    if (this->is_empty()){
        return 0;
    }
    if (this->back >= this->front){
        return (this->back - this->front + 1);
    }
    else {return (this->capacity - this->front + this->back + 1);}
}

template <class T>
bool CircularArray<T>::is_full(){
    if (this->size() == this->capacity) {
        return true;
    }
    else {return false;}
}

template <class T>
T CircularArray<T>::pop_front(){
    if (this->is_empty()){
        //mensaje de error porque no hay elementos que eliminar
        cout<<"No hay elementos para eliminar"<<endl;
    }
    else{
        if(this->front == this->capacity -1 ){
            this->front = 0;
        }
        else{this->front = front + 1;}
    }
}

template <class T>
T CircularArray<T>::pop_back(){
    if (this->is_empty()){
        //mensaje de error porque no hay elementos para eliminar
        cout<<"No hay elementos para eliminar"<<endl;
    }
    else{
        if(this->back == 0){
            this->back = this->capacity-1;
        }
        else{this->back = this->back-1;}
    }
}

template <class T>
CircularArray<T>::~CircularArray(){
    if(this->array != nullptr){
        delete[] this->array;
    }
    cout<<"Ha terminado"<<endl;
}

template <class T>
void CircularArray<T>::sort(){
    for(int i=0;i<this->size()-1;i++){
        int may = this->array[i];
        if (may>this->array[i+1]){
            this->array[i] = this->array[i+1];
            this->array[i+1] = may;
        }
    }
}

template<class T>
bool CircularArray<T>::is_sorted(){
    for(int i=0;i<this->size()-1;i++){
        int may = this->array[i];
        if (may>this->array[i+1]){
            return false;
        }
    }
    return true;
}

template <class T>
void CircularArray<T>::reverse(){
    T *temp = new T(this->capacity);
    int j=0;
    for(int i=this->size()-1;i>=0;i--){
        temp[j] = array[i];
        j++;
    }
    this->array = temp;
    this->front = 0;
    this->back =  this->size()-1;
}
/*
template <class T>
std::string CircularArray<T>::to_string(std::string sep=" "){
    return "";
}
*/
template <class T>
void CircularArray<T>::insert(T data, int pos){

}

template <class T>
void CircularArray<T>::redimensionar(){
    T *temp = new T[this->capacity*2];
    //recorremos y copiamos
    int j = 0;
    int pos = this->front;
    if(this->is_full()){
        temp[j] = this->array[pos];
        pos = this->next(pos);
        j=j+1;
        while ( pos != this->front){
            temp[j] = this->array[pos];
            pos = this->next(pos);
            j=j+1;
        }
    } else{
        while (pos != this->next(this->back)){
            temp[j] = this->array[pos];
            pos = this->next(pos);
            j=j+1;
        }
    }
    this->array = temp;
    this->front = 0;
    this->back = j-1;
    this->capacity = this->capacity*2;

    cout<<"redimensionar"<<endl;
    this->display();
}

template<class T>
void CircularArray<T>::display(){
    int pos = this->front;
    if(this->is_full()){
        cout<<this->array[pos]<<endl;
        pos = this->next(pos);
        while ( pos != this->front)
        {
            cout<<this->array[pos]<<endl;
            pos = this->next(pos);
        }
    } else{
        while (pos != this->next(this->back))
        {
            cout<<this->array[pos]<<endl;
            pos = this->next(pos);
        }
    }
}

template<class T>
int CircularArray<T>::next(int pos){
    if (pos == capacity-1){
        return 0;
    } else{
        return pos + 1;
    }
}

template<class T>
int CircularArray<T>::prev(int pos){
    if (pos == 0){
        return capacity-1;
    } else{
        return pos - 1;
    }
}

template<class T>
CircularArrayIterator<T> CircularArray<T>::begin(){
        return iterator(this->front, this->capacity, this->array);
}

template<class T>
CircularArrayIterator<T> CircularArray<T>::end(){
        return iterator(this->next(back),this->capacity);
}  