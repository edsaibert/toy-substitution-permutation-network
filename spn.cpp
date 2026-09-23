
/*===== Trabalho de Criptografia =====
Algoritmo que utiliza cifra de substituição e permutação para criptografar e descriptografar mensagens.
es23: GRR20232368
sbc23: GRR2023
====================================*/

#include <iostream>
#include <vector>
#include <iomanip>
#include <functional>
#include <chrono>
#include <cstdint>
#include <array>

using namespace std;
using namespace chrono;
Logger* logger = nullptr;

using block_t = array<array<uint8_t, 4>, 4>; // Bloco de 16 bits representado como uma matriz 4x4 de bytes

class Round {
public:
    virtual ~Round() = default;

    virtual void encrypt(block_t& block, const block_t& key) = 0;
    virtual void decrypt(block_t& block, const block_t& key) = 0;
};

class SubstitutionRound : public Round {
public:
    void encrypt(block_t& block, const block_t& key) override {
        // Implementação da cifra de substituição
    }

    void decrypt(block_t& block, const block_t& key) override {
        // Implementação da cifra de substituição
    }
};

class PermutationRound : public Round {
public:
    void encrypt(block_t& block, const block_t& key) override {
        // Implementação da cifra de permutação
    }

    void decrypt(block_t& block, const block_t& key) override {
        // Implementação da cifra de permutação
    }
};

class Cipher {
public:
    vector<Round*> rounds;
    vector<block_t> roundKeys;

    void addRound(Round* round, const block_t& key) {
        rounds.push_back(round);
        roundKeys.push_back(key);
    }

    void encrypt(block_t& block) {
        LoggerRAII log("Cipher Encrypt");

        for (size_t i = 0; i < rounds.size(); ++i) {
            // TO-DO
        }
    }

    void decrypt(block_t& block) {
        LoggerRAII log("Cipher Decrypt");
        for (size_t i = rounds.size(); i-- > 0;) {
            // TO-DO
        }
    }

};

class KeyGenerator {
public:
    vector<block_t> generateKeys(const block_t& key, int rounds) {
        // Se a semente for diferente de -1, utilizar a semente para gerar chaves pseudo-aleatórias
        // Caso contrário, gerar nova semente   

        // TO-DO
    }
};

struct LogRound {
    string roundType;
    double duration;
};

class Logger {
public:
    vector<LogRound> logs;

    void addLog(struct LogRound log) {
        logs.push_back(log);
    }

    double getTotalDuration() {
        double totalDuration = 0.0;
        for (const auto& log : logs) {
            totalDuration += log.duration;
        }
        return totalDuration;
    }

    void printLogs() {
        for (const auto& log : logs) {
            cout << "Round Type: " << log.roundType << ", Duration: " << fixed << setprecision(6) << log.duration << " seconds" << endl;
        }

        cout << "Total Duration: " << fixed << setprecision(6) << getTotalDuration() << " seconds" << endl;
    }
};

class LoggerRAII {
public:
    string roundType;
    high_resolution_clock::time_point start;

    LoggerRAII(const string& roundType)
        : roundType(roundType), start(high_resolution_clock::now()) {}

    ~LoggerRAII() {
        auto end = high_resolution_clock::now();
        duration<double> duration = end - start;

		if (logger)
			logger->addLog({roundType, duration.count()});
    }
};


int main() {
    logger = new Logger();
    LoggerRAII log_main("Main Function");

    // TO-DO

    return 0;
}
