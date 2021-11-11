#include <vector>
#include <map>

#include <iostream>
#include <fstream>
#include <regex>

#include "../Library/element.h"
#include "../Library/class.h"

#include "TextProcessor.h"



TextProcessor::TextProcessor(fs::path filename) : TextProcessor() {
    load_words(filename);
}

TextProcessor::TextProcessor(std::vector<std::pair<std::string, int>> v) : TextProcessor() {
    words = v;
    filled = true;
}


void TextProcessor::list_files(fs::path dirname) const {
    for (const auto& entry : fs::directory_iterator(dirname))
        std::cout << entry.path().filename() << std::endl;
}

void TextProcessor::load_words(fs::path filename) {
    clear_words();

    std::ifstream file(filename);
    if (!file) throw std::runtime_error("Can't open the file.");
        
    std::cout << "Loading..." << std::endl;

    std::map<std::string, int> dict;
    while (!file.eof()) {
        std::string str;
        file >> str;

        std::smatch result;
        if (std::regex_search(str, result, std::regex("\\b[a-zA-Z']+\\b"))) {
            for (std::string word : result) {
                std::transform(word.begin(), word.end(), word.begin(), ::tolower);
                dict[word]++;
            }
        }
    }
    file.close();

    for (const auto & [k, v] : dict) {
        words.push_back(std::pair<std::string, int>(k, v));
    }

    filled = true;
    return;
}

void TextProcessor::get_words(int min_len, int num) noexcept {
    if (num == 0) num = words.size();

    if (!sorted) {
        std::cout << "Sorting..." << std::endl;
        sort();
    }


    int count = 0;
    for (auto it = words.begin(); it != words.end(); it++) {
        std::string word = it->first;
        if (word.length() >= min_len) {
            std::cout << std::setw(21) << std::left << it->first <<
                it->second << std::endl;
            count++;
        }

        if (count >= num)
            break;
    }
}


void TextProcessor::clear_words() noexcept {
    words.clear();
    filled = false;
    sorted = false;

    return;
}

void TextProcessor::sort() {
    Stack s;
    s.push(Element(0, words.size() - 1));


    while (!s.isEmpty()) {
        Element e;
        s.pop(e);
        int l = e._a;
        int r = e._b;

        if (l >= r) continue;

        // Split
        int i = l;
        int j = r;
        std::pair<std::string, int> v = words[(l + r) / 2];
        do {
            while (cmp(words[i], v) < 0 && i < r)
                i++;
            while (cmp(words[j], v) > 0 && j > l)
                j--;
            if (i <= j)
                std::swap(words[i++], words[j--]);
        } while (i <= j);
        //

        s.push(Element(l, j));
        s.push(Element(i, r));
    }


    sorted = true;
    return;
}

int TextProcessor::cmp(std::pair<std::string, int> a, std::pair<std::string, int> b) const noexcept {
    if (a.second < b.second) return 1;
    else if (a.second > b.second) return -1;
    else return 0;
}