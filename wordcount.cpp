#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <ranges>
#include <algorithm>
#include <map>
#include <vector>
#include <cctype>

std::string removePunctuation(const std::string &str)
{
    std::string result;
    for (char c : str)
    {
        if (std::isalnum(c) || c == ' ')
        {
            result += c;
        }
    }
    return result;
}

int main()
{
    std::fstream f("discoveryofindia.txt");
    std::string line;
    std::map<std::string, int> word_count;

    while (std::getline(f, line))
    {
        std::istringstream iss(line);
        std::string word;

        while (iss >> word)
        {
            std::transform(word.begin(), word.end(), word.begin(), [](unsigned char c)
                           { return std::tolower(c); });
            word = removePunctuation(word);

            if (!word.empty())
            {
                if (word_count.find(word) != word_count.end())
                {
                    word_count[word]++;
                }
                else
                {
                    word_count[word] = 1;
                }
            }
        }
    }
    std::vector<std::pair<std::string, int>> count;
    for (auto e : word_count)
    {
        count.push_back(e);
    }
    std::sort(count.begin(), count.end(), [](auto e, auto e2)
              { return e.second < e2.second; });

    for (auto v : count)
    {
        std::cout << v.first << " : " << v.second << std::endl;
    }

    return 0;
}