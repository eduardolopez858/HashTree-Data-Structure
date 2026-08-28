// AI generated testing
#include <iostream>
#include <unordered_map>
#include <vector>
#include <chrono>
#include "HashTree.h"  // include your implementation

using namespace std;
using namespace std::chrono;

// -------------------
// Timer Helper
// -------------------
long long measure_time(function<void()> func) {
    auto start = high_resolution_clock::now();
    func();
    auto stop = high_resolution_clock::now();
    return duration_cast<milliseconds>(stop - start).count();
}

// -------------------
// Benchmark Function
// -------------------
void run_benchmark(const vector<int>& elements, const string& label) {
    cout << "\n=== Benchmark: " << label << " ===\n";

    // ---------- unordered_map ----------
    {
        unordered_map<int,string> umap;

        auto insert_time = measure_time([&](){
            for (int k : elements) umap[k] = "val" + to_string(k);
        });

        auto search_time = measure_time([&](){
            for (int k : elements) {
                volatile auto it = umap.find(k);
            }
        });

        auto delete_time = measure_time([&](){
            for (int k : elements) umap.erase(k);
        });

        cout << "unordered_map -> find: " << search_time << " ms, insert: " << insert_time << " ms, remove: " << delete_time << " ms\n";
    }

    // ---------- HashTree ----------
    {
        HashTree ht;

        auto insert_time = measure_time([&](){
            for (int k : elements) ht.map(k, "val" + to_string(k));
        });

        auto search_time = measure_time([&](){
            for (int k : elements) {
                volatile auto v = ht.find(k);
            }
        });

        auto delete_time = measure_time([&](){
            for (int k : elements) ht.remove(k);
        });

        cout << "HashTree -> find: " << search_time << " ms, insert: " << insert_time << " ms, remove: " << delete_time << " ms\n";
    }
}

// -------------------
// Main
// -------------------
int main() {
    // Normal case: unique keys
    vector<int> normal_elements;
    for (int i = 0; i < 100000; i++) normal_elements.push_back(i);
    run_benchmark(normal_elements, "Average Case (unique keys)");

    // Worst case: all keys collide
    // (simulate collisions by using the same key over and over)
    vector<int> bad_elements;
    for (int i = 0; i < 100000; i++) bad_elements.push_back(42);
    run_benchmark(bad_elements, "Worst Case (all collide)");

    return 0;
}
