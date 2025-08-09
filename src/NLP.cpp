#include "../include/NLP.h"
#include <map>
#include <fstream>
#include "../include/json.hpp"

using json = nlohmann::json;
namespace lib {
    std::vector<std::vector<std::string>> importFromJSON(std::string point, int labels){
        std::ifstream file(point);
        json j;
        file >> j;
        std::vector<std::vector<std::string>> trainData;
        for (int i =0;i<labels;i++) {trainData.push_back({});};
        
        for (auto& data : j){
            trainData[data["label"]].push_back(data["text"]);
        }
        return trainData;
    }

    NLP::NLP(){}
    NLP::NLP(string s){
        this->fromEncoded(s);
    }
    NLP::NLP(vector<vector<string>> trainD) {
        this->train=trainD;
        double count = 0;
        vector<string> uS;
        
        for (int i =0;i<trainD.size();i++){
            for (int k = 0;k<trainD[i].size();k++){
                string curr = "";
                for (int j=0;j<trainD[i][k].length();j++){
                   if (trainD[i][k][j] == ' '){
                      // cout << curr << endl;
                    if (curr.length() > 0){
                        if (this->wordb.find(curr) == this->wordb.end()){
                            uS.push_back(curr);
                            this->wordb[curr]={0.0,i};
                            count++;
                        }
                    }
                    curr="";
                } else {
                    //cout << train[i][k][j] << endl;
                    curr+=trainD[i][k][j];
                }
                }
                if (curr.length() > 0){
                        if (this->wordb.find(curr) == this->wordb.end()){
                            uS.push_back(curr);
                            this->wordb[curr]={0.0,i};
                            count++;
                        }
                    }
            }
        }
        for (int i =0;i<uS.size();i++){
            this->wordb[uS[i]].first=(1.0/count);
        }
        this->uC=uS;
        this->total=count;
        this->nLabels=trainD.size();
    }
    
    pair<double, int> NLP::getFullPredict(string s){
        vector<double> score (this->nLabels, 0.0);
        string c = "";
        int prevLabel=-1;
        int lblCount=2;
        for (int i =0;i<s.length();i++){
            if (s[i] == ' '){
                if (c.length() > 0 && this->wordb.find(c) != this->wordb.end()){
                    pair<double,int> p = this->wordb[c];
                    if (prevLabel == p.second){
                        score[p.second]+=p.first*lblCount;
                        lblCount++;
                    } else {
                        score[p.second]+=p.first;
                        lblCount=2;
                    }
                    prevLabel=p.second;
                }
                c="";
            } else {
                c+=s[i];
            }
        }
        if (c.length() > 0 && this->wordb.find(c) != this->wordb.end()){
                    pair<double,int> p = this->wordb[c];
                    if (prevLabel == p.second){
                        score[p.second]+=p.first*lblCount;
                        lblCount++;
                    } else {
                        score[p.second]+=p.first;
                        lblCount=2;
                    }
                    prevLabel=p.second;
                }
        pair<double, int> ans;
        for (int i =0;i<score.size();i++){
            if (score[i] > ans.first){
                ans.first=score[i];
                ans.second=i;
            }
        }
        return ans;
    }
    
    
    
