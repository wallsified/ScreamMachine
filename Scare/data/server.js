/* 
Creamos un objeto "db" con las caracteristicas que ocuparemos para el juego. 
*/
var db = {
  value: "", //atributo único del objeto db
  letmeKnow() {
    console.log("DB changed");
  },
  get giveDb() {
    //getter
    return this.value;
  },
  set setDB(value) {
    //setter
    this.value = value;
    //this.letmeKnow();
  },
};

/* 
Función de intervarlo constante en la ejecución. 
1. Se crea una nueva solicitud XMLHTTP
2. Verificamos que haya información del lado del servidor. 
3. Recibimos un valor de regreso, y apartir de este comparamos la respuesta para interactuar 
con la bateria del juego. 
4. Confirmamos la solicitud en cuestión. 
5. Mandamos la solicitud. 
*/
setInterval(function () {
  var xhttp = new XMLHttpRequest(); //Request al ESP32
  xhttp.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
      //Digamos, si si hay algo del otro lado del código
      db.setDB = Number(this.responseText); //consideramos la respuesta y la transformamos a numero.
      var giveMeSomeNoise = db.giveDb; //Asignamos la respuesta a una variable y de ahi trabajamos.
      if (giveMeSomeNoise != 49) {
        //49 es el valor db promedio de un cuarto. Consideramos lecturas mayores.
        setTimeout(gameOn(giveMeSomeNoise), 7000); //función tipo delay de Javascript. Recibe una función y el tiempo.
      } else if ((giveMeSomeNoise = 49)) {
        setTimeout(gameOff(),7000);
      }
    }
  };
  xhttp.open("GET", "/decibel", true); //Confirmamos solicitud.
  xhttp.send(); //Mandamos solicitud.
}, 100);

/* 
Función que considera un valor de entrada para alterar propiedades CSS de elementos HTML
*/
function gameOn(value) {
  if (52 < value && value <= 54) {
    //Buscamos en el documento por ID y cambiamos la propiedad de estilo del mismo.
    document.getElementById("segment-1").setAttribute("style", "opacity:100%;");
    setTimeout(gameOff, 6000);
  } else if (55 <= value && value <= 57) {
    document.getElementById("segment-1").setAttribute("style", "opacity:100%;");
    document.getElementById("segment-2").setAttribute("style", "opacity:100%;");
    setTimeout(gameOff, 6000);
  } else if (58 <= value && value <= 60) {
    document.getElementById("segment-1").setAttribute("style", "opacity:100%;");
    document.getElementById("segment-2").setAttribute("style", "opacity:100%;");
    document.getElementById("segment-3").setAttribute("style", "opacity:100%;");
    setTimeout(gameOff, 6000);
  } else if (61 <= value && value <= 62) {
    document.getElementById("segment-1").setAttribute("style", "opacity:100%;");
    document.getElementById("segment-2").setAttribute("style", "opacity:100%;");
    document.getElementById("segment-3").setAttribute("style", "opacity:100%;");
    document.getElementById("segment-4").setAttribute("style", "opacity:100%;");
    setTimeout(gameOff, 6000);
  } else if (63 <= value && value < 70) {
    document.getElementById("segment-1").setAttribute("style", "opacity:100%;");
    document.getElementById("segment-2").setAttribute("style", "opacity:100%;");
    document.getElementById("segment-3").setAttribute("style", "opacity:100%;");
    document.getElementById("segment-4").setAttribute("style", "opacity:100%;");
    document.getElementById("segment-5").setAttribute("style", "opacity:100%;");
    document.getElementById("circle").setAttribute("style", "opacity:100%;");
    alert("¡Hey Wazowski dejanos algo! ¡Buen Grito, has encendido la puerta! ¡Gracias por Jugar!");
    setTimeout(gameOff, 6000);
  } /* else if (64 <= value && value <= 66) {
    document.getElementById("segment-1").setAttribute("style", "opacity:100%;");
    document.getElementById("segment-2").setAttribute("style", "opacity:100%;");
    document.getElementById("segment-3").setAttribute("style", "opacity:100%;");
    document.getElementById("segment-4").setAttribute("style", "opacity:100%;");
    document.getElementById("segment-5").setAttribute("style", "opacity:100%;");
    document.getElementById("segment-6").setAttribute("style", "opacity:100%;");
    setTimeout(gameOff, 6000);
  } else if (67 <= value && value < 70) {
    document.getElementById("segment-1").setAttribute("style", "opacity:100%;");
    document.getElementById("segment-2").setAttribute("style", "opacity:100%;");
    document.getElementById("segment-3").setAttribute("style", "opacity:100%;");
    document.getElementById("segment-4").setAttribute("style", "opacity:100%;");
    document.getElementById("segment-5").setAttribute("style", "opacity:100%;");
    //document.getElementById("segment-6").setAttribute("style", "opacity:100%;");
    //document.getElementById("segment-7").setAttribute("style", "opacity:100%;");

    setTimeout(gameOff, 6000); */
  }

/* 
Función contraria a gameOn. "Apaga" los elementos HTML del archivo. 
*/
function gameOff() {
  document.getElementById("segment-1").setAttribute("style", "opacity:0%;");
  document.getElementById("segment-2").setAttribute("style", "opacity:0%;");
  document.getElementById("segment-3").setAttribute("style", "opacity:0%;");
  document.getElementById("segment-4").setAttribute("style", "opacity:0%;");
  document.getElementById("segment-5").setAttribute("style", "opacity:0%;");
  //document.getElementById("segment-6").setAttribute("style", "opacity:0%;");
  //document.getElementById("segment-7").setAttribute("style", "opacity:0%;");
  document.getElementById("circle").setAttribute("style", "opacity:0%;");
}
