#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;


int botao = 7;
int estado = false;


int totalFiles = 0; 
int currentFile = 0;

void setup() {
  pinMode(botao, INPUT_PULLUP); 
  mySoftwareSerial.begin(9600);
  Serial.begin(115200);


  Serial.println(F("\nDFRobot DFPlayer Mini"));
  Serial.println(F("Inicializando modulo DFPlayer... (3~5 segundos)"));
  if (!myDFPlayer.begin(mySoftwareSerial)) {
    Serial.println(F("Erro ao inicializar:"));
    Serial.println(F("1. Verifique conexões do DFPlayer Mini"));
    Serial.println(F("2. Insira um cartão SD"));
    while (true);
  }
  Serial.println(F("Modulo DFPlayer Mini inicializado!"));


  myDFPlayer.setTimeOut(500);
  myDFPlayer.volume(20);     
  myDFPlayer.EQ(0);           


  totalFiles = myDFPlayer.readFileCounts(DFPLAYER_DEVICE_SD); 
  if (totalFiles > 1) {
    currentFile = totalFiles - 1; // Define o penúltimo arquivo como o inicial
  } else {
    currentFile = 1; // Se houver apenas um arquivo, começa com ele
  }
  Serial.print(F("Total de arquivos: "));
  Serial.println(totalFiles);
}

void loop() {
  estado = false;

  
  while (estado == false) {
    estado = digitalRead(botao); 

    
    if (estado == false) { 
      playPenultimateFile();  // Toca o penúltimo arquivo
      delay(17000);  // Aguarda 17 segundos para o áudio terminar
    }
  }
}

// Função para reproduzir o penúltimo arquivo
void playPenultimateFile() {
  Serial.print(F("Reproduzindo penúltimo arquivo: "));
  Serial.println(currentFile);
  myDFPlayer.play(currentFile);
}
