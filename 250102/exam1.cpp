#include <iostream>

template <typename T>
class SimpleVector {
private:
    T* data;                // 데이터를 저장할 동적 배열 포인터
    int currentSize = 0;        // 현재 원소의 개수
    int currentCapacity = 10;    // 배열의 크기 (용량)

public:
    // 기본 생성자: 크기가 10인 배열 생성
    SimpleVector()  {
        data = new T[currentCapacity]; // 크기가 10인 배열 할당
    }

    // 숫자를 하나 받는 생성자: 해당 숫자만큼 크기 조정
    SimpleVector(int capacity)  {
        currentCapacity = capacity;
        data = new T[currentCapacity]; // 주어진 크기의 배열 할당
    }

    // 소멸자: 동적 메모리 해제
    ~SimpleVector() {
        delete[] data;
    }

    // push_back: 배열의 맨 뒤에 원소 추가
    void push_back(const T& value) {
        if (currentSize < currentCapacity) {
            data[currentSize] = value;  // 배열에 원소 추가
            ++currentSize;
        }
        // 배열이 꽉 찼을 경우 아무 동작도 하지 않음
    }

    // pop_back: 배열의 마지막 원소 제거
    void pop_back() {
        if (currentSize > 0) {
            data[currentSize - 1] = T(); // 타입의 기본값으로 설정
            --currentSize;
        }
    }

    // size: 현재 원소의 개수를 반환
    int size() const {
        return currentSize;
    }

    // capacity: 내부 배열의 크기를 반환
    int capacity() const {
        return currentCapacity;
    }

    // print: 배열의 모든 원소를 출력
    void print() const {
        std::cout << "Dataset : ";  // 배열의 원소 출력
        for (int i = 0; i < currentSize; ++i) {
            std::cout << data[i] << " ";  // 배열의 원소 출력
        }
        std::cout << std::endl;
    }
};

int main() {
    int arraySize;
    
    // 사용자에게 배열 크기 입력 받기
    std::cout << "Enter the size of the vector (or press 0 to use default size 10): ";
    std::cin >> arraySize;

    // 입력값이 0이라면 기본 크기 10을 사용하고, 그렇지 않으면 입력한 크기로 벡터 생성
    SimpleVector<int> vec(arraySize > 0 ? arraySize : 10);

    // 몇 개의 원소를 추가
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);
    vec.push_back(40);

    // 크기와 용량 출력
    std::cout << "Size: " << vec.size() << std::endl;
    std::cout << "Capacity: " << vec.capacity() << std::endl;  // 사용자 입력값 또는 기본값 10

    // 마지막 원소 제거
    vec.pop_back();

    // 제거 후 크기 출력
    std::cout << "Size after pop_back: " << vec.size() << std::endl;
    vec.print();  // 원소 출력

    return 0;
}
