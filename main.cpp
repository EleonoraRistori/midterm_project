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


int main() {
//    auto books = read_book_n_times("../Text/prova.txt",100);
    NGramsCounter nGramsCounter(3);
//    auto begin = chrono::high_resolution_clock::now();
//    nGramsCounter.countNGrams(books);
//    auto end = chrono::high_resolution_clock::now();
//    auto duration = chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
//    printf("Time for sequential algorithm   %.3f s |\n", (duration.count() * 1e-9));
//    printOccurences(nGramsCounter.getMap(), 5);
//    begin = chrono::high_resolution_clock::now();
//    nGramsCounter.parallelCountNGrams(books, 12);
//    end = chrono::high_resolution_clock::now();
//    duration = chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
//    printf("Time for parallel algorithm   %.3f s |\n", (duration.count() * 1e-9));
//    printOccurences(nGramsCounter.getMap(), 5);
    vector<string> words;
    vector<std::chrono::nanoseconds> sequentialDuration;
    vector<std::chrono::nanoseconds> parallelDuration;
//    for(int i=1; i<50; i++){
//        words =  read_book_n_times("../Text/Text.txt",i);
//        cout << i;
//        auto begin = chrono::high_resolution_clock::now();
//        nGramsCounter.countNGrams(words);
//        auto end = chrono::high_resolution_clock::now();
//        sequentialDuration.push_back(chrono::duration_cast<std::chrono::nanoseconds>(end - begin));
//        cout << i;
//    }

    for(int i=1; i<50; i++){
        cout << i;
        words =  read_book_n_times("../Text/Text.txt",i);
        cout << i;
        auto beginP = chrono::high_resolution_clock::now();
        cout << i;
        nGramsCounter.parallelCountNGrams(words, 12);
        cout << i;
        auto endP = chrono::high_resolution_clock::now();
        cout << i;
        parallelDuration.push_back(chrono::duration_cast<std::chrono::nanoseconds>(endP - beginP));
    }

    return 0;
}