    int NLP::predict(string s){
        vector<double> score (this->nLabels, 0.0);
        string c = "";
        int prevLabel=-1;
        int lblCount=2;
        for (int i =0;i<s.length();i++){
            if (s[i] == ' '){
                if (c.length() > 0 && this->wordb.find(c) != this->wordb.end()){
                    pair<double,int> p = this->wordb[c];
                    if (prevLabel == p.second){
                        score[p.second]+=p.first*lblCount;
                        lblCount++;
                    } else {
                        score[p.second]+=p.first;
                        lblCount=2;
                    }
                    prevLabel=p.second;
                }
                c="";
            } else {
                c+=s[i];
            }
        }
        if (c.length() > 0 && this->wordb.find(c) != this->wordb.end()){
                    pair<double,int> p = this->wordb[c];
                    if (prevLabel == p.second){
                        score[p.second]+=p.first*lblCount;
                        lblCount++;
                    } else {
                        score[p.second]+=p.first;
                        lblCount=2;
                    }
                    prevLabel=p.second;
                }
        pair<double, int> ans;
        for (int i =0;i<score.size();i++){
            if (score[i] > ans.first){
                ans.first=score[i];
                ans.second=i;
            }
        }
        return ans.second;
    }
    pair<int, vector<pair<string, double>>> NLP::predict_test_mode(string s) {
        vector<pair<double, vector<pair<string, double>>>> score (this->nLabels, {0.0, {}});
        string c = "";
        int prevLabel=-1;
        int lblCount=2;
        for (int i =0;i<s.length();i++){
            if (s[i] == ' '){
                if (c.length() > 0 && this->wordb.find(c) != this->wordb.end()){
                    pair<double,int> p = this->wordb[c];
                    if (prevLabel == p.second){
                        score[p.second].first+=p.first*lblCount;
                        score[p.second].second.push_back({c,p.first*lblCount});
                        lblCount++;
                    } else {
                        score[p.second].first+=p.first;
                        score[p.second].second.push_back({c,p.first});
                        lblCount=2;
                    }
                    prevLabel=p.second;
                }
                c="";
            } else {
                c+=s[i];
            }
        }
        if (c.length() > 0 && this->wordb.find(c) != this->wordb.end()){
                    pair<double,int> p = this->wordb[c];
                    if (prevLabel == p.second){
                        score[p.second].first+=p.first*lblCount;
                        score[p.second].second.push_back({c,p.first*lblCount});
                        lblCount++;
                    } else {
                        score[p.second].first+=p.first;
                        score[p.second].second.push_back({c,p.first});
                        lblCount=2;
                    }
                    prevLabel=p.second;
                }
        pair<int, vector<pair<string,double>>> ans;
        double lar = 0.0;
        for (int i =0;i<score.size();i++){
            if (score[i].first > lar){
                lar=score[i].first;
                ans.first=i;
                ans.second=score[i].second;
            }
        }
        return ans;
    }
    void NLP::setRate(double d){
        this->rate=d;
    }
    void NLP::optimize(pair<int, vector<pair<string,double>>> p){
        string mS="";
        double lar = 0.0;
        map<string, double> mp;
        for (int i=0;i<p.second.size();i++){
            mp[p.second[i].first]+=p.second[i].second;
            if (mp[p.second[i].first] > lar){
                lar=p.second[i].second;
                mS=p.second[i].first;
            }
        }
        // Decreasing the weight of a word
        double k = this->wordb[mS].first - (this->wordb[mS].first / rate);
        this->wordb[mS].first /= rate;
        // Redistribution of the lost weight.
        double evenD = (k/this->total);
        for (int i =0;i<this->uC.size();i++){
            if (this->uC[i] != mS){
                this->wordb[this->uC[i]].first +=evenD;
            }
        }
        
        
    }
    void NLP::fit(int epochs){
        int e=1;
        while (e<=epochs){
            double correct=0.0;
            double outOf=this->train.size()*this->train[0].size();
            for (int i =0;i<this->train.size();i++){
                // i == label
                for (int j =0;j<this->train[i].size();j++){
                    pair<int, vector<pair<string,double>>> p = this->predict_test_mode(this->train[i][j]);
                    if (p.first == i) {
                        correct+=1;
                    } else {
                        this->optimize(p);
                    }
                }
            }
            double acc = (correct/outOf);
            cout << "Epoch : " << e << " :: ACC :: " << acc << endl;
            e++;
        }
    }
    void NLP::evaluate(vector<vector<string>> test_data) {
            double correct=0.0;
            double outOf=test_data.size()*test_data[0].size();
            for (int i =0;i<test_data.size();i++){
                // i == label
                for (int j =0;j<test_data[i].size();j++){
                    pair<int, vector<pair<string,double>>> p = this->predict_test_mode(test_data[i][j]);
                    if (p.first == i) {
                        correct+=1;
                    } else {
                        this->optimize(p);
                    }
                }
            }
            double acc = (correct/outOf);
            cout << "ACC :: " << acc << endl;
    }
    double NLP::getWeightOfWord(string s){
        if (this->wordb.find(s) != this->wordb.end()){
            return this->wordb[s].first;
        }
        return -1;
    }
    void NLP::encodeTo(string s){
         json j;
         for (int i =0;i<this->uC.size();i++){
            j.push_back({
                {"word", this->uC[i]},
                {"weight", this->wordb[this->uC[i]].first},
                {"label", this->wordb[this->uC[i]].second}
            });
            
        }
        std::ofstream file(s);
        file << j.dump(4);
        file.close();

        
    }
    void NLP::fromEncoded(string s){
        std::ifstream file(s);
        json j;
        file >> j;
        std::map<int, bool> mp;
        for (auto& save_weight : j){
            if (!mp[save_weight["label"]]){
                this->nLabels++;
                mp[save_weight["label"]]=true;
            }
            this->wordb[save_weight["word"]]={save_weight["weight"],save_weight["label"]};
        }
        cout << "Model Loaded Sucessfully." << endl;
    }
}