//
// Created by eleri on 22/02/2023.
//

#include "NGramsCounter.h"

//definire numero dei thread nel programma e si prova a variare DONE
//esperimento fisso il numero di thread e aumento il numero di libri e
//poi fisso il numero di libri e vario i thread.
//ngram python 2 parall
//k-means 2 versioni openmp e cuda

using namespace std;



void NGramsCounter::countNGrams(const std::vector<std::string>& words) {
    map.clear();
    for(const auto & word : words){
        if(word.size() >= NGramLength) {
            vector<string> ngrams = extractNGramsFromWord(word);
            for (auto & ngram : ngrams) {
                if (!map[ngram]) {
                    map[ngram] = 1;
                } else {
                    map[ngram]++;
                }
            }
        }
    }
}

NGramsCounter::NGramsCounter(int nGramLength) : NGramLength(nGramLength) {}


vector<string> NGramsCounter::extractNGramsFromWord(const string& word) const {
    vector<string> ngrams;
    for(int i = 0 ; i<=word.size()-NGramLength; i++){
        ngrams.push_back(word.substr(i,NGramLength));
    }
    return ngrams;
}

const unordered_map<std::string, int> &NGramsCounter::getMap() const {
    return map;
}

void NGramsCounter::parallelCountNGrams(const vector<std::string> &words, int num_threads) {
    int size = static_cast<int>(words.size());
    map.clear();

#pragma omp parallel num_threads(num_threads)  default(none) shared(size, words)
    {

        unordered_map<string, int> threadMap;

#pragma omp for nowait
        for (int i=0; i < size; i++) {
            if (words[i].size() >= NGramLength) {
                vector<string> ngrams = extractNGramsFromWord(words[i]);
                for (auto &ngram: ngrams) {
                    if (!threadMap[ngram]) {
                        threadMap[ngram] = 1;
                    } else {
                        threadMap[ngram]++;
                    }
                }
            }
        }
//atomic oppure sequenzializzazione DONE
// separare i tempi
//#pragma omp critical
//        for (auto [ngram, count]: threadMap) {
//            if (!map[ngram]) {
//                map[ngram] = count;
//            } else {
//                map[ngram] += count;
//            }
//            map[ngram] += count;
//
//        }
        for (auto [ngram, count]: threadMap) {
#pragma omp critical
            map[ngram] += count;

        }

    }

}


