
#include <unordered_map>
#include <string>
#include <vector>

class NGramsCounter{
public:

    explicit NGramsCounter(int nGramLength);
    virtual ~NGramsCounter();

    void parallelCountNGrams(const std::vector<std::string>& words, int num_threads);

    void countNGrams(const std::vector<std::string>& words);

    const std::unordered_map<std::string, int> &getMap() const;

private:
    int NGramLength;
    std::unordered_map<std::string, int> map;
    std::vector<std::string> extractNGramsFromWord(const std::string& word) const;
};



