#pragma once

#include <chrono>
#include <unordered_map>
#include <string>

namespace ben {

class StopWatch
{
    typedef std::chrono::system_clock clock;
    typedef clock::duration duration;
public:
    void StartProcess(std::string const & name)
    {
        m_current_processes[name] = clock::now();
    }

    void StopProcess(std::string const & name)
    {
        auto stop = clock::now();
        auto diff = stop - m_current_processes[name];
        m_stopped_processes[name] = diff;
        m_current_processes.erase(name);
    }

    void StopAllProcesses()
    {
        while (!m_current_processes.empty())
        {
            auto ip = m_current_processes.begin();
            StopProcess(ip->first);
        }
    }
private:
    std::unordered_map<std::string, clock::time_point> m_current_processes;
    std::unordered_map<std::string, duration> m_stopped_processes;

    friend std::ostream& operator<<(std::ostream& os, StopWatch const& sw);
};

inline std::ostream& operator<<(std::ostream& os, StopWatch const& sw)
{
    for (auto & p : sw.m_stopped_processes)
    {
        using namespace std::chrono;
        double seconds = nanoseconds(p.second).count() / 1000000000.0;
        os << p.first << " : " << seconds << '\n';
    }
    return os;
}

}