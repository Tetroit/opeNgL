#pragma once

#include <string>
#include <vector>

static class Utils {
public:
    static void Words(std::string line, std::vector<std::string>& res, char separator, bool ignoreEmpty = true) {

        res.clear();
        int wordStart = 0;
        for (int i = 0; i < line.size(); i++)
        {
            if (line[i] == separator)
            {
                if (wordStart != i || !ignoreEmpty)
                {
                    std::string word = line.substr(wordStart, i - wordStart);
                    res.push_back(word);
                    wordStart = i + 1;
                }
            }
        }
        if (wordStart < line.size())
        {
            std::string word = line.substr(wordStart, line.size() - wordStart);
            res.push_back(word);
        }

    }
    static std::shared_ptr<std::vector<std::string>> Words(std::string line, char separator, bool ignoreEmpty = true) {

        auto res = std::make_shared<std::vector<std::string>>();
        int wordStart = 0;
        for (int i = 0; i < line.size(); i++)
        {
            if (line[i] == separator)
            {
                if (wordStart != i || !ignoreEmpty)
                {
                    std::string word = line.substr(wordStart, i - wordStart);
                    res->push_back(word);
                    wordStart = i + 1;
                }
            }
        }
        if (wordStart < line.size())
        {
            std::string word = line.substr(wordStart, line.size() - wordStart);
            res->push_back(word);
        }
        return res;
    }
};