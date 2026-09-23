
/*===== Trabalho de Criptografia =====
Algoritmo que utiliza cifra de substituição e permutação para criptografar e descriptografar mensagens.
es23: GRR20232368
sbc23: GRR2023
====================================*/

#include "rounds.h"

vector<block_t> KeyGenerator::generateKeys(const block_t& key, int rounds) {
	// Se a semente for diferente de -1, utilizar a semente para gerar chaves pseudo-aleatórias
	// Caso contrário, gerar nova semente   

	// TO-DO
}

void SubstitutionRound::encrypt(block_t& block, const block_t& key) {
	// Implementação da cifra de substituição
}

void SubstitutionRound::decrypt(block_t& block, const block_t& key) {
	// Implementação da cifra de substituição
}

void PermutationRound::encrypt(block_t& block, const block_t& key) {
	// Implementação da cifra de permutação
}

void PermutationRound::decrypt(block_t& block, const block_t& key) {
	// Implementação da cifra de permutação
}

void Cipher::encrypt(block_t& block) {
	LoggerRAII log("Cipher Encrypt");

	for (size_t i = 0; i < rounds.size(); ++i) {
		// TO-DO
	}
}

void Cipher::decrypt(block_t& block) {
	LoggerRAII log("Cipher Decrypt");
	for (size_t i = rounds.size(); i-- > 0;) {
		// TO-DO
	}
}
