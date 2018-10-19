#include <iostream>

#include "wayqueue.hpp"

Wayqueue::Wayqueue()
{
    size = 0;
    head = nullptr;
    tail = nullptr;
    needs_update = true;
}

void Wayqueue::push(Point *toAdd)
{
    unique_lock<std::mutex> mlock(mtx);
    Point *temp = new Point();
    temp->x = toAdd->x;
    temp->y = toAdd->y;
    temp->next = nullptr;
    if(head == nullptr){
        head = temp;
        tail = temp;
    } else {
        tail->next = temp;
        tail = temp;
    }
    size++;
    needs_update = false;
    mlock.unlock();
    cond_var.notify_one();
}

Point* Wayqueue::pop()
{
    // Always get the mutex before you check the condition variable
    unique_lock<std::mutex> mlock(mtx);
    while (head == nullptr)
    {
        cond_var.wait(mlock);
    }
    Point *ret = new Point;
    ret = head;
    head = head->next;
    size--;
    return ret;
}

int Wayqueue::getSize()
{
    return size;
}

void clearAll()
{
    unique_lock<std::mutex> mlock(mtx);
    Point *curr = new Point();
    Point *del = new Point();
    temp = head;
    while(temp != nullptr)
    {
        del = temp;
        temp = temp->next;
        delete del;
    }
    
}

void Wayqueue::display()
{
    Point *temp = new Point();
    temp = head;
    while(temp != nullptr)
    {
        cout << "(" << temp->x << ", " << temp->y << ")" << endl;
        temp = temp->next;
    }
}







