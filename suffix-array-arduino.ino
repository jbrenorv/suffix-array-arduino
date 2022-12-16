/*
* [T2] Microcontrolador - Desenvolvimento de SW embarcado (PARTE 2)
* Sistemas embarcados 2022.2 - Engenharia da Computacao IFCE
* Equipe Joao Breno Rodrigues Venancio e Maria Eduarda Caetano da Silva
*
* Etapas concluidas:
*  - Migrar codigo feito no linux para o Arduino UNO
*  - Otimizar utilizacao de memoria
*/

#include <avr/pgmspace.h>
#include "BasicSuffixArray.h"

// Stored on progmen
const char inputText[] PROGMEM = {"ababba$"};

unsigned int inputTextLength;
char charToReadInput;

void setup() {
  Serial.begin(9600);

  while (Serial.available()) ;

  // Read Flash Memory
  inputTextLength = strlen_P(inputText);
  pair<char, int> a[inputTextLength];
  for (byte i = 0; i < inputTextLength; i++) {
    charToReadInput = pgm_read_byte_near(inputText + i);
    Serial.print(charToReadInput);
    a[i] = {charToReadInput, i};
  }
  Serial.println();

  // para guardar o suffix array resultante
  int p[inputTextLength];

  // encontra o suffix array. ao final na execucao, o array p guardara os sufixos em ordem
  buildSuffixArray(p, a, inputTextLength);

  // imprime o suffix array no monitor serial
  printArray(p, inputTextLength);
}

void loop() {
  // put your main code here, to run repeatedly:

}

void printArray(int* array, int n) {
  Serial.print(array[0]);
  for (int i = 1; i < n; ++i) {
    Serial.print(' ');
    Serial.print(array[i]);
  }
  Serial.println();
}
