#include <iostream>
#include <vector>
#include "heap.h"
using namespace std;

void ejemplo_1 () {
    utec::heap<int> h;
    vector v {10, 7, 27, 50, 3, -1, 2, 10};
    for (const auto& item: v)
        h.push(item);

    while(!h.empty()) {
        cout << h.top() << " ";
        h.pop();
    }
}

void ejemplo_2 () {
    vector v {10, 7, 27, 50, 3, -1, 2, 10};
    utec::heap<int> h(v);

    while(!h.empty()) {
        cout << h.top() << " ";
        h.pop();
    }
    cout << endl;
    utec::heap<int> h1(v);
    h1.replace(7, 20);
    while(!h1.empty()) {
        cout << h1.top() << " ";
        h1.pop();
    }
}

void ejemplo_3 () {
    vector v {10, 7, 27, 50, 3, -1, 2, 10};
    utec::heap<int, vector, greater<>> h(v);

    while(!h.empty()) {
        cout << h.top() << " ";
        h.pop();
    }
}

void ejemplo_4 () {
    vector v {10, 7, 27, 50, 3, -1, 2, 10};
    auto compare_greater = [](auto a, auto b) { return a > b; };
    utec::heap<int, vector, decltype(compare_greater)> h(v, compare_greater);

    while(!h.empty()) {
        cout << h.top() << " ";
        h.pop();
    }
}

int main() {
    ejemplo_1();
    cout << endl;
    ejemplo_2();
    cout << endl;
    ejemplo_3();
    cout << endl;
    ejemplo_4();
    return 0;
}
