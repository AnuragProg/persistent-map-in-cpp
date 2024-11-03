#include <cstdio>
#include <string>
#include <iostream>
#include <fstream>
#include <unordered_map>

class PersistentMap{
private:
    std::string name;
    const std::string limiter;
public:
    PersistentMap(const std::string name, const std::string limiter): name(name), limiter(limiter){}

    bool has(const std::string key){
        std::ifstream file(this->name);
        if(!file){
            throw "unable to open " + this->name;
        }
        std::string line;
        while(std::getline(file, line)){
            size_t limiter_idx = line.find(this->limiter);
            if(limiter_idx == std::string::npos) continue;

            std::string k = line.substr(0, limiter_idx);
            if(k == key){
                return true;
            }
        }
        file.close();
        return false;
    }

    void set(const std::string key, const std::string value){
        std::unordered_map<std::string, std::string> _mp;
        std::string line;
        bool key_inserted_or_updated = false;

        std::ifstream prev(this->name);
        while(std::getline(prev, line)){
            size_t limiter_idx = line.find(this->limiter);
            if(limiter_idx == std::string::npos) continue;
            std::string k = line.substr(0, limiter_idx);
            std::string v = line.substr(limiter_idx+1, line.size()-limiter_idx);
            if(k == key){
                _mp[k] = value;
                key_inserted_or_updated = true;
            }else{
                _mp[k] = v;
            }
        }
        prev.close();

        if(!key_inserted_or_updated){ // in case insertion or updation didn't happen
            _mp[key] = value;
        }

        std::ofstream cur(this->name, std::ios::out | std::ios::trunc);
        if(!cur){
            throw "unable to open " + this->name;
        }
        for(auto& kv: _mp){
            line = kv.first + this->limiter + kv.second;
            // std::cout << line << std::endl;
            cur << line << "\n";
        }
        cur.close();
    }

    std::string get(const std::string key){
        std::ifstream file(this->name);
        if(!file){
            throw "unable to open " + this->name;
        }
        std::string line;
        while(std::getline(file, line)){
            size_t limiter_idx = line.find(this->limiter);
            if(limiter_idx == std::string::npos) continue;

            std::string k = line.substr(0, limiter_idx);
            if(k == key){
                file.close();
                return line.substr(limiter_idx+1, line.size()-limiter_idx);
            }
        }
        file.close();
        return "";
    }
};
