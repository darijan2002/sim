#include <iostream>
#include <random>
#include <chrono>
#include <list>
#include <vector>

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
    int ipos = -1, jpos = -1;
};

struct Cat : Cell {
    static int CAT_INSTANCES;
    int radius, cooldown, speed;

    Cat() : Cell() {
        type = CELL_TYPE::CAT;
        index = CAT_INSTANCES++;
        radius = 1;
        cooldown = 0;
        speed = 2;
    }

    Cat(int i, int j) : Cat() {
        ipos = i;
        jpos = j;
    }

};

int Cat::CAT_INSTANCES = 0;

struct Mouse : Cell {
    static int MOUSE_INSTANCES;

    Mouse() : Cell() {
        type = CELL_TYPE::MOUSE;
        index = MOUSE_INSTANCES++;
    }

    Mouse(int i, int j) : Mouse() {
        ipos = i;
        jpos = j;
    }
};

int Mouse::MOUSE_INSTANCES = 0;

default_random_engine rng(chrono::system_clock::now().time_since_epoch().count());
uniform_int_distribution<int> dist(0, N - 1);

// what if we use lists instead of vectors?
void putAnimalsOnRandomLocations(vector<Cat> &cats, vector<Mouse> &mice) {
    CELL_TYPE field[N][N]{};

    for (int i = 0; i < N_CATS; i++) {
        int ti, tj;
        ti = dist(rng);
        tj = dist(rng);
        while (field[ti][tj] != CELL_TYPE::EMPTY) {
            ti = dist(rng);
            tj = dist(rng);
        }

        // field[ti][tj] = {CELL_TYPE::CAT, i};
        cats.emplace_back(ti, tj);
    }
    for (int i = 0; i < N_MICE; i++) {
        int ti, tj;
        ti = dist(rng);
        tj = dist(rng);
        while (field[ti][tj] != CELL_TYPE::EMPTY) {
            ti = dist(rng);
            tj = dist(rng);
        }

        // field[ti][tj] = {CELL_TYPE::MOUSE, i};
        mice.emplace_back(ti, tj);
    }
}

void printField(vector<Cat> const &cats, vector<Mouse> const &mice) {
    vector<string> field(N, string(N, '.'));
    for (auto &c: cats) field[c.ipos][c.jpos] = 'C';
    for (auto &m: mice) field[m.ipos][m.jpos] = 'M';

    for (auto &str: field) cout << str << endl;
}

int runIteration(vector<Cat> &cats, vector<Mouse> &mice, int limit = 600) {
    int tick;
    if(limit <= 0) limit = 2000; // no (reasonable) limit

    for(tick = 0; !mice.empty() && tick < limit; tick++)
    {
        vector<vector<Mouse>::iterator> eatenMice;
        // update cats
        for(auto& cat : cats)
        {
            // get mice in cat's radius
            // if multiple, then eat the furthest
            // if none, go to the nearest

            // animals move in all directions
        }

        // update mice
        // 1. delete eaten mice
        for(auto& mouse : eatenMice) mice.erase(mouse);

        // 2. move the rest
        for(auto& mouse : mice)
        {

        }
    }

    // -1 - DNF
    return (tick == limit) ? -1 : limit;
}

int main() {
    // Cell* field[N][N];

    vector<Cat> cats;
    vector<Mouse> mice;
    putAnimalsOnRandomLocations(cats, mice);

    cout << "BEFORE: " << endl;
    printField(cats, mice);
    cout << endl;

    int timeToFinish = runIteration(cats, mice);
    cout << timeToFinish << endl;

    cout << "AFTER: " << endl;
    printField(cats, mice);
    cout << endl;

    return 0;
}