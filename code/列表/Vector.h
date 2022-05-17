#ifndef VECTOR_H
#define VECTOR_H
/**
 * @brief 实现一个自己的vertor，不进行分离编译
 *  
 */

#include<algorithm>
#include<iostream>

template <typename Object>
class Vector
{
private:
    /* data */
    int Size;       //现在的大小
    int Capacity;   //容量，到一定容量需要进行扩容
    Object *objects; //存放对象的数组
public:
    static const int SPARE_CAPACITY=16;
    Vector(int size):Size(size),Capacity(size+SPARE_CAPACITY){
        objects =new Object[Capacity];
    }
    Vector(const Vector &rhs):Size(rhs.Size),Capacity(rhs.Capacity),objects(nullptr){
        objects=new Object[Capacity];
        for (int i=0;i<Size;i++)
            objects[i]=rhs.objects[i];
    }
    ~Vector(){
        delete [] objects;
    }

    
    Object & at(int index){
        if (index>0&&index<Size){
            return objects[index];
        }
        return nullptr;
    }

    Vector & operator=(const Vector &rhs){
        Vector copy=rhs;
        std::swap(*this,copy);//这里就是用了移动吗
        return *this;
    }
    //
    void resize(int newSize){
        if (newSize>(*this).Capacity){
            reverve(Capacity*2);
        }
        Size=newSize;
    }
    //用来扩容
    void reverve(int newCapacity){
        if(newCapacity<Size){
            return;
        }
        Object *newObjects=new Object[newCapacity];
        for (int i=0;i<Size;i++)
            newObjects[i]=std::move(objects[i]);
        Capacity=newCapacity;
        std::swap(objects,newObjects);//这里交换首元素地址
        delete []newObjects;
    }
    // [] 等同于 at() 
    Object & operator[] (int index){
        if (index>=0&&index<Size){
            return objects[index];
        }
        // return NULL;
    }

    bool empty() const{
        return Size==0;
    }
    int size() const {
        return Size;
    }
    int capacity() const {
        return Capacity;
    }

    void push_back(const Object &ob){
        if (Size==Capacity){
            reverve(Capacity*2);
        }
        objects[Size++]=ob;
    }

    void pop_back(){
        --Size;
    }
    
    const Object & back() const{
        return objects[Size-1];
    }

    typedef Object* iterator;
    typedef const Object *cons_iterator;

    iterator begin(){
        return &objects[0];
    }
    cons_iterator begin() const {
        return &objects[0];
    }
    iterator end(){
        return &objects[size()];
    }
    cons_iterator end() const {
        return &objects[size()];
    }

    //实现两个麻烦一点的
    
    void insert(int index,const Object& ob){
        if (Size==Capacity){
            reverve(Capacity*2);
        }
        if(index>=0&&index<Size){
            //先把index之后的数据都向后挪动一位
            for (int i=Size;i>index;i--)
                objects[i]=objects[i-1];
            objects[index]=ob;
            Size++;
        }
    }
    void remove (int index){
        if(index>=0&&index<Size){
            for (int i=index;i<Size-1;i++){
                objects[i]=objects[i+1];
            }
            Size--;
        }
    }
    void print() const{
        for(int i=0;i<Size;i++)
            printf("第 %d 个元素为 %d \n",i,objects[i]);
    }
};
#endif
