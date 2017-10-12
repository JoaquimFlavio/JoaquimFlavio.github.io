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
#include <SPI.h>
#include <Ethernet.h>
String readString;

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
#define pinoNaoUsado            A4  //Analog
#define pinoNaoUsado            A5  //Analog

//Definimos as variantes de controle do termostato.___________
#define debug 0

//Criamos as variaveis do sistema.____________________________
boolean ligado    = true;
boolean ligado_2  = true;

//Informacoes de endereco IP, gateway, mascara de rede________
byte mac    [] = { 0xA4, 0x28, 0x72, 0xCA, 0x55, 0x2F };
byte ip     [] = { 192, 168, 0, 110 };
byte gateway[] = { 192, 168, 0, 1 };
byte subnet [] = { 255, 255, 255, 0 };

//Criamos os objetos do sistema.______________________________
EthernetServer server(80);

void setup() {
#if debug == 1
  Serial.begin(9600);
#endif

  //Inicializa Ethernet Shield
  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();

  inicia_Rele(pino_rele1);
  inicia_Rele(pino_rele2);

  //Desliga os dois reles
  estado_Rele(pino_rele1, HIGH);
  estado_Rele(pino_rele2, HIGH);

#if debug == 1
  Serial.println("Guarabots - Automacao Residencial");
  Serial.println("Iniciado com sucesso!!!");
#endif
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
        
        if (c == 'n') {
          //Liga o Rele 1___________________________________
          if (readString.indexOf("?ligar") > 0) {
            estado_Rele(pino_rele1, LOW);
            ligado = false;
          }
          else {
            //Desliga o Rele 1______________________________
            if (readString.indexOf("?desligar") > 0) {
              estado_Rele(pino_rele1, HIGH);
              ligado = true;
            }
          }

          //Liga o Rele 2___________________________________
          if (readString.indexOf("?2_ligar") > 0) {
            estado_Rele(pino_rele2, LOW);
            ligado_2 = false;
          }
          else {
            //Desliga o Rele 2______________________________
            if (readString.indexOf("?2_desligar") > 0) {
              estado_Rele(pino_rele2, HIGH);
              ligado_2 = true;
            }
          }
          
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
