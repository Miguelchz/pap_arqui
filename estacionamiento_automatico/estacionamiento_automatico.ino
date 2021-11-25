int retardo = 5;      // Tiempo de retardo en milisegundos (Velocidad del Motor)
int dato;             // valor recibido en grados
int numero_pasos = 0; // Valor en grados donde se encuentra el motor
String leeCadena;     // Almacena la cadena de datos recibida

//Sensores
int detector1;
int detector2;
int detector3;
int detector4;
int detector5;
int detector6;
//leds
const int LED1 = 2;
const int LED2 = 3;
const int LED3 = 4;
const int LED4 = 5;
const int LED5 = 6;
const int LED6 = 7;

void setup()
{
  Serial.begin(9600); // inicializamos el puerto serie a 9600 baudios
  //salidas motor pap
  pinMode(11, OUTPUT); // Pin 11 conectar a IN4
  pinMode(10, OUTPUT); // Pin 10 conectar a IN3
  pinMode(9, OUTPUT);  // Pin 9 conectar a IN2
  pinMode(8, OUTPUT);  // Pin 8 conectar a IN1
  //entrada de sensores IR
  pinMode(detector1, INPUT);
  pinMode(detector2, INPUT);
  pinMode(detector3, INPUT);
  pinMode(detector4, INPUT);
  pinMode(detector5, INPUT);
  pinMode(detector6, INPUT);
}

void loop()
{
  while (Serial.available())
  {
    // Leer el valor enviado por el Puerto serial
    delay(retardo);
    char c = Serial.read(); // Lee los caracteres
    leeCadena += c;         // Convierte Caracteres a cadena de caracteres
  }
  if (leeCadena.length() > 0)
  {
    int op = leeCadena.toInt(); // Convierte Cadena de caracteres a Enteros
    //se le indica cuantos grados debe moverse dependiendo de la posición ingresada
    switch (op)
    {
    case 1:
      dato = 30;
      break;
    case 2:
      dato = 90;
      break;
    case 3:
      dato = 150;
      break;
    case 4:
      dato = -150;
      break;
    case 5:
      dato = -90;
      break;
    case 6:
      dato = -30;
      break;
    }

    Serial.print(dato); // Envia valor en Grados
    Serial.print(" Grados --> ");
    delay(retardo);
    dato = (dato * 1.4222222222); // Ajuste de 512 vueltas a los 360 grados 1.4222222222
    Serial.print(dato);           // Envia valor en Grados
    Serial.println(" pasos");
  }

  bool terminado = false; // será true si el primer giro termina para luego regresar a la pasicion de origen

  //Mientras el giro continue el while se seguirá ejecutando
  while (!girar_motor(dato))
  {
    int pasos; //
    //Si los grados convertidos son positivos se sumara uno, si son negativos se le resta uno y luego se compara
    if (dato >= 0)
    {
      pasos = numero_pasos + 1;
    }
    else
    {
      pasos = numero_pasos - 1;
    }
    //compara si los pasos de la primera vuelta ya fueron alcanzados
    if (dato == pasos)
    {
      terminado = true;
    }
  }
  //Si terminado es true se regresa el giro a la posicion de origen
  if (terminado == true)
  {
    delay(3000);
    dato = dato * -1; // se invieten los pasos
    //Serial.println("Si entra");

    terminado = false;
    dato = 0;
  }
  leeCadena = ""; // Inicializamos la cadena de caracteres recibidos
  apagado();      // Apagado del Motor para que no se caliente

  sensores();
}
///////////////////// Fin del Loop ///////////////////////////

void paso_der()
{ // Pasos a la derecha
  digitalWrite(11, LOW);
  digitalWrite(10, LOW);
  digitalWrite(9, HIGH);
  digitalWrite(8, HIGH);
  delay(retardo);
  digitalWrite(11, LOW);
  digitalWrite(10, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(8, LOW);
  delay(retardo);
  digitalWrite(11, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(9, LOW);
  digitalWrite(8, LOW);
  delay(retardo);
  digitalWrite(11, HIGH);
  digitalWrite(10, LOW);
  digitalWrite(9, LOW);
  digitalWrite(8, HIGH);
  delay(retardo);
}

void paso_izq()
{ // Pasos a la izquierda
  digitalWrite(11, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(9, LOW);
  digitalWrite(8, LOW);
  delay(retardo);
  digitalWrite(11, LOW);
  digitalWrite(10, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(8, LOW);
  delay(retardo);
  digitalWrite(11, LOW);
  digitalWrite(10, LOW);
  digitalWrite(9, HIGH);
  digitalWrite(8, HIGH);
  delay(retardo);
  digitalWrite(11, HIGH);
  digitalWrite(10, LOW);
  digitalWrite(9, LOW);
  digitalWrite(8, HIGH);
  delay(retardo);
}

void apagado()
{ // Apagado del Motor
  digitalWrite(11, LOW);
  digitalWrite(10, LOW);
  digitalWrite(9, LOW);
  digitalWrite(8, LOW);
}

bool girar_motor(int pasos)
{

  while (pasos > numero_pasos)
  { // Girohacia la izquierda en grados
    //Serial.println("giro a la izquierda");
    paso_izq();
    numero_pasos = numero_pasos + 1;
    if (pasos == numero_pasos)
    {
      return true;
    }
    return false;
  }
  while (pasos < numero_pasos)
  { // Giro hacia la derecha en grados
    paso_der();
    //Serial.println("giro a la derecha");
    numero_pasos = numero_pasos - 1;
    if (pasos == numero_pasos)
    {
      return true;
    }
    return false;
  }
}

void sensores()
{
  //int value = 0;
  detector1 = analogRead(A0);
  detector2 = analogRead(A1);
  detector3 = analogRead(A2);
  detector4 = analogRead(A3);
  detector5 = analogRead(A4);
  detector6 = analogRead(A5);

  //value = digitalRead(detector);
  //Serial.println (detector);

  //Serial.println(detector1);

  if (detector1 > 450)
  {

    //Serial.println ("Detectado obstaculo sensor 1");

    digitalWrite(LED1, HIGH);
  }
  else
  {
    digitalWrite(LED1, LOW);
  }

  if (detector2 > 450)
  {

    //Serial.println ("Detectado obstaculo sensor 2 ");

    digitalWrite(LED2, HIGH);
  }
  else
  {
    digitalWrite(LED2, LOW);
  }
  if (detector3 > 450)
  {

    //Serial.println ("Detectado obstaculo sensor 3");

    digitalWrite(LED3, HIGH);
  }
  else
  {
    digitalWrite(LED3, LOW);
  }
  if (detector4 > 450)
  {

    //Serial.println ("Detectado obstaculo sensor 4");

    digitalWrite(LED4, HIGH);
  }
  else
  {
    digitalWrite(LED4, LOW);
  }
  if (detector5 > 450)
  {

    //Serial.println ("Detectado obstaculo sensor 5");

    digitalWrite(LED5, HIGH);
  }
  else
  {
    digitalWrite(LED5, LOW);
  }
  if (detector6 > 450)
  {

    //Serial.println ("Detectado obstaculo sensor 6");

    digitalWrite(LED6, HIGH);
  }
  else
  {

    digitalWrite(LED6, LOW);
  }
}
