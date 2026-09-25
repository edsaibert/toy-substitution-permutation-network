
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


block_t masterKey = {{
    {0x2B, 0x7E, 0x15, 0x16},
    {0x28, 0xAE, 0xD2, 0xA6},
    {0xAB, 0xF7, 0x15, 0x88},
    {0x09, 0xCF, 0x4F, 0x3C}
}};

int main(int argc, char* argv[]) {
	// =================================
	// Tratamento do argc --------------
	// =================================
	if (argc < 4){
		cerr << "Usage: " << argv[0] << "-enc/-dec <input_file> <output_file>\n";
		return 1;
	}

	bool enc;
	if (strcmp(argv[1], "-enc") == 0) enc = true;
	else if (strcmp(argv[1], "-dec") == 0) enc = false;
	else {
		cerr << "\nErro: flag incorreta\n";
		exit(1);
	}

	string inputPath = argv[2];
	string outputPath = argv[3];	

	// =================================
	// Criação arquivos in/out ---------
	// =================================
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

	// =================================
	// Instanciamento classes ----------
	// =================================
	logger = new Logger();
    LoggerRAII log_main("Main Function");

	int numRounds = 4;
	KeyGenerator keyGen;
	vector<block_t> generatedKeys = keyGen.generateKeys(masterKey, numRounds);

	Cipher cipher;
	SubstitutionRound subRound;
	PermutationRound permRound;

	// Critério arbitrário para criação da cifra
	for (int i = 0; i < numRounds; ++i) {
		if (i % 2 == 0) {
			cipher.addRound(&subRound, generatedKeys[i]);
		} else {
			cipher.addRound(&permRound);
		}
	}

	// =================================
	// Leitura/escrita dos blocos ------
	// =================================
	block_t block{};
	size_t bytesRead;
	uint8_t* block_ptr = reinterpret_cast<uint8_t*> (block.data());

	while ((bytesRead = fread(block_ptr, 1, block_s, inFile)) > 0) {
		// Se o bloco lido for menor que o tamanho do bloco, realiza padding para preencher a matriz
		if (bytesRead < block_s) {
			memset(block_ptr + bytesRead, 0, block_s - bytesRead);			
		}

		if (enc) cipher.encrypt(block);
		else cipher.decrypt(block);

		size_t bytesWritten = fwrite(block_ptr, 1, block_s, outFile);
		if (bytesWritten < block_s){
			cerr << "Erro enquanto escrevia no arquivo de saída.";
			break;
		}
		
	}

	// =================================
	// Operações finais ----------------
	// =================================
	fclose(inFile);
	fclose(outFile);

	//logger->printLogs();
	delete logger;

	logger = nullptr;
    return 0;
}
