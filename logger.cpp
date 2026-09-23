
/*===== Trabalho de Criptografia =====
Algoritmo que utiliza cifra de substituição e permutação para criptografar e descriptografar mensagens.
es23: GRR20232368
sbc23: GRR2023
====================================*/

#include "logger.h"

void Logger::addLog(struct LogRound log) {
	logs.push_back(log);
}

double Logger::getTotalDuration() {
	double totalDuration = 0.0;
	for (const auto& log : logs) {
		totalDuration += log.duration;
	}
	return totalDuration;
}

void Logger::printLogs() {
	for (const auto& log : logs) {
		cout << "Round Type: " << log.roundType << ", Duration: " << fixed << setprecision(6) << log.duration << " seconds" << endl;
	}

	cout << "Total Duration: " << fixed << setprecision(6) << getTotalDuration() << " seconds" << endl;
}

LoggerRAII::LoggerRAII(const string& roundType)
: roundType(roundType), start(high_resolution_clock::now()) {}

LoggerRAII::~LoggerRAII() {
	auto end = high_resolution_clock::now();
	duration<double> duration = end - start;

	if (logger)
		logger->addLog({roundType, duration.count()});
}
