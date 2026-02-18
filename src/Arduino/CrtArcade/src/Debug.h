#ifndef DEBUG_H
#define DEBUG_H

//#define DEBUG

#ifdef DEBUG
    #define debug_print(...) Serial.print(__VA_ARGS__)
    #define debug_println(...) Serial.println(__VA_ARGS__)
#else
    #define debug_print(...)
    #define debug_println(...)
#endif

class Debug {
public:
    static void initialize();
};

#endif
