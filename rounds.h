
/*===== Trabalho de Criptografia =====
Algoritmo que utiliza cifra de substituição e permutação para criptografar e descriptografar mensagens.
es23: GRR20232368
sbc23: GRR2023
====================================*/

#ifndef ROUNDS_H
#define ROUNDS_H

#include <iostream>
#include <vector>
#include <iomanip>
#include <functional>
#include <chrono>
#include <cstdint>
#include <array>

#include "logger.h"

using namespace std;
using namespace chrono;

using block_t = array<array<uint8_t, 4>, 4>; 	// Bloco de 16 bits representado como uma matriz 4x4 de bytes
const size_t block_s = 16;						// Tamanho do bloco (em bytes)

class KeyGenerator {
public:
    vector<block_t> generateKeys(const block_t& key, int rounds); 
};

class Round {
public:
    virtual ~Round() = default;

    virtual void encrypt(block_t& block, const block_t& key) = 0;
    virtual void decrypt(block_t& block, const block_t& key) = 0;
};

class SubstitutionRound : public Round {
public:
    void encrypt(block_t& block, const block_t& key) override;
    void decrypt(block_t& block, const block_t& key) override;
};

class PermutationRound : public Round {
public:
    void encrypt(block_t& block, const block_t& key) override;
    void decrypt(block_t& block, const block_t& key) override;
};

class Cipher {
public:
    vector<Round*> rounds;
    vector<block_t> roundKeys;

    void addRound(Round* round, const block_t& key = {});
    void encrypt(block_t& block);
    void decrypt(block_t& block);
};

#endif
