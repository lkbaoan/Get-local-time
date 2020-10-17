#include <iostream>
#include <ctime>
#include <sstream>
#include <string>

using namespace std;

class Clock {
public:
    virtual int get_hours();
    virtual int get_minutes();
    virtual string get_time();
    virtual int set_alarm(int hours,int minutes);
private:
    int alarm;
};

int Clock::get_hours() {
    time_t current_time = time(0);
    tm* local_time=localtime(&current_time);
    return local_time->tm_hour;
}

int Clock::get_minutes() {
    time_t current_time = time(0);
    tm* local_time=localtime(&current_time);
    return local_time->tm_min;
}

int Clock::set_alarm(int hours,int minutes) {
    stringstream string_time;
    string_time << (hours) << (minutes);
    string_time >> alarm;
    return alarm;
}

string Clock::get_time() {
    int hours = get_hours();
    int minutes = get_minutes();
    int i_alarm = alarm;
    stringstream string_time;
    string_time << (hours) << ":" << (minutes);
    string time;
    string_time >> time;
    if (hours < (i_alarm/100%100)) {
        return time;
    }
    else if (hours == (i_alarm/100%100)) {
        if (minutes < (i_alarm%100)) {
            return time;
        }
        else {
            return time + " Alarm";
        }
    }
    else {
        return time + " Alarm";
    }
}

class WorldClock:public Clock{
public:
    WorldClock(int);
    int get_hours();
    int get_minutes();
private:
    int offset;
};

WorldClock::WorldClock(int offset):Clock(), offset{offset} {}
int WorldClock::get_hours() {
    time_t current_time = time(0);
    tm* local_time=localtime(&current_time);
    int hours= local_time->tm_hour;
    hours += offset;
    if (hours >= 24) {
        hours -= 24;
        return hours;
    }
    else {
        return hours;
    }
}
int WorldClock::get_minutes() {
    time_t current_time = time(0);
    tm* local_time=localtime(&current_time);
    return local_time->tm_min;
}


int main() {
    Clock clock;
    clock.set_alarm(13,30);
    cout << "Current Time(California): " << clock.get_time() << endl;
    WorldClock worldclock(3);
    worldclock.set_alarm(19,30);
    cout << "Current Time(New York): " << worldclock.get_time() << endl;
}