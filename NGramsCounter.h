//
// Created by eleri on 22/02/2023.
//
#include <unordered_map>
#include <string>
#include <vector>
class NGramsCounter{
public:
    void countNGrams(const std::vector<std::string>& words);

    void parallelCountNGrams(const std::vector<std::string>& words);

    explicit NGramsCounter(int nGramLength);

    const std::unordered_map<std::string, int> &getMap() const;

private:
    int NGramLength;
    std::unordered_map<std::string, int> map;



    std::vector<std::string> extractNGramsFromWord(const std::string& word) const;
};



