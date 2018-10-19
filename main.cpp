#include <iostream>
#include <thread>
#include <mutex>
#include <cstdlib>
#include <ctime>

#include <time.h>
#include <unistd.h>

#include "wayqueue.hpp"

using namespace std;

Wayqueue queue;
mutex mt;

void push_method()
{
    Point *p = new Point();
    int i;
    for(i = 0; i < 20; i++){
        p->x = rand() % 10;
        p->y = rand() % 10;
        queue.push(p);
        mt.lock();
        cout << "__Push: (" << p->x << ", " << p->y << ")" << endl;
        mt.unlock();
    }
}

void pop_method()
{
    Point *p = new Point;
    int i;
    for(i = 0; i < 10; i++){
        int rnd = rand() % 20;
        usleep(rnd);
        p = queue.pop();
        mt.lock();
        cout << "Pop: " << "(" << p->x << ", " << p->y << ")" << endl;
        mt.unlock();
    }
}

int main(int argv, char * argc[])
{
    srand(time(0));

    thread t1 (push_method);
    thread t2 (pop_method);

    t1.join();
    t2.join();

    return 0;
}
