#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <chrono>
#include "NGramsCounter.h"


using namespace std;

vector<string> read_text(const string& fileName){
    ifstream input(fileName);
    if(!input.is_open()){
        throw runtime_error("Cannot open file " + fileName + "\n");
    }
    cout << "Start reading file\n";
    vector<string> words;
    string word;
    while(input >> word) {
        string noPunctWord;
        for (char c: word) {
            if (!ispunct(c)) {
                noPunctWord += tolower(c);
            }
        }
        if (!noPunctWord.empty()) {
            words.push_back(noPunctWord);
        }
    }
    return words;
}

void printHistogram(const std::unordered_map<std::string, int>& map, int n){
    //sort the histogram
    priority_queue<pair<int, string>> queue;
    for (auto& [ngram, num]: map) {
        queue.push({num, ngram});
    }

    // prinit the most common ngrams

    for(int i=0; i<n; i++)
    {       cout << queue.top().second << "|";
            for (int j = 0; j < queue.top().first; j++)
            {
                printf("%c", (char)254u);
            }
            printf("\n");
            queue.pop();
    }

}


int main() {
    auto words = read_text("../Text/Text.txt");
    NGramsCounter nGramsCounter(3);
    auto begin = chrono::high_resolution_clock::now();
    nGramsCounter.countNGrams(words);
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    printf("Time for sequential algorithm   %.3f s |\n", (duration.count() * 1e-9));
    //printHistogram(nGramsCounter.getMap(), 4);
    begin = chrono::high_resolution_clock::now();
    nGramsCounter.parallelCountNGrams(words);
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    printf("Time for parallel algorithm   %.3f s |\n", (duration.count() * 1e-9));
    //printHistogram(nGramsCounter.getMap(), 4);

    return 0;
}
