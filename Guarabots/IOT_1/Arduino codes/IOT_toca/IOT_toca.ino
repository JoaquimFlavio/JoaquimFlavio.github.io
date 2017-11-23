//############################################################
//#Controle IOT da Toca do Guarabots_________________________#
//#Versão: BETA______________________________________________#
//#Data: outubro/2017________________________________________#
//#Autores: Joaquim Flavio Almeida Quirino Gomes_____________#
//#suporte: {joaquimflavio.quirino@gmail.com}________________#
//#-----------{https://guarabots.wordpress.com/}-------------#
//############################################################

//Incluimos as bibliotecas necessarias._______________________
#include <GuaraTeca_Hardware.h>
#include <LiquidCrystal_I2C.h>
#include <Ethernet.h>
#include <Wire.h>
#include <SPI.h>

//Definimos os pinos dos componentes para controle IOT._______
#define pino_rele1              2 
#define pino_rele2              3   //PWM
#define pinoNaoUsado            4
#define pinoNaoUsado            5   //PWM
#define pinoNaoUsado            6   //PWM
#define pinoNaoUsado            7
#define pinoNaoUsado            8
#define pinoNaoUsado            9   //PWM
#define pinoNaoUsado            10  //PWM
#define pinoNaoUsado            11  //PWM
#define pinoNaoUsado            12  //PWM
#define pinoNaoUsado            13  //PWM

#define pinoNaoUsado            A0  //Analog
#define pinoNaoUsado            A1  //Analog
#define pinoNaoUsado            A2  //Analog
#define pinoNaoUsado            A3  //Analog
#define interfaceI2C            A4  //Analog
#define interfaceI2C            A5  //Analog

//Definimos as variantes de controle do termostato.___________
#define E_porta 0x68
#define msgBegin 10
#define debug 0

//Criamos as variaveis do sistema.____________________________
int leituraPorta[7];
bool ligado           = true;
bool ligado_2         = true;
bool msgPersonalizada = false;
String readString;

//Informacoes de endereco IP, gateway, mascara de rede________
byte mac    [] = { 0xA4, 0x28, 0x72, 0xCA, 0x55, 0x2F };
byte ip     [] = { 192, 168, 1, 110 };
byte gateway[] = { 192, 168, 1, 1 };
byte subnet [] = { 255, 255, 255, 0 };

//Criamos os objetos do sistema.______________________________
EthernetServer server(80);
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

void setup() {
#if debug == 1
  Serial.begin(9600);
#endif

  //Inicializa Ethernet Shield
  Ethernet.begin(mac, ip, gateway, subnet); //Inicializa a Ethernet-shield.
  server.begin();                           //Inicializa o object server da Ethernet-shield.
  inicia_GY521_MPU6050(E_porta);            //Inicializa o sensor Giroscopio.
  lcd.begin (16, 2);                        //Inicializa o display LCD.
  inicia_Rele(pino_rele1);                  //Inicializa o rele 1.
  inicia_Rele(pino_rele2);                  //Inicializa o rele 2.

#if debug == 1
  Serial.println("Guarabots - Automacao Residencial");
  Serial.println("Iniciado com sucesso!!!");
#endif

  //Desliga os dois reles
  estado_Rele(pino_rele1, HIGH);
  estado_Rele(pino_rele2, HIGH);

  //Imprime a logo da equipe no LCD. 
  lcd.setBacklight(HIGH);
  lcd.setCursor(3, 0);
  lcd.print("GuaraBots");
  lcd.setCursor(5, 1);
  lcd.print("DNO");
}

void loop() {
  EthernetClient client = server.available();

  if (client) {
    while (client.connected()) {
      if (client.available()) {

        char c = client.read();

        if (readString.length() < 100) {
          readString += c;
        }
        
        controle_RELE();
        controle_LCD();
        obtemDados_GY521_MPU6050(leituraPorta, E_porta);
        
        if (c == 'n') {    
          #if debug == 1
            Serial.println(readString);
          #endif
          readString = "";

          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println();
          client.println("<html>");
          client.println("  <head>");
          client.println("    <title>GuaraBots</title>");
          client.println("    <link rel='stylesheet' type='text/css' href='https://joaquimflavio.github.io/Guarabots/IOT_1/style.css'/>");
          client.println("    <script type='text/javascript' src='https://joaquimflavio.github.io/Guarabots/IOT_1/script.js'></script>");
          client.println("  </head>");
          client.println("  <body>");
          client.println("    <div id='wrapper'>");
          client.println("      <img id='logoGuara' alt='GUARABOTS' src='https://joaquimflavio.github.io/Guarabots/IOT_1/GuaraBots.png'/><br/>");
          client.println("      <div id='div1'>Rele 1</div>");
          client.println("      <div id='div2'>nada</div>");
          client.println("      <div id='rele'></div>");
          client.print("      <div id='estado' style='visibility: hidden;'>");client.print(ligado);client.println("</div>");
          client.println("      <div id='botao'></div>");
          client.println("      <div id='botao_2'></div>");
          client.println("      <div id='rele_2'></div>");
          client.print("      <div id='estado_2' style='visibility: hidden;'>");client.print(ligado_2);client.println("</div>");
          client.println("    </div>");
          client.println("  <script>AlteraRele1()</script><script>AlteraRele2()</script>");
          client.println("</body></head><html>");
          
          delay(1);
          client.stop();
        }
      }
    }
  }
}
