#include <iostream>
using namespace std;

// Animal 클래스 정의
class Animal {
public:
    virtual void makeSound() const = 0; // 순수 가상 함수
    virtual ~Animal() {} // 가상 소멸자
};

// Dog 클래스, Animal 클래스 상속
class Dog : public Animal {
public:
    void makeSound() const override {
        cout << "Bark!" << endl; // 개의 소리
    }
};

// Cat 클래스, Animal 클래스 상속
class Cat : public Animal {
public:
    void makeSound() const override {
        cout << "Meow!" << endl; // 고양이의 소리
    }
};

// Cow 클래스, Animal 클래스 상속
class Cow : public Animal {
public:
    void makeSound() const override {
        cout << "Moo!" << endl; // 소의 소리
    }
};

int main() {
    // Animal 타입의 포인터 배열 선언
    Animal* animals[3];

    // 배열에 각 동물 클래스 객체 생성
    animals[0] = new Dog();
    animals[1] = new Cat();
    animals[2] = new Cow();

    // 동물들의 소리를 반복문으로 출력
    for (int i = 0; i < 3; ++i) {
        animals[i]->makeSound(); // 각 동물의 makeSound 호출
    }

    // 메모리 해제
    for (int i = 0; i < 3; ++i) {
        delete animals[i];
    }

    return 0;
}
