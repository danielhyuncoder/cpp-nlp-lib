#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <string>
using namespace std;
namespace lib{
    std::vector<std::vector<std::string>> importFromJSON(std::string point, int labels);
    class NLP{
       public:
       NLP(vector<vector<string>> trainD);
       NLP(string s);
       NLP();
       void fit(int epochs);
       int predict(string s);
       void setRate(double d);
       void evaluate(vector<vector<string>> test_data);
       double getWeightOfWord(string s);
       void encodeTo(string fName);
       void fromEncoded(string fName);
       pair<double,int> getFullPredict(string s);
       private:
       map<string, pair<double, int>> wordb;
       vector<vector<string>> train;
       pair<int, vector<pair<string,double>>> predict_test_mode(string s);
       void optimize(pair<int, vector<pair<string,double>>> p);
       double total;
       vector<string> uC;
       double rate=2.0;
       int nLabels=0;
    };
}