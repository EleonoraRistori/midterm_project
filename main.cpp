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

vector<string> read_book_n_times(const string& fileName, int n){
    vector<string> words;
    vector<string> text_words;
    text_words = read_text(fileName);
    for(int i=0; i<n; i++){
        words.insert(std::end(words), std::begin(text_words), std::end(text_words));
    }
    return words;
}

void printHistogram(const std::unordered_map<std::string, int>& map, int n){
    //sort the histogram
    priority_queue<pair<int, string>> queue;
    for (auto& [ngram, num]: map) {
        queue.push({num, ngram});
    }

    // print the most common ngrams

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

void printOccurences(const std::unordered_map<std::string, int>& map, int n){
    //sort the histogram
    priority_queue<pair<int, string>> queue;
    for (auto& [ngram, num]: map) {
        queue.push({num, ngram});
    }

    // print the most common ngrams

    for(int i=0; i<n; i++){
        cout << queue.top().second << ": " << queue.top().first << " \n";

        queue.pop();
    }

}


void saveArray (int num_points, vector<chrono::milliseconds> array, string filename){
    std::ofstream performance;
    performance.open (filename);
    for(int point_id=0; point_id<num_points; point_id++){
        performance << array[point_id].count() ;
        performance << "\n";
    }
}



int main() {

    NGramsCounter nGramsCounter(3);
    vector<string> words;
    vector<std::chrono::milliseconds> sequentialDuration;
    vector<std::chrono::milliseconds> parallelDuration;
    int num_iteration = 25;


    for(int i=1; i<num_iteration; i++){
        words =  read_book_n_times("../Text/Text.txt", 50);
        std::cout << i;
        auto beginP = chrono::high_resolution_clock::now();
        nGramsCounter.parallelCountNGrams(words, i);
        auto endP = chrono::high_resolution_clock::now();
        parallelDuration.push_back(chrono::duration_cast<std::chrono::milliseconds>(endP - beginP));
    }
    saveArray(num_iteration, parallelDuration, "threads_time.csv");

    for(int i=1; i<num_iteration; i++){
        words =  read_book_n_times("../Text/Text.txt",i*5);
        std::cout << i;
        auto begin = chrono::high_resolution_clock::now();
        nGramsCounter.countNGrams(words);
        auto end = chrono::high_resolution_clock::now();
        sequentialDuration.push_back(chrono::duration_cast<std::chrono::milliseconds>(end - begin));
    }

    for(int i=1; i<num_iteration; i++){
        words =  read_book_n_times("../Text/Text.txt",i*5);
        std::cout << i;
        auto beginP = chrono::high_resolution_clock::now();
        nGramsCounter.parallelCountNGrams(words, 12);
        auto endP = chrono::high_resolution_clock::now();
        parallelDuration.push_back(chrono::duration_cast<std::chrono::milliseconds>(endP - beginP));
    }
    saveArray(num_iteration, sequentialDuration, "time.csv");
    saveArray(num_iteration, parallelDuration, "p_time.csv");
    return 0;
}
