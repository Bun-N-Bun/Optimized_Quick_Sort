#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <numeric>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace std::chrono;

void manualSort(vector<int>& arr, int low, int high) {
    int N = high - low + 1;
    if (N <= 1) {
        return;
    } else if (N == 2) {
        if (arr[low] > arr[high]) {
            swap(arr[low], arr[high]);
        }
    } else if (N == 3) {
        if (arr[low] > arr[high - 1]) {
            swap(arr[low], arr[high - 1]);
        }
        if (arr[low] > arr[high]) {
            swap(arr[low], arr[high]);
        }
        if (arr[high - 1] > arr[high]) {
            swap(arr[high - 1], arr[high]);
        }
    }
}

int partition(vector<int>& arr, int low, int high, int pivot) {
    int i = low - 1;
    int j = high + 1;
    while (true) {
        while (arr[++i] < pivot);
        while (arr[--j] > pivot);
        if (i >= j) {
            return j;
        }
        swap(arr[i], arr[j]);
    }
}

void insertionSort(vector<int>& arr, int low, int high) {
    for (int i = low + 1; i <= high; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= low && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

int calculatePivot(vector<int>& arr, int low, int high) {
    int mid = (low + high) / 2;
    vector<int> leftSubarray(arr.begin() + low, arr.begin() + mid + 1);
    vector<int> rightSubarray(arr.begin() + mid + 1, arr.begin() + high + 1);

    double leftMean = accumulate(leftSubarray.begin(), leftSubarray.end(), 0.0) / leftSubarray.size();
    double rightMean = accumulate(rightSubarray.begin(), rightSubarray.end(), 0.0) / rightSubarray.size();

    int pivot = static_cast<int>((leftMean + rightMean) / 2);

    return pivot;
}

void quickSort(vector<int>& arr, int low, int high) {
    int N = high - low + 1;
    if (N <= 3) {
        manualSort(arr, low, high);
    } else if (N <= 100) {
        insertionSort(arr, low, high);
    } else {
        int pivot = calculatePivot(arr, low, high);
        int q = partition(arr, low, high, pivot);
        quickSort(arr, low, q);
        quickSort(arr, q + 1, high);
    }
}

int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 100);

    vector<int> data(101); // Increase the size of the data
    generate(data.begin(), data.end(), [&]() { return dis(gen); });

    auto start = high_resolution_clock::now(); // Start timer

    quickSort(data, 0, data.size() - 1);

    auto stop = high_resolution_clock::now(); // Stop timer
    auto duration = duration_cast<nanoseconds>(stop - start); // Calculate duration in nanoseconds

    cout << "Time taken by quickSort: " << scientific << duration.count() << " nanoseconds" << endl;

    return 0;
}
