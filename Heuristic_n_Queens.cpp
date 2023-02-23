#include <iostream>
#include <ctime>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

pair<vector<int>,int> data;
int n;
double T;

void init() { // Khoi tao
    cout << "Input n = ";
    cin >> n;
    T = n;
    srand(time(0));
    vector<int> a;
    for(int i = 0; i < n; i++) {
        a.push_back(i);
    }
    for(int i = 0; i < n; i++) {
        int temp = rand() % a.size();
        data.first.push_back(a[temp]);
        a.erase(a.begin() + temp);
    }
    // Tinh H(n)
    int result = 0;
    for(int i = 0 ; i < n - 1; i++) {
        for(int j = i + 1 ; j < n; j++){
            if(j - i == data.first[j] - data.first[i] || data.first[i] + i == data.first[j] + j){
                result++;
            }
        }
    }
    data.second = result;
}

pair<vector<int>,int> Next_move(pair<vector<int>,int> data, int i, int j) {
    pair<vector<int>,int> temp = data;
    int heuristic = data.second;
    int jj = data.first[i];
    int ii = data.first[j];
    temp.first[i] = ii;
    temp.first[j] = jj;
    int count1 = 0, count2 = 0;

    for (int k = 0; k < data.first.size(); k++) {
        if (k != i) {
            if (ii + i == temp.first[k] + k
                || ii - i == temp.first[k] - k) {
                count1++;
            }

            if (jj + i == data.first[k] + k
                || jj - i == data.first[k] - k) {
                count2++;
            }
        }
        if (k != j) {
            if (jj + j == temp.first[k] + k
                || jj - j == temp.first[k] - k) {
                count1++;
            }
            if (ii + j == data.first[k] + k
                || ii - j == data.first[k] - k) {
                count2++;
            }
        }
    }
    temp.second = (heuristic - count2 + count1);
    return temp;
}

void show(pair<vector<int>,int> data) {
    for(int i = 0; i < n; i++) {
        cout << data.first[i] << " ";
    }
}

void solve() {
    srand(time(0));
    double p;
    int step = 0;
    while(T > 0) {
        if(data.second == 0){
            show(data);
            break;
        }
        T *= 0.99;
        int i = rand()%n;
        int j = rand()%n;
        pair<vector<int>, int> next_move = Next_move(data,i,j);
        if(next_move.second == 0) {
            cout << next_move.second << endl;
            cout << "Steps: " << step << endl;
            cout << "Result: ";
            show(next_move);
            break;
        }
        int delta = next_move.second - data.second;
        if(delta < 0) {
            data = next_move;
            step++;
            cout << next_move.second << endl;
        }
        else {
            p = exp(-delta/double(T));
            if(rand()/double(RAND_MAX) < p){
                data = next_move;
                step++;
                cout << next_move.second << endl;
            }
        }
    }
}

int main() {
    clock_t start = clock();
    init();
    cout << "The first value of heuristic: " << data.second << endl;
    solve();
    clock_t  finish = clock();
    cout << endl << "Time running: " << finish - start << " micro seconds." << endl;
    return 0;
}
