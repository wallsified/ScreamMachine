/* Proyecto Final: Asustometro!

  Código modificado por los alumnos:
  - Paredes Zamudio Luis Daniel @Wallsified
  - González Arceo Carlos Eduardo @Carlos-crea

¿Qué hace el proyecto?

Al final de Monsters University, el juego final de las
"Sustolimpiadas" consiste en una cámara de simulación 
de sustos, en donde el equipo que más puntos-por-susto
consiga, será nombrado campeón. 

Nosotros hicimos una aproximación a dicho juego usando 
lo que aprendimos en el curso de Introducción a Ciencias de
la Computación y algo de creativad inocente.

*/

//Bibliotecas----------------------------------
#include "WiFi.h" 
#include "ESPAsyncWebServer.h" //ESP32 as a server
#include "SPIFFS.h" //Sistema de archivos
#include "Wire.h" 
#include "Adafruit_GFX.h" //Ésta y la siguiente son para la pantalla. 
#include "Adafruit_SH110X.h"

//SSID y Password de la red a conectarse. Deben de llenarse para poderse ejecutar. 
const char* ssid = "INFINITUMA6A4_2.4"; 
const char* password = "Zamudiov3!";
String decibels = "0";

//Configuraciones de la pantalla. 
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1       // Reset pin 
Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#define i2c_Address 0x3c
const int sampleWindow = 50;  // La pantalla se refresca cada 50ms

//Lectura del Micrófono mediante el comparador de voltaje. 
unsigned int sample;  

//Objeto AsyncWebServer, puerto 80-------------
AsyncWebServer server(80);

/* 
  Función que inicializa la pantalla al momento de empezar el programa
 */
void start_screen() {
  display.begin(i2c_Address, true); //Inicia pantalla              
  display.clearDisplay(); //Limpiamos lo que pudo estar antes. 
  display.setCursor(0, 0); //Coordenadas de inicio. 
  display.setTextSize(1); //Tamaño de letra
  display.setTextColor(SH110X_WHITE); //Color de letra
  display.display(); 
  delay(1000);
  display.clearDisplay();
}

/* 
Función que escribe la pantalla OLED el valor ingresado al ESP32, junto a su llenado correspondiente en la barra. 
 */
void writeScreen(float decibelLevel) {
  display.setCursor(0, 0);
  display.setTextSize(2);
  display.print(decibelLevel); //Imprimimos el valor del micrófono. 
  display.print(" dB");

  for (int x = 23; x < 185; x = x + 24) {
    display.drawLine(x, 32, x, 27, SH110X_WHITE); //División de los segmentos de la barra en pantalla.  
  }

  display.drawRoundRect(0, 32, 120, 19, 6, SH110X_WHITE);       //borde de la bateria en pantalla
  int r = map(decibelLevel, 0, 120, 1, 120);                       //la bateria tiene el borde la pantalla con eso
  display.fillRoundRect(1, 33, r, 18, 6, SH110X_WHITE);         //y ahora la acompletamos por "dentro"
  display.display();
  display.clearDisplay();
}

/* 
Función de inicialización de la conexión web. 
 */
void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Conectando a: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi conectado");
  Serial.println("Dirección IP: ");
  Serial.println(WiFi.localIP());
  delay(2000);

  //Función para error 404
  server.onNotFound([](AsyncWebServerRequest * request) {
    request->send(404, "text/plain", "Error 404");
  });
}


/* 
Acciones a realizar durante la ejecución.
 */
String processor(const String& var) {

  if (var == "DECIBEL") {
    return decibels;
  }
  return String();
}

/* 
Función que recibe la lectura del micrófono y la convierte a decibeles. 
 */
float readDecibels() {
  unsigned long startMillis = millis();                  // no podemos usar delay() en este caso. 
  float puntoAPunto = 0;                                  //Es el rango de lecturas a trabajar. 
  unsigned int signalMax = 0;                            
  unsigned int signalMin = 700;                         //Aunque el valor máximo es 1024, bajarlo a 700 ayuda a hacerlo más sensible.

  // Consideramos 50 ms para tomar la muestra de db. 
  while (millis() - startMillis < sampleWindow)
  {
    sample = analogRead(34);                             //lectura del microfono
    if (sample < 500)                                  // quitamos lecturas no necesarias. 
    {
      if (sample > signalMax)
      {
        signalMax = sample;                           // solo val. max.
      }
      else if (sample < signalMin)
      {
        signalMin = sample;                           // solo val. min. 
      }
    }
  }
  puntoAPunto = signalMax - signalMin;                    // max - min = amplitud peak-peak 
  float db = map(puntoAPunto, 20, 900, 49.5, 90);         //calibramos a que si nos de los decibeles. 
  return db;
}

/* 
Transformación de readDecibels a una función que regresa un string. 
 */ 
String ReadSensor() {
  float sensorVal = readDecibels();
  Serial.println(sensorVal);
  return String(sensorVal);
}

/* 
Función setup. Considera lo previo a realizar antes de la ejecución. 
 */
void setup() {
  //Iniciamos los Leds en output usando un bucle for para recorrer el arreglo.
  Serial.begin(115200);
  
  setup_wifi();
  start_screen();
  server.begin();

  //Revisar archivos subidos a la memoria flash---
  if (!SPIFFS.begin(true)) {
    Serial.println("Hubo un error en SPIFFS. Vuelve a enviar los archivos.");
    return;
  }

  //Ruta raíz del archivo HTML-----------------
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });

  //Archivo CSS--------------------------------
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/style.css", "text/css");
  });

  //  Archivo JS--------------------------------
  server.on("/help.js", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/server.js", "text/js");
  });

  // Imágenes --------------------------------
  server.on("/door2.png", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/door2.png", "image/png");
  });

  // Enviar información sobre los decibeles.
  server.on("/decibel", HTTP_GET, [](AsyncWebServerRequest * request) {
    Serial.println(ReadSensor().c_str());
    request->send(200, "text/plain", ReadSensor().c_str());
  });
}

//Loop para ir escribiendo en pantalla la información calculada. 
void loop() {
  float dbToScreen = readDecibels();
  writeScreen(dbToScreen);
  delay(500);
}
