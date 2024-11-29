// #include <TMRpcm.h>
// #include <SD.h>
// #include <SPI.h>
// #include <Wire.h>
// #include <LiquidCrystal_I2C.h>

// const char* mensagem = "se voce fosse uma musica, qual seria?"; // Define a mensagem que será exibida

// int scrollPos = 0; // Posição inicial para rolagem da mensagem
// int mensagemLen = strlen(mensagem); // Comprimento da mensagem

// // Defina o endereço I2C do seu display. Geralmente, é 0x27 ou 0x3F.
// LiquidCrystal_I2C lcd(0x27, 16, 2); // Inicializa o LCD I2C com 16 colunas e 2 linhas




// TMRpcm audio;
// int file_number = 0;
// char filePrefixname[50] = "1";
// char exten[10] = ".wav";
// const int recordLed = 7;
// const int mic_pin = A0;
// const int sample_rate = 16000;

// int botao = 6;
// int estado;
// #define SD_CSPin 10
// // delay function for with serial log.
// void wait_min(int mins) {
//   int count = 0;
//   int secs = mins * 1;
//   while (1) {
//     Serial.print('1');
//     delay(1000);
//     count++;
//     if (count == secs) {
//       count = 0;
//       break;
//     }
//   }
//   Serial.println();
//   return ;
// }


// void setup() {
//   lcd.init(); // Inicializa o LCD (equivalente ao begin())
//   lcd.backlight(); // Liga a luz de fundo do LCD
//   lcd.print("Pergunta: ");
//   // lcd.print("Pergunta: "); // Exibe "Pergunta: " na primeira linha
//   lcd.setCursor(0, 0); // Move o cursor para a primeira coluna da segunda linha
  
//   // put your setup code here, to run once:
//   //initialises the serial connection between the arduino and any connected serial device(e.g. computer, phone, raspberry pi...)
//   Serial.begin(9600);
//   //Sets up the pins
//   pinMode(mic_pin, INPUT);
//   pinMode(recordLed, OUTPUT);
//   Serial.println("loading... SD card");
//   if (!SD.begin(SD_CSPin)) {
//     Serial.println("An Error has occurred while mounting SD");
//   }
//   while (!SD.begin(SD_CSPin)) {
//     Serial.print(".");
//     delay(500);
//   }
//   audio.CSPin = SD_CSPin;
// }
// void loop() {
//   // Atualiza a linha 2 com o efeito de letreiro
//   lcd.setCursor(0, 1);
//   char buffer[17] = ""; // Buffer para armazenar o texto a ser exibido (16 caracteres + nulo)

//   // Preenche o buffer com a parte visível da mensagem
//   for (int i = 0; i < 16; i++) {
//     int index = (scrollPos + i) % mensagemLen; // Calcula o índice circular da mensagem
//     buffer[i] = mensagem[index];
//   }
//   buffer[16] = '\0'; // Adiciona o caractere nulo para finalizar a string

//   lcd.print(buffer); // Exibe o texto na segunda linha

//   // Incrementa a posição de rolagem
//   scrollPos = (scrollPos + 1) % mensagemLen;
//   delay(300); // Controle da velocidade do letreiro
//   estado = false;
//   while (estado == false) {  
//     estado = digitalRead(botao);
//   }
//       lcd.clear();
//     for (int i = 15; i > 0; i--) {
//       lcd.clear();
//       lcd.print("Cronometro: ");
//       lcd.setCursor(12, 0);
//       lcd.print(i);
//       digitalWrite(2, HIGH);
//       delay(500);
//       digitalWrite(2, LOW);
//       delay(500);
//     }
 
