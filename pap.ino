
int retardo = 5;      // Tiempo de retardo en milisegundos (Velocidad del Motor)
int dato;             // valor recibido en grados
int numero_pasos = 0; // Valor en grados donde se encuentra el motor
String leeCadena;     // Almacena la cadena de datos recibida

void setup()
{
  Serial.begin(9600);  // inicializamos el puerto serie a 9600 baudios
  pinMode(11, OUTPUT); // Pin 11 conectar a IN4
  pinMode(10, OUTPUT); // Pin 10 conectar a IN3
  pinMode(9, OUTPUT);  // Pin 9 conectar a IN2
  pinMode(8, OUTPUT);  // Pin 8 conectar a IN1
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
    switch(op){
      case 1:
        dato = 30;
        break;
      case 2:
        dato = 90;
        break;
      case 3:
        dato = 120;
        break;
      case 4:
        dato = -120;
        break;
      case 5:
        dato = -90;
        break;
      case 6:
        dato = -30;
        break;
    }

    Serial.print(dato);       // Envia valor en Grados
    Serial.print(" Grados --> ");
    delay(retardo);
    dato = (dato * 1.4222222222); // Ajuste de 512 vueltas a los 360 grados 1.4222222222
    Serial.print(dato);              // Envia valor en Grados
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
    Serial.println("Si entra");

    terminado = false; 
    dato = 0;
  }
  leeCadena = ""; // Inicializamos la cadena de caracteres recibidos
  apagado();      // Apagado del Motor para que no se caliente
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
