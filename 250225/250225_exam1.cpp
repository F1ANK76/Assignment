#include <iostream>
#include <vector>
using namespace std;

int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high]; // 피벗을 배열의 마지막 원소로 설정
    int i = low - 1; // i는 피벗보다 작은 원소들의 인덱스

    // low부터 high-1까지 반복
    for (int j = low; j <= high - 1; j++) {
        // 만약 arr[j]가 피벗보다 작으면
        if (arr[j] < pivot) {
            i++; // i를 증가시킨 후 arr[i]와 arr[j]를 교환
            swap(arr[i], arr[j]);
        }
    }

    // 피벗을 적절한 위치로 이동시키고 피벗의 인덱스를 반환
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        // 피벗을 기준으로 배열을 분할하고 피벗의 인덱스를 반환
        int pi = partition(arr, low, high);

        // 재귀적으로 분할된 부분을 정렬
        quickSort(arr, low, pi - 1);  // 피벗의 왼쪽 부분
        quickSort(arr, pi + 1, high); // 피벗의 오른쪽 부분
    }
}

int main() {
    vector<int> arr = { 10, 7, 8, 9, 1, 5 };
    int n = arr.size();

    cout << "정렬 전 배열: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    quickSort(arr, 0, n - 1);

    cout << "정렬 후 배열: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
