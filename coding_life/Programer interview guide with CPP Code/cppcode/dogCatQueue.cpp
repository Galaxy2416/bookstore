#include <iostream>
#include <memory>
#include <stdlib.h>
#include <queue>
#include <algorithm>
#include <assert.h>
#include <string>

/*
宠物、狗和猫的类如下：
public class Pet {
private String type;
public Pet(String type) {
this.type = type;
}
public String getPetType() {
return this.type;
}
}
public class Dog extends Pet {
public Dog() {
super("dog");
}
}
public class Cat extends Pet {
public Cat() {
super("cat");
}
}
实现一种狗猫队列的结构，要求如下：
- 用户可以调用 add 方法将 cat 类或 dog 类的实例放入队列中；
- 用户可以调用 pollAll 方法，将队列中所有的实例按照进队列的先后顺序依次弹出；
- 用户可以调用 pollDog 方法，将队列中 dog 类的实例按照进队列的先后顺序依次弹出；
- 用户可以调用 pollCat 方法，将队列中 cat 类的实例按照进队列的先后顺序依次弹出；
- 用户可以调用 isEmpty 方法，检查队列中是否还有 dog 或 cat 的实例；
- 用户可以调用 isDogEmpty 方法，检查队列中是否有 dog 类的实例；
- 用户可以调用 isCatEmpty 方法，检查队列中是否有 cat 类的实例
*/

using namespace std;
class Pet
{
    private:
        string type;
    public:
        Pet(string _type) : type(_type)
        {
        }
        const string& getPetType()
        {
            return type;
        }
};

class Cat : public Pet
{
    public:
        Cat() : Pet("cat")
        {
        }
};

class Dog : public Pet
{
    public:
        Dog() : Pet("dog")
        {
        }
};

class PetEnterQueue 
{
    private:
        Pet pet;
        long int count;
    public:
        PetEnterQueue(Pet _pet, long int _count) : pet(_pet), count(_count) // For C++ have to do this otherwise will be no-default construct issue 
        {
        }
        Pet getPet() 
        {
            return this->pet;
        }
        long int getCount() 
        {
            return this->count;
        }
        const string& getEnterPetType() 
        {
            return this->pet.getPetType();
        }

};

class DogcatQueue
{
    private:
        std::queue<PetEnterQueue> dogQueue, catQueue;
        long int count;
    public:
        DogcatQueue()
        {
            this->count = 0;
        }
        void add(Pet data)
        {
            if ("cat" == data.getPetType())
                catQueue.push(PetEnterQueue(data, count++));
            else if ("dog" == data.getPetType())
                dogQueue.push(PetEnterQueue(data, count++));
            else
                throw "Only cat and dog are supported";
        }
        
        Pet pollDog()
        {
            if (!dogQueue.empty())
                {
                    Pet pet = dogQueue.front().getPet();
                    // Dog *dogp = static_cast<Dog*> (&pet); // dangerous but ok in this case
                    dogQueue.pop();
                    return pet;
                }
        }

        Pet pollCat()
        {
            if (!catQueue.empty())
                {
                    Pet pet = catQueue.front().getPet();
                    // Cat *catp = static_cast<Cat*> (&pet); // dangerous but ok in this case
                    catQueue.pop();
                    return pet;
                }
        }

        bool isDogEmpty()
        {
            return dogQueue.empty();
        }

        bool isCatEmpty()
        {
            return catQueue.empty();
        }

        bool isEmpty()
        {
            return isDogEmpty() && isCatEmpty();
        }

        Pet pollAll()
        {
            if (isEmpty())
                throw "Empty.";
            cout << dogQueue.front().getCount();
            cout << catQueue.front().getCount();

            return isDogEmpty() ? pollCat() : isCatEmpty() ? pollDog() : dogQueue.front().getCount() > catQueue.front().getCount() ? pollDog() : pollCat();
        }

        void sizePrint()
        {
            cout << "dogQueue: " << dogQueue.size() << endl;
            cout << "catQueue: " << catQueue.size() << endl;
        }
};

int main()
{
    DogcatQueue test;
    assert(true == test.isEmpty());
    test.add(Pet("dog"));
    assert(false == test.isEmpty());
    assert(false == test.isDogEmpty());
    assert(true == test.isCatEmpty());
    test.add(Pet("dog"));
    test.add(Pet("cat"));
    assert(false == test.isCatEmpty());
    test.add(Pet("cat"));
    test.add(Pet("dog"));
    test.sizePrint();
    test.pollAll(); test.sizePrint();
    test.pollCat(); test.sizePrint();
    test.pollDog(); test.sizePrint();    
}
