#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

const int LIMIT_X = 20;
const int LIMIT_Y = 20;
const int STEP_DELAY_MS = 100;

mutex output_mutex;

void goldfishMovement(int id, double speed) {
    double x = 0;
    while (x <= LIMIT_X) {
        {
            lock_guard<mutex> lock(output_mutex);
            cout << "Goldfish #" << id << " at X = " << x << endl;
        }
        this_thread::sleep_for(chrono::milliseconds(STEP_DELAY_MS));
        x += speed;
    }
    {
        lock_guard<mutex> lock(output_mutex);
        cout << "Goldfish #" << id << " reached the end." << endl;
    }
}

void guppyMovement(int id, double speed) {
    double y = 0;
    while (y <= LIMIT_Y) {
        {
            lock_guard<mutex> lock(output_mutex);
            cout << "Guppy #" << id << " at Y = " << y << endl;
        }
        this_thread::sleep_for(chrono::milliseconds(STEP_DELAY_MS));
        y += speed;
    }
    {
        lock_guard<mutex> lock(output_mutex);
        cout << "Guppy #" << id << " reached the end." << endl;
    }
}

int main() {
    const double V = 5.0;

    thread goldfish1(goldfishMovement, 1, V);
    thread goldfish2(goldfishMovement, 2, V);
    thread guppy1(guppyMovement, 1, V);
    thread guppy2(guppyMovement, 2, V);

    goldfish1.join();
    goldfish2.join();
    guppy1.join();
    guppy2.join();

    cout << "All fish have completed their journey." << endl;
    return 0;
}
