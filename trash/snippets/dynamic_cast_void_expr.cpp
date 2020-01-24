#include<iostream>

struct Unit
{
    virtual void f() {};
    int c;
};

struct Archer : Unit
{
    int d;
};

struct Elf: Unit
{
    int a;
};

struct ElfArcher: Elf, Archer
{
    int b;
};


int main()
{
    ElfArcher obj;
    Unit* obj_ptr = &obj;

    std::cout << dynamic_cast<Unit*>(obj_ptr) << std::endl;
    std::cout << dynamic_cast<Elf*>(obj_ptr) << std::endl;
    std::cout << dynamic_cast<Archer*>(obj_ptr) << std::endl;
    std::cout << dynamic_cast<ElfArcher*>(obj_ptr) << std::endl;
    std::cout << dynamic_cast<void *>(obj_ptr) << std::endl;

    return 0;
}