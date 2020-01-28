#include <iostream>
//#define RAII //whether to use RAII mode

/*
this is a demo of RAII class
*/

//https://stackoverflow.com/questions/2321511/what-is-meant-by-resource-acquisition-is-initialization-raii
//https://zhuanlan.zhihu.com/p/34660259
//https://stackoverflow.com/questions/2709719/throwing-out-of-range-exception-in-c/2709733
//https://www.gergel.im/2016/06/05/dtors-not-always-called-when-exceptions-are-thrown/
//http://www.cplusplus.com/doc/tutorial/dynamic/

#ifdef RAII
class ResourceManager{
public:
    ResourceManager(): size(0), resource(nullptr){
        std::cout << "resource initialized" << std::endl;
    }

    ResourceManager(int size): size(size){
        resource = new int[size];
        std::cout << "resource initialized" << std::endl;
    }

    ~ResourceManager(){
        delete resource;
        std::cout << "resource released" << std::endl;
    }

    void set(int index, int value){
        if(index < 0 || index > size){
            throw std::out_of_range("invalid index!");
        }
        resource[index] = value;
    }

    int get(int index){
        if(index < 0 || index > size){
            throw std::out_of_range("invalid index!");
        }
        return resource[index];
    }
private:
    int* resource;
    int size;
};
#else
void set(int* resource, int size, int index, int value){
    if(index < 0 || index > size){
        throw std::out_of_range("invalid index!");
    }
    resource[index] = value;
}

int get(int* resource, int size, int index){
    if(index < 0 || index > size){
        throw std::out_of_range("invalid index!");
    }
    return resource[index];
}
#endif

int main(){
    try{
#ifdef RAII
        ResourceManager rm(100);
        std::cout << "set 100th element..." << std::endl;
        rm.set(100, 0);
        std::cout << "set 101th element..." << std::endl;
        rm.set(101, 0);
#else
        int* resource;
        int size = 100;
        resource = new int[size];
        std::cout << "resource initialized" << std::endl;
        std::cout << "set 100th element..." << std::endl;
        set(resource, size, 100, 0);
        std::cout << "set 101th element..." << std::endl;
        set(resource, size, 101, 0);
        delete resource;
        std::cout << "resource released" << std::endl;
#endif
    }catch(...){
        throw;
    }
    return 0;
}
