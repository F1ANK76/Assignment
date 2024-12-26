#include <iostream>
using namespace std;

// 합계를 구하는 함수
int calculateSum(int arr[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];  // 배열 요소를 더함
    }
    return sum;
}

// 평균을 구하는 함수
double calculateAverage(int sum, int size) {
    return static_cast<double>(sum) / size;  // 합계를 크기만큼 나누어 평균 계산
}

int main() {
    int numbers[5];  // 숫자 5개를 저장할 배열
    int sum;  // 합계 변수
    double average;  // 평균 변수

    // 사용자로부터 5개의 숫자 입력 받기
    cout << "5개의 숫자를 입력하세요: ";
    for (int i = 0; i < 5; i++) {
        cin >> numbers[i];  // 배열에 숫자 입력
    }

    // 합계를 계산
    sum = calculateSum(numbers, 5);

    // 평균을 계산
    average = calculateAverage(sum, 5);

    // 합계와 평균 출력
    cout << "합계: " << sum << endl;
    cout << "평균: " << average << endl;

    return 0;
}
