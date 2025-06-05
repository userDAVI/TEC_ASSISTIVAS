// Inclusão das Bibliotecas
#include<Wire.h> //biblioteca para comunicação i2c
#define buzzer 9

// Endereco I2C do sensor MPU-6050
const int MPU = 0x68;
int i=0;

// Variaveis para armazenar valores do sensor - esses valores são palavras binárias de 16bits
float AccX, AccY, AccZ, Temp, GyrX, GyrY, GyrZ;


void setup() {
  configuracao();  
}

void loop() {

  requisicao();
  
  Serial.println(AccX);
  Serial.print(" ");
  Serial.print(AccY);
  Serial.print(" ");
  Serial.println(AccZ);


  delay(100);
  

}





void configuracao(){
  pinMode(buzzer, OUTPUT);
  
  // Inicialização da porta Serial e sua taxa de trasmissão de dados
  Serial.begin(9600);

  // Inicialização a comunicação i2c com o MPU-6050
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0); 
  Wire.endTransmission(true);

  // seleção do fundo do escala do giroscópio.
  /*
    Wire.write(0b00000000); // fundo de escala em +/-250°/s
    Wire.write(0b00001000); // fundo de escala em +/-500°/s
    Wire.write(0b00010000); // fundo de escala em +/-1000°/s
    Wire.write(0b00011000); // fundo de escala em +/-2000°/s
  */
  Wire.beginTransmission(MPU);
  Wire.write(0x1B);         //posição de momeória responsável pelo fundo de escala do giroscópio
  Wire.write(0x00011000);   // escrita no endereço de memória
  Wire.endTransmission();
  
//   seleção do fundo do escala do acelerômetro.
  /*
      Wire.write(0b00000000); // fundo de escala em +/-2g
      Wire.write(0b00001000); // fundo de escala em +/-4g
      Wire.write(0b00010000); // fundo de escala em +/-8g
      Wire.write(0b00011000); // fundo de escala em +/-16g
  */
  Wire.beginTransmission(MPU);
  Wire.write(0x1C);           //posição de memória responsával pelo ajuste de fundo de escala do acelerômetro
  Wire.write(0b00011000);     // Trocar esse comando para fundo de escala desejado conforme acima
  Wire.endTransmission();
}




void requisicao(){
    // Comandos para iniciar transmissão de dados
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);     //posição de memória inicial
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 14, true); // requisição de 14 palavras de 16 bits. Começando do endereço de memoria indicado acima (0x3B)

  // Armazena o valor das palavras nas variaveis correspondentes
  AccX = Wire.read() << 8 | Wire.read(); //0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)     // lê os primeiros 8bits da parte alta, desloca e lê os outros 8 bits da parte baixa
  AccY = Wire.read() << 8 | Wire.read(); //0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)     // faz o mesmo para os outros sensores.
  AccZ = Wire.read() << 8 | Wire.read(); //0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Temp = Wire.read() << 8 | Wire.read(); //0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyrX = Wire.read() << 8 | Wire.read(); //0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyrY = Wire.read() << 8 | Wire.read(); //0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyrZ = Wire.read() << 8 | Wire.read(); //0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
}
