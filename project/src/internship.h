#pragma once
#include <string>
#include <chrono>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

#include <date/date.h>
#include <nlohmann/json.hpp>


using json = nlohmann::json;
using namespace date;
using namespace std::chrono;



namespace internship {

    struct DistrInfo{
        std::string name;
        std::string cycle;
        date::sys_days release;
        date::sys_days eol;
        int period;

        DistrInfo(const std::string& name, const std::string& cycle, const date::sys_days& r_date, const date::sys_days& e_date, int period)
            : name(name), cycle(cycle), release(r_date), eol(e_date), period(period) {}
    };



    // function to compare two distributions, used to sort the whole list
    bool compare(const DistrInfo distr1, const DistrInfo distr2);
    
    // function to transform date from string to ymd
    date::sys_days transform_date(const std::string dateStr);

    // function to load/read json file and parse into struct DistrInfo
    std::vector<DistrInfo> parse_json(const std::string& file);

    void output_list(const std::vector<DistrInfo>& distributions, int count);

    // do not remove this function
    void solution(const std::string& jsonFileName, int elementsCount);
}