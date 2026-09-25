
/*===== Trabalho de Criptografia =====
Algoritmo que utiliza cifra de substituição e permutação para criptografar e descriptografar mensagens.
es23: GRR20232368
sbc23: GRR2023
====================================*/

#include "rounds.h"

vector<block_t> KeyGenerator::generateKeys(const block_t& key, int rounds) {
	vector<block_t> keys;

	block_t currKey = key;
	keys.push_back(currKey);

	for (int i = 0; i < rounds; i++){
		block_t nextKey{};

		for (int r = 0; r < 4; r++){
			for (int c = 0; c < 4; c++){
				uint8_t shiftedByte = currKey[r][(c + 1) % 4];
				nextKey[r][c] = shiftedByte ^ currKey[r][c] ^ i;
			}
		}

		keys.push_back(nextKey);
		currKey = nextKey;
	}

	return keys;
}

// Debugging
void printMatrix(block_t& block){
	cout << "\n";

	for (int r = 0; r < 4; ++r) {
		for (int c = 0; c < 4; ++c) {
			cout << "0x" 
				<< hex << setw(2) << setfill('0') 
				<< static_cast<int>(block[r][c]) << " ";
		}
		cout << "\n";
	}
	cout << dec; 
}

void SubstitutionRound::encrypt(block_t& block, const block_t& key) {
	// Implementação da cifra de substituição

	// Exemplo bobo
	for (int r = 0; r < 4; ++r) {
		for (int c = 0; c < 4; ++c) {
			block[r][c] ^= key[r][c];
		}
	}
}

void SubstitutionRound::decrypt(block_t& block, const block_t& key) {
	// Implementação da cifra de substituição

	// Exemplo bobo
	for (int r = 0; r < 4; ++r) {
		for (int c = 0; c < 4; ++c) {
			block[r][c] ^= key[r][c];
		}
	}
}

void PermutationRound::encrypt(block_t& block, const block_t& key) {
	// Algoritmo de permutação similar ao ShiftRows do AES, porém para a esquerda
	for (int r = 1; r < 4; ++r) {
		array<uint8_t, 4> temp = block[r];
		for (int c = 0; c < 4; ++c) {
			block[r][c] = temp[(c+r)%4];
		}
	}
}

void PermutationRound::decrypt(block_t& block, const block_t& key) {
	// Implementação da cifra de permutação

	// Exemplo bobo
	for (int r = 1; r < 4; ++r) {
		array<uint8_t, 4> temp = block[r];
		for (int c = 0; c < 4; ++c) {
			block[r][c] = temp[((c+4)-(r%4))%4];
		}
	}
}

void Cipher::addRound(Round* round, const block_t& key){
	rounds.push_back(round);
	roundKeys.push_back(key);
}

void Cipher::encrypt(block_t& block) {
	LoggerRAII log("Cipher Encrypt");

	for (size_t i = 0; i < rounds.size(); ++i) {
		rounds[i]->encrypt(block, roundKeys[i]);	
	}
}

void Cipher::decrypt(block_t& block) {
	LoggerRAII log("Cipher Decrypt");
	for (size_t i = rounds.size(); i-- > 0;) {
		rounds[i]->decrypt(block, roundKeys[i]);
	}
}
