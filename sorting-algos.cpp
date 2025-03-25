#include <iostream>
#include <vector>
#include <climits>

using namespace std;

void printArr(const vector<int> in, const string msg) {
    cout << msg << "\n";
    for (auto elem: in) {
        cout << elem << " ";
    }
    cout << "\n";
}
/*
 * insertion sort
 *
*/

void insertionSortIterative(vector<int> in) {
    if (in.size() <= 1) {
        printArr(in, "Sorted array by insertionSortIterative");
    }
    bool sorted = false;
    for(int i=1; i < in.size(); ++i) {
        for(int j=i; j >= 0; --j)
            if(in[j] < in[j-1])
                swap(in[j], in[j-1]);
            else {
                if(sorted)
                    break;
            }
        sorted = true;
    }
    printArr(in, "Sorted array by insertionSortIterative");
}

void insertionSortRecursive(vector<int> &in, int i) {
    // exit/base case
    if(i >= in.size()) {
        printArr(in, "Sorted array by insertionSortRecursive");
        return;
    }

    // solve one case
    for(int j=i; j >= 0; --j)
        if(in[j] < in[j-1])
            swap(in[j], in[j-1]);

    // Rest, recursion will handle
    insertionSortRecursive(in, i+1);
}

void insertionSort(vector<int> in) {
    printArr(in, "Orig Array");
    insertionSortIterative(in);

    printArr(in, "Orig Array");
    insertionSortRecursive(in, 1);
}


/*
 * selection sort
 *
*/

/*
 * bubble sort
 *
*/

/*
 *
 *
*/

int main() {
    vector<int> arr1 = {13, 5, 16, 1, 12, 0};
    insertionSort(arr1);
    return 0;
}
