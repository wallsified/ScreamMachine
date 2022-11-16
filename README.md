<h2 align='center'>
  "Los sustos no se estudian, se hacen y ya está..."
</h2>

O al menos, eso creiamos. Lo que pasa es que nos volvimos universitarios...

## ¿Qué hace el proyecto?

Al final de Monsters University, el juego final de las
"Sustolimpiadas" consiste en una cámara de simulación 
de sustos, en donde el equipo que más puntos-por-susto
consiga, será nombrado campeón. 

Nosotros hicimos una aproximación a dicho juego usando 
lo que aprendimos en el curso de _Introducción a Ciencias de
la Computación_ y algo de creativad inocente.

## ¿Por qué este proyecto?

La verdad es que fue una ocurrencia coincidente. 

Uno de nosotros un día jugando con una máquina de garra en una plaza pasó de pensar sobre como esas máquinas son modificadas
a la máquina de garra de _Pizza Planeta_ de _Toy Story_ y de alguna forma recordó la sección que dio pie a este proyecto.  

A su vez, no tenemos Sustolimpiadas, ¿por qué no al menos intentar hacer un juego de ellas?


## ¿Qué necesito para replicar el proyecto?

Vas a necesitar lo siguiente: 

- Microcontrolador ESP32 
- IDE de Arduino
- Librerias especificas de Arduino 

Para este punto, copia el contenido de la carpeta _"Sketchbook"_
en la carpeta del mismo nombre en tu sistema operativo. (en sistemas Linux, está en _/home/Arduino_)

- Unidad de Micrófono Electret de 9x7mm
- Comparador de Voltaje LM393
- Pantalla OLED 1.3’’ IIC
- Cable USB - MicroUSB
- Breadboard / Protoboard y conectores para las conexiones 
- Modificar el código donde sea necesario (ya viene señalizado donde) 


## Créditos

- Librerias usadas en el proyecto: 

1. Wifi.h
2. [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer)
3. [SPIFFS File Uploader](https://github.com/me-no-dev/arduino-esp32fs-plugin)
4. Wire.h
5. Adafruit_GFX.h
6. Adafruit_SH110X.h

Nota: Las librerias sin enlace se instalan desde el gestor de bibliotecas en el IDE de Arduino. 

<br>

> _“¡He estado esperando esto toda mi vida! ¡Voy a ser un asustador!”_