#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SD.h>
#include <SPI.h>

// Pino do chip select (CS) para o cartão SD
const int chipSelect = 53; // Usando o pino CS para Mega 2560

// Inicializa o LCD I2C com 16 colunas e 2 linhas (Endereço 0x27 para o LCD)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Variáveis para ler o arquivo do cartão SD
File grupo13;
char mensagem[128]; // Para armazenar a mensagem lida do SD
int pos = 0; // Inicializa a posição da mensagem

void setup() {
  // Inicializa a comunicação serial
  Serial.begin(9600);

  // Inicializa o LCD
  lcd.init();
  lcd.backlight(); // Liga a luz de fundo do LCD
  lcd.print("Carregando SD...");

  // Inicializa o cartão SD
  if (!SD.begin(chipSelect)) {
    lcd.clear();
    lcd.print("Falha SD!");
    Serial.println("Falha na inicialização do cartão SD");
    return;
  }

  lcd.clear();
  lcd.print("Cartao SD OK!");

  // Abre o arquivo "mensagem.txt" do cartão SD para leitura
  grupo13 = SD.open("mensagem.txt");
  if (grupo13) {
    int i = 0;
    // Lê o conteúdo do arquivo e armazena na variável mensagem[]
    while (grupo13.available() && i < sizeof(mensagem) - 1) {
      mensagem[i] = grupo13.read();  // Lê um byte do arquivo
      i++;
    }
    mensagem[i] = '\0';  // Finaliza a string com '\0'
    grupo13.close();  // Fecha o arquivo após ler
  } else {
    lcd.clear();
    lcd.print("Erro ao abrir");
    Serial.println("Erro ao abrir o arquivo.");
    return;
  }

  lcd.clear();
  lcd.print("Mensagem carregada!");
  delay(1000);  // Atraso para exibir a mensagem "Mensagem carregada!" por um tempo
}

void loop() {
  lcd.clear(); // Limpa a tela do LCD antes de atualizar a mensagem
  lcd.setCursor(0, 1); // Posiciona o cursor na segunda linha
  lcd.print(mensagem + pos); // Exibe a parte da mensagem a partir da posição atual

  // Verifica se a posição atual ainda está dentro dos limites da mensagem
  if (pos < strlen(mensagem)) {
    pos++; // Incrementa a posição para mostrar o próximo caractere
  } else {
    pos = 0; // Reinicia a posição se a mensagem chegou ao final
  }

  delay(700); // Aguarda 700 milissegundos para a próxima atualização da mensagem
}
