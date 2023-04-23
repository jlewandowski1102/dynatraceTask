#include "internship.h"


namespace internship {

    bool compare(const DistrInfo distr1, const DistrInfo distr2){
        return distr1.period > distr2.period;
    }

    date::sys_days transform_date(const std::string dateStr){
        //setting a timestamp
        date::sys_seconds tp;
        //creating a stream to use parse() function
        std::istringstream is(dateStr);
        //parsing the date to ymd format
        is >> date::parse("%F", tp);
        //rounding the date to days
        auto finalDate = date::floor<date::days>(tp);
        return finalDate;
    }

    std::vector<DistrInfo> parse_json(const std::string& file){
        std::ifstream f(file);
        json data = json::parse(f);
        std::vector<DistrInfo> distributions;
        
        for (const auto& elem : data){
            if (elem["os"] == true){
                //getting the name of OS
                const std::string name = elem["name"].get<std::string>();
                //creating iterable array of versions
                const auto& versions_array = elem["versions"];
                // loop to iterate through all versions of OS system.
                for (const auto& version : versions_array){
                    try{
                        //getting the cycle of each version
                        const std::string cycle = version["cycle"].get<std::string>();
                        //transforming dates from string to ymd
                        auto release = transform_date(version["releaseDate"].get<std::string>());
                        auto eol = transform_date(version["eol"].get<std::string>());
                        //calculating period
                        const int period = (eol-release).count()+1;
                        //pushing complete element with calculated period
                        distributions.emplace_back(name, cycle, release, eol, period);
                    } catch(...){
                        //Ignore incorrect values
                    }

                }
            }

        }
        //sorting an array by period time, descending (using compare() function as comparator)
        std::sort(distributions.begin(), distributions.end(), compare);

        return distributions;
    }

    void output_list(const std::vector<DistrInfo>& distributions, int elementsCount){
        //loop to iterate until elementsCount (command line argument COUNT)
        for(int i=0;i<elementsCount;i++){
            const auto& version = distributions[i];
            //print the result in correct format
            std::cout<< version.name << " " << version.cycle << " " <<version.period << "\n";
        }

    }

    void solution(const std::string& jsonFileName, int elementsCount) {
        std::vector<DistrInfo> distributions = parse_json(jsonFileName);
        output_list(distributions, elementsCount);
    }
}