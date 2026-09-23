
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

#include "logger.h"
#include "rounds.h"

using namespace std;
using namespace chrono;

int main() {
    logger = new Logger();
    LoggerRAII log_main("Main Function");

    // TO-DO

	logger->printLogs();
	delete logger;

	logger = nullptr;
    return 0;
}
