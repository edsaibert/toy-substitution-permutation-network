
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
#include <cstring>

#include "logger.h"
#include "rounds.h"

using namespace std;
using namespace chrono;

int main(int argc, char* argv[]) {
	if (argc < 2){
		cerr << "Necessário caminho para o texto. Usage: " << argv[0] << " <input_file>\n";
		return 1;
	}

	string inputPath = argv[1];
	string outputPath = inputPath + ".enc";	

	cout << "output path: " << outputPath << "\n";

	FILE* inFile = fopen(inputPath.c_str(), "rb");
	if (!inFile) {
		perror("Failed to open input file");
		return 1;
	}

	FILE* outFile = fopen(outputPath.c_str(), "wb");
	if (!outFile) {
		perror("Failed to open output file");
		fclose(inFile);
		return 1;
	}

	logger = new Logger();
    LoggerRAII log_main("Main Function");

	int numRounds = 4;
	KeyGenerator keyGen;
	vector<block_t> generatedKeys = keyGen.generateKeys(masterKey, numRounds);

	Cipher cipher;
	SubstitutionRound subRound;
	PermutationRound permRound;

	for (int i = 0; i < numRounds; ++i) {
		if (i % 2 == 0) {
			cipher.addRound(&subRound, generatedKeys[i]);
		} else {
			cipher.addRound(&permRound, generatedKeys[i]);
		}
	}

	block_t block{};
	size_t bytesRead;
	uint8_t* block_ptr = reinterpret_cast<uint8_t*> (block.data());

	while ((bytesRead = fread(block_ptr, 1, block_s, inFile)) > 0) {
		// Se o bloco lido for menor que o tamanho do bloco, realiza padding para preencher a matriz
		if (bytesRead < block_s) {
			memset(block_ptr + bytesRead, 0, block_s - bytesRead);			
		}

		cout << "\n[" << bytesRead << "] bytes read";

		cipher.encrypt(block);

		size_t bytesWritten = fwrite(block_ptr, 1, block_s, outFile);
		if (bytesWritten < block_s){
			cerr << "Erro enquanto escrevia no arquivo de saída.";
			break;
		}
		
	}

	fclose(inFile);
	fclose(outFile);

	logger->printLogs();
	delete logger;

	logger = nullptr;
    return 0;
}
