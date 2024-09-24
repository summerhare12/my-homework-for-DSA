#include <iostream>
#include <cstring>

class Chicken
{
    private:
        int age = 24;
        char *name = nullptr;
    public:
        Chicken(){};
        Chicken(int _age) : age(_age) {};
        Chicken(int _age, const char *_name) : age(_age) //This function is a constructor to equip the new chicken with age and name.
        {
            int len = strlen(_name) + 1;
            name = new char[len];
            for (int i = 0; i < len; i++)
                name[i] = _name[i];
        };

        void MakeEmpty()//I've ADDED this function to delete the name of the chicken.
        {
            if (name != nullptr)
                delete[] name;
        }

        ~Chicken()//I've CHANGED this function because i need MakeEmpty in the copy assignment function.
        {
            MakeEmpty();
        }

        void setAge(int _age)
        {
            age = _age;
        }
        void setName(const char *_name)
        {
            int len = strlen(_name) + 1;
            name = new char[len];
            for (int i = 0; i < len; i++)
                name[i] = _name[i];
        }

        const char *getName() const
        {
            return name;
        }

        const int &getAge() const
        {
            return age;
        }

        void printChicken()//I've added this function to print the chicken's name and age  :)
        {
            std::cout << "Hi, everyone! My name is " << name << ", I am " << age << " years old." << std::endl;
        }

        Chicken( const Chicken &chick )//I've written this function!! This function is a copy constructor ~
        {
            age = chick.age;
            int len = strlen(chick.name) + 1;
            name = new char[len];
            for (int i = 0; i < len; i++)
                name[i] = chick.name[i];
        }

        const Chicken &operator=( const Chicken &chick )//I've written this function as well!! This function is a copy assignment operator ~
        {
            if (this == &chick)
                return *this;
            MakeEmpty(); //I've written this function on line 20 and added this line to delete the original chicken.
            age = chick.age;
            int len = strlen(chick.name) + 1;
            name = new char[len];
            for (int i = 0; i < len; i++)
                name[i] = chick.name[i];
            return *this;
        }
};

int main()
{
    Chicken c(24, "Kunkun");
    c.printChicken();
    Chicken c1 = c;
    c1.printChicken();// to test the copy constructor
    Chicken c2;
    c2 = c1= c;
    c2.printChicken();// to test the copy assignment operator
}
// i've also used the Valgrind to check the memory leaks. Luckily, this code is fine.
// Here is the result of Valgrind:
// ==1442== Rerun with --leak-check=full to see details of leaked memory
// ==1442==
// ==1442== For lists of detected and suppressed errors, rerun with: -s
// ==1442== Rerun with --leak-check=full to see details of leaked memory
// ==1442==
// ==1442== For lists of detected and suppressed errors, rerun with: -s
// ==1442== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)