
#include <iostream>
#include <fstream>
#include <mutex>
#include <thread>
#include <string>

using namespace std;

class Logger {
private:
    static std::unique_ptr<Logger> instance;
    static std::mutex init_mtx;
    static std::mutex write_mtx;
    std::ofstream logFile;
    Logger(const std::string& filename) {
        logFile.open(filename, std::ios::trunc);
        logFile << "[Init] Logger started." << endl;
    }


public:
    ~Logger() {
        logFile << "[Shutdown] Logger closed." << endl;
    }
    static Logger* getInstance(const std::string& filename = "Test/output2.txt") {
        lock_guard<mutex> lock(init_mtx);
        if (!instance)
            instance.reset(new Logger(filename));
        return instance.get();
    }

    void log(const std::string& message) {
        /* TODO */
        lock_guard<mutex> lock(write_mtx);
        logFile << message << endl;
    }

};

std::unique_ptr<Logger> Logger::instance;
std::mutex Logger::init_mtx;
std::mutex Logger::write_mtx;