//  lcd.clear();
//  lcd.print("Resposta salva!");

      
//       char fileSlNum[20] = "";
//   itoa(file_number, fileSlNum, 10);
//   char file_name[50] = "";
//   strcat(file_name, filePrefixname);
//   strcat(file_name, fileSlNum);
//   strcat(file_name, exten);
//   Serial.print("New File Name: ");
//   Serial.println(file_name);
//   digitalWrite(recordLed, HIGH);
//   audio.startRecording(file_name, sample_rate, mic_pin);
//   Serial.println("startRecording ");
//   // record audio for 2mins. means , in this loop process record 2mins of audio.
//   // if you need more time duration recording audio then
//   // pass higher value into the wait_min(int mins) function.
//   wait_min(15);
    

    
      

  
//   digitalWrite(recordLed, LOW);
//   audio.stopRecording(file_name);
//   Serial.println("stopRecording");
//   file_number++;
//   Serial.println("####################################################################################");
//   // delay(700);
//   // lcd.print("Gravacao salva...");
//   // lcd.clear(); // Limpa a tela do LCD antes de atualizar a mensagem
//   // lcd.setCursor(0, 1); // Posiciona o cursor na segunda linha
//   // lcd.print(mensagem + pos); // Exibe a parte da mensagem a partir da posição atual
//   // lcd.print(som + pos);
  
  
//   // Verifica se a posição atual ainda está dentro dos limites da mensagem


// }







#include <TMRpcm.h>
#include <SD.h>
#include <SPI.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const char* mensagem = "Qual musica da sua vida, e a quem voce a dedicaria? ";
int scrollPos = 0; 
int mensagemLen = strlen(mensagem); // Comprimento da mensagem


LiquidCrystal_I2C lcd(0x27, 16, 2);

TMRpcm audio;
int file_number = 0; 
const int recordLed = 7;
const int mic_pin = A0;
const int sample_rate = 16000;

int botao = 6;
int estado;
#define SD_CSPin 10

void wait_min(int seconds) {
  int count = 0;
  while (count < seconds) {
    delay(1000);
    count++;
  }
}

void setup() {
  lcd.init(); 
  lcd.backlight();
  lcd.print("Pergunta: ");
  lcd.setCursor(0, 0);

  Serial.begin(9600);
  pinMode(mic_pin, INPUT);
  pinMode(recordLed, OUTPUT);
  pinMode(botao, INPUT);
  Serial.println("Carregando... SD card");
  if (!SD.begin(SD_CSPin)) {
    Serial.println("Erro ao inicializar o SD");
    while (1);
  }
  audio.CSPin = SD_CSPin;
}

void loop() {

  lcd.setCursor(0, 1);
  char buffer[17] = ""; 


  for (int i = 0; i < 16; i++) {
    int index = (scrollPos + i) % mensagemLen; // Calcula o índice circular da mensagem
    buffer[i] = mensagem[index];
  }
  buffer[16] = '\0'; // Adiciona o caractere nulo para finalizar a string

  lcd.print(buffer); // Exibe o texto na segunda linha


  scrollPos = (scrollPos + 1) % mensagemLen;
  delay(600); 


  estado = digitalRead(botao);
  if (estado == HIGH) {
    lcd.clear();
    for (int i = 10; i > 0; i--) {
      lcd.clear();
      lcd.print("Cronometro: ");
      lcd.setCursor(12, 0);
      lcd.print(i);
      digitalWrite(2, HIGH);
      delay(500);
      digitalWrite(2, LOW);
      delay(500);
    }

    lcd.clear();
    lcd.print("Gravando...");
    // for (int i =15; i>0; i--){
    //   lcd.clear();
    //   lcd.print("Cronometro: ");
    //   lcd.setCursor(12, 0);
    //   lcd.print(i);
    //   digitalWrite(2, HIGH);
    //   delay(500);
    //   digitalWrite(2, LOW);
    //   delay(500);
    // }

    // Gera o nome do arquivo automaticamente
    char file_name[20];
    do {
      sprintf(file_name, "%03d.wav", file_number); 
      file_number++; 
    } while (SD.exists(file_name)); 

   
    digitalWrite(recordLed, HIGH);
    audio.startRecording(file_name, sample_rate, mic_pin);
    Serial.print("Gravando no arquivo: ");
    Serial.println(file_name);

    wait_min(15); 
    digitalWrite(recordLed, LOW);
    audio.stopRecording(file_name);

    Serial.println("Gravação encerrada.");
    lcd.clear();
    lcd.print("Resposta salva!");
    delay(2000);

    // Reinicia o loop
    lcd.clear();
    lcd.print("Pergunta: "); // Exibe novamente a pergunta
    scrollPos = 0; // Reinicia a posição do letreiro
  }
}
