#include <iostream>
#include <string>


class C {
    
};

template <typename T>
class A {
    public:
            
        A(const std::string & value) {
            std::cout << "string" << std::endl;
            value_ = value;
        }

        A(std::string&& some_class) {}

        A(const C & some_class) {
            class_ = &some_class;
        }

        A() : class_(nullptr) {}
    
        virtual void foo() {
            std::cout << "Method A::foo" << std::endl;
        }

        A& operator=(const A & some_class) {
            value_ = some_class.value_;
            return *this;
        }

        static void bar(T class_a, A<C> * class_b) {
            std::cout << "Method A::bar" << std::endl;
        }

        A<C> operator+=(A<C> right) {
            return *this;
        }        

    private:
        const T * class_;
        std::string value_;
};
 
class B : public A<C> {
    public:
        virtual void foo() {
            std::cout << "B::foo()" << std::endl;
        }
};
 
int main() {
    A<C>* a = new B();
     
    A<C> a2{C()}; // подсказка по запросу
    
    a->foo(); // calls B::foo - 1. виртуальные функции и их переопределение
    
    a2.foo(); // calls A::foo
    
    A<C>::bar(C(), a);
    
    A<C> a3;
    
    a3 = a2; // подсказка по запросу
    
    a2 = std::move(a3);
    
    a3 += a2;
    
    A<std::string> a4{"asdf"}; // надо чтобы вызывался конструктор с std::string
    
    std::string initializer{"foo"};
    // A a5{initializer}; // надо чтобы вызывался конструктор как в a4, но ничего не копировал и не создавал
    
    
    return 0;
}