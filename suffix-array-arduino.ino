/*
* [T3] Microcontrolador - Desenvolvimento de SW embarcado (PARTE 2)
* Sistemas embarcados 2022.2 - Engenharia da Computacao IFCE
* Equipe Joao Breno Rodrigues Venancio e Maria Eduarda Caetano da Silva
*
* Etapas concluidas:
*  - Migrar codigo feito no linux para o Arduino UNO
*  - Otimizar utilizacao de memoria
*/

#include <avr/pgmspace.h>
#include "BasicSuffixArray.h"
#define MAXN 255

/// Stored in flash memory using progmen
const char inputText[] PROGMEM = {
  "ababbaababbaababbaba"
  "bbaababbaababbababba"
  "ababbaababbababbaaba"
  "bbaababbababbaababba"
  "ababbababbaababbaaba"
  "bbababbaababbaababba"
  "babbaababbaababbabab"
  "baababbaababbababbaa"
  "babbaababbababbaabab"
  "baababbababbaababbaa"
  "babbababbaababbaabab"
  "bababbaababbaababbab"
  "abbaababbaabab$"
};

uint8_t suffixArray[MAXN];
uint8_t inputTextLength;

void setup() {
  Serial.begin(9600);

  while (Serial.available()) ;

  inputTextLength = strlen_P(inputText);

  /** Encontra o suffix array. ao final na execucao,
    * o array suffixArray guardara os sufixos em ordem */
  buildSuffixArray(suffixArray, inputText, inputTextLength);

  /** Imprime o suffix array no monitor serial */
  printSuffixArray();
}

void loop() { }

void printSuffixArray() {
  Serial.println(F("Suffix array:"));
  Serial.print(suffixArray[0]);
  for (uint8_t i = 1; i < inputTextLength; i++) {
    Serial.print(' ');
    Serial.print(suffixArray[i]);
  }
  Serial.println();
}
