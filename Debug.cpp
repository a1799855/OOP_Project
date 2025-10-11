#include "Debug.h"
#include <iostream>

// Time functions
#include <ctime>
//Input/output manipulations. Used for timestamps
#include <iomanip>
//String streams. Found online, used for timestamps
#include <sstream>

using namespace std;

// Writing log messages
static ofstream g_log;
// To prevent two threads from writing into the file at the same time
static mutex g_mtx;
// If debug logger is running or not
static bool g_initialized = false;
// If writing to console as well as file
static bool g_alsoConsole = true;
// Switch for enable or disabling logging
static bool g_enabled = true;

// Returns references for static functions from header. Global inside this cpp file but not outside
ofstream& Debug::stream() { return g_log; }
mutex& Debug::mtx() { return g_mtx; }
bool& Debug::initialized() { return g_initialized; }
bool& Debug::alsoConsole() { return g_alsoConsole; }
bool& Debug::enabled() { return g_enabled; }

// Prepares logger. Locks down logging when ran, unlocks afterwards. Opens log file. Wipes old log file. If log file doesn't exist, create one 
void Debug::init(const string& filename, bool alsoStdout) {
    lock_guard<mutex> lk(mtx());
    if (initialized()) return;
    stream().open(filename, ios::out | ios::trunc);
    alsoConsole() = alsoStdout;
    initialized() = true;
}

// Cleanup function for the logger. Shuts it down and closes log file.
void Debug::shutdown() {
    lock_guard<mutex> lk(mtx());
    if (!initialized()) return;
    stream().flush();
    stream().close();
    initialized() = false;
}

// Pulls current time from OS, and outputs something like "2025-12-25 12:13:45"
static string timestamp() {
    time_t t = time(nullptr);
    tm tm{};
#if defined(_WIN32)
    // Windows time. Hopefully works
    localtime_s(&tm, &t);
#else
    // Non-windows time
    localtime_r(&t, &tm);
#endif
    // For building a string
    ostringstream oss;
    // Assembles the timestamp
    oss << put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

// Turns LogLevel severity enum into a string. Defined for each severity enum with "?" as a fallback
string Debug::levelToStr(LogLevel lvl) {
    switch (lvl) {
        case LogLevel::Trace: return "TRACE";
        case LogLevel::Info:  return "INFO";
        case LogLevel::Warn:  return "WARN";
        case LogLevel::Error: return "ERROR";
    }
    return "?";
}

// Logging player facing outputs
// void Debug::print(const string& s) {
//     cout << s;
// }

//Brings it all together. Main logging function
void Debug::log(LogLevel lvl, const string& msg) {
    if (!isEnabled()) return;
    lock_guard<mutex> lk(mtx());
    auto line = "[" + timestamp() + "][" + levelToStr(lvl) + "] " + msg + "\n";
    if (stream().is_open())
        stream() << line;
    if (alsoConsole())
        cerr << line;
}
