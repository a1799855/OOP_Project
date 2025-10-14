#ifndef DEBUG_H
#define DEBUG_H
#include <string>
#include <fstream>
// Mutual exclusion lock. Mainly for stopping duplicate entries
#include <mutex>

using namespace std;

//Enum values with varying levels of severity
enum class LogLevel {
    Trace,
    Info,
    Warn,
    Error
};

class Debug {
public:
    //Creates a log file, and prints both to the log file and the terminal
    static void init(const string& filename = "debug.log", bool alsoStdout = true);

    //Cleanup function - closes log file.
    static void shutdown();
    
    // An idea on how to log what the players see. All player facing outputs would have to route through here with "s" being what the user sees
    static void print(const string& s);

    // Log to log file with specified severity
    static void log(LogLevel lvl, const string& msg);
    
    // Same as above but shortened versions for ease of use
    static void trace(const string& msg) { log(LogLevel::Trace, msg); }
    static void info(const string& msg) { log(LogLevel::Info, msg); }
    static void warn(const string& msg) { log(LogLevel::Warn, msg); }
    static void error(const string& msg) { log(LogLevel::Error, msg); }
    
    // Enables/disables debug logging.
    static void setEnabled(bool on) { enabled() = on; }

    // Checks is debugging is enabled
    static bool isEnabled() { return enabled(); }

private:
    // Calling the same single log file
    static ofstream& stream();

    // To prevent two threads from writing into the file at the same time
    static mutex& mtx();

    // Static bool references
    static bool& alsoConsole();
    static bool& initialized();
    static bool& enabled();

    // Turns LogLevel severity enum into a string 
    static string levelToStr(LogLevel lvl);
};

#endif