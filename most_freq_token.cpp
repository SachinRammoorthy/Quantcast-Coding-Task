#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>
#include <cassert>

using namespace std;

void getMostFreqToken(string fileName, string reqDate);

int main(int argc, char** argv){
    string fileName = argv[1];
    string reqDate = argv[3];
    getMostFreqToken(fileName, reqDate);
    
    return 0;
}

void getMostFreqToken(string fileName, string reqDate){
    
    ifstream fin;
    fin.open(fileName);
    unordered_map<string, int> tokenFreq;

    int maxTokenFreq = 1;

    string line = "";
    getline(fin, line);

    while(getline(fin, line)){
        string token = line.substr(0, line.find(','));
        string rest = line.substr(line.find(',')+1, line.size());
        string date = rest.substr(0, rest.find('T'));

        assert(date.size() == 10);

        // still haven't reached the required date, keep going
        if (date > reqDate) continue;

        if (date == reqDate){
            if (tokenFreq.find(token) == tokenFreq.end()){
                tokenFreq[token] = 1;
            } else {
                tokenFreq[token] += 1;
                maxTokenFreq = max(maxTokenFreq, tokenFreq[token]);
            }
        }

        // went past the required date, end the loop here
        if (date < reqDate) break;
    }

    if (tokenFreq.size() == 0) return;

    for (auto it : tokenFreq){
        if (it.second == maxTokenFreq){
            cout << it.first << "\n";
        }
    }

}