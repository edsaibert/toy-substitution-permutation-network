
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
				next_key[r][c] = shiftedByte ^ currKey[r][c] ^ i;
			}
		}

		keys.push_back(nextKey);
		currKey = nextKey;
	}

	return keys;
}

void SubstitutionRound::encrypt(block_t& block, const block_t& key) {
	// Implementação da cifra de substituição

	// Exemplo bobo
	for (int r = 0; r < 4; ++r) {
            for (int c = 0; c < 4; ++c) {
                block[r][c] ^= 0x55;
            }
        }
    }
}

void SubstitutionRound::decrypt(block_t& block, const block_t& key) {
	// Implementação da cifra de substituição

	// Exemplo bobo
	for (int r = 0; r < 4; ++r) {
            for (int c = 0; c < 4; ++c) {
                block[r][c] ^= 0x55;
            }
        }
    }
}

void PermutationRound::encrypt(block_t& block, const block_t& key) {
	// Implementação da cifra de permutação

	// Exemplo bobo
	for (int r = 0; r < 4; ++r) {
		for (int c = r + 1; c < 4; ++c) {
			std::swap(block[r][c], block[c][r]);
		}
	}
}
}

void PermutationRound::decrypt(block_t& block, const block_t& key) {
	// Implementação da cifra de permutação

	// Exemplo bobo 
	for (int r = 0; r < 4; ++r) {
            for (int c = r + 1; c < 4; ++c) {
                std::swap(block[r][c], block[c][r]);
            }
        }
    }
}

void Cipher::encrypt(block_t& block) {
	LoggerRAII log("Cipher Encrypt");

	for (size_t i = 0; i < rounds.size(); ++i) {
		rounds[i].encrypt(block, roundKeys[i]);	
	}
}

void Cipher::decrypt(block_t& block) {
	LoggerRAII log("Cipher Decrypt");
	for (size_t i = rounds.size(); i-- > 0;) {
		rounds[i].decrypt(block, roundKeys[i]);
	}
}
