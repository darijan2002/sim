#include <iostream>
#include <random>
#include <chrono>

using namespace std;

int const N = 10;
int const N_MICE = 3;
int const N_CATS = 3;

enum class CELL_TYPE {
    EMPTY = 0,
    CAT,
    MOUSE
};

struct Cell {
    CELL_TYPE type = CELL_TYPE::EMPTY;
    int index = -1;
};

int main() {
    Cell field[N][N]{};
    default_random_engine rng(chrono::system_clock::now().time_since_epoch().count());

    uniform_int_distribution<int> dist(0, N - 1);
    vector<pair<int, int>> cats(N_CATS), mice(N_MICE);
    for (int i = 0; i < N_CATS; i++) {
        int ti, tj;
        ti = dist(rng);
        tj = dist(rng);
        while (field[ti][tj].type != CELL_TYPE::EMPTY) {
            ti = dist(rng);
            tj = dist(rng);
        }

        field[ti][tj] = {CELL_TYPE::CAT, i};
        cats[i] = {ti, tj};
    }
    for (int i = 0; i < N_MICE; i++) {
        int ti, tj;
        ti = dist(rng);
        tj = dist(rng);
        while (field[ti][tj].type != CELL_TYPE::EMPTY) {
            ti = dist(rng);
            tj = dist(rng);
        }

        field[ti][tj] = {CELL_TYPE::MOUSE, i};
        mice[i] = {ti, tj};
    }

    char enum_to_char[] = {'.', 'C', 'M'};
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            cout << enum_to_char[(int)field[i][j].type];
        }
        cout << endl;
    }

    return 0;
}