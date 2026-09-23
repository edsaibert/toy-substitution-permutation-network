
/*===== Trabalho de Criptografia =====
Algoritmo que utiliza cifra de substituição e permutação para criptografar e descriptografar mensagens.
es23: GRR20232368
sbc23: GRR2023
====================================*/

#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <vector>
#include <iomanip>
#include <functional>
#include <chrono>
#include <cstdint>
#include <array>

using namespace std;
using namespace chrono;

struct LogRound {
    string roundType;
    double duration;
};

class Logger {
public:
    vector<LogRound> logs;

    void addLog(struct LogRound log);
    double getTotalDuration();
    void printLogs();
};

inline Logger* logger = nullptr;

class LoggerRAII {
public:
    string roundType;
    high_resolution_clock::time_point start;

    LoggerRAII(const string& roundType);
    ~LoggerRAII();
};

#endif


