#include "Utils.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

namespace fre {
    bool cmp(pair<string, float> a, pair<string, float> b) {
        return a.second < b.second;
    }

    vector<string> sort(map<string, float> M) {
        vector<pair<string, float> > A;
        for (auto& it : M) {
            A.push_back(it);
        }
        sort(A.begin(), A.end(), cmp);
        vector<string> res;
        for (auto& it : A) {
            res.push_back(it.first);
        }
        return res;
    }

    string converTime(string date) {
        vector<string> dmy = split(date, '-');
        map<string, string> monthMap = {{"Jan", "01"}, {"Feb", "02"}, {"Mar", "03"}, {"Apr", "04"}, {"May", "05"}, {"Jun", "06"}, {"Jul", "07"}, {"Aug", "08"}, {"Sep", "09"}, {"Oct", "10"}, {"Nov", "11"}, {"Dec", "12"}};
        string day = dmy[0].size() == 1 ? "0"+dmy[0] : dmy[0];
        string month = monthMap[dmy[1]];
        string year = "20"+dmy[2];
        return year + "-" + month + "-" + day;
    }

    vector<string> split(string text, char delim) {
        string line;
        vector<string> vec;
        stringstream ss(text);
        while (std::getline(ss, line, delim)) {
            vec.push_back(line);
        }
        return vec;
    }

    size_t writeCallback(void* contents, size_t size, size_t nmemb, void* userp) {
        ((string*)userp)->append((char*)contents, size * nmemb);
        return size * nmemb;
    }

    map<string, string> processConfigFile(string configFile) {
        map<string, string> configMap;
        ifstream fin;
        fin.open(configFile, ios::in);
        string line, name, value;
        while (!fin.eof()) {
            getline(fin, line);
            stringstream sin(line);
            getline(sin, name, ':');
            getline(sin, value);
            configMap.insert(pair<string, string>(name, value));
        }
        return configMap;
    }

    vector<string> processSymbolFile(string configFile) {
        vector<string> symbolVector;
        ifstream fin;
        fin.open(configFile, ios::in);
        string line, symbol, description;
        while (!fin.eof()) {
            getline(fin, line);
            stringstream sin(line);
            getline(sin, symbol, ',');
            getline(sin, description);
            symbolVector.push_back(symbol);
        }
        return symbolVector;
    }

    map<string, vector<string>> processAnnouncementFile(string configFile) {
        map<string, vector<string>> annMap;
        ifstream fin;
        fin.open(configFile, ios::in);
        string line, symbol, date, periodEnding, estimate, reported, surprise, surprisePct;
        getline(fin, line);
        while (!fin.eof()) {
            vector<string> factors;
            getline(fin, line);
            stringstream sin(line);
            getline(sin, symbol, ',');
            getline(sin, date, ',');
            factors.push_back(date);
            getline(sin, periodEnding, ',');
            factors.push_back(periodEnding);
            getline(sin, estimate, ',');
            factors.push_back(estimate);
            getline(sin, reported, ',');
            factors.push_back(reported);
            getline(sin, surprise, ',');
            factors.push_back(surprise);
            getline(sin, surprisePct);
            factors.push_back(surprisePct);
            if (symbol.empty()) {
                continue;
            }
            annMap[symbol] = factors;
        }
        return annMap;
    }

    vector<string> bootstrapping(vector<string> symbols, int size) {
        vector<string> selectedSymbols;
        for (int i = 0; i < size; i++) {
            selectedSymbols.push_back(symbols[rand() % symbols.size()]);
        }
        return selectedSymbols;
    }
}
