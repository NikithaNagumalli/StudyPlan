#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

void createStudyPlan(int weeks, map<string, double> chapterToTime) {
    double totalTime = 0;
    map<string, double>::iterator it = chapterToTime.begin();
    while (it != chapterToTime.end()) {
        totalTime += it->second; 
        ++it;
    }

    it = chapterToTime.begin();
    double timePerWeek = totalTime / weeks;
    double timeLeft = timePerWeek;
    for (int i = 0; i < weeks; i++) {
        cout << "WEEK " << i + 1 << ": " << endl;
        while (timeLeft > 0) {
            if (timeLeft - it->second >= 0) {
                cout << it->second << " hours of "<< it->first << endl;
                timeLeft -= it->second;
                ++it;
            } else {
                cout << timeLeft << " hours of " << it->first << endl;
                it->second = it->second - timeLeft;
                timeLeft = 0;
            }
        }
        timeLeft = timePerWeek;
    }
}

int main() {
    ifstream ifs("C:\\Users\\nikit\\PersonalProjects\\StudyPlan\\courses\\course.json");
    json data = json::parse(ifs);
    int weeks = data["weeks"];
    map<string, double> chapterToTime;
    for (json info : data["chapters"]) {
        chapterToTime[info["name"]] = info["time"];
    }

    createStudyPlan(weeks, chapterToTime);
    return 0;
}