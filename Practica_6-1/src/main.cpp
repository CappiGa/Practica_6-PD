#include <Arduino.h>
#include <SD.h>


File myFile;
void setup()
{
Serial.begin(9600);
Serial.print("Iniciando SD ...");
if (!SD.begin(4)) {
Serial.println("No se pudo inicializar");
return;
}
Serial.println("inicializacion exitosa");
File archivo = SD.open("/ejemplo.txt", FILE_WRITE);
if (archivo) {
Serial.println("Escribiendo en archivo ejemplo.txt...");
archivo.println("Hola, este es un archivo creado en la SD con ESP32-S3.");
archivo.println("Puedes modificar este código para escribir más datos.");
archivo.close(); // Cierra el archivo después de escribir
Serial.println("Archivo escrito correctamente.");
} else {
Serial.println("Error al crear el archivo.");
}
myFile = SD.open("/ejemplo.txt");//abrimos el archivo
if (myFile) {
Serial.println("/ejemplo.txt:");
while (myFile.available()) {
Serial.write(myFile.read());
}
myFile.close(); //cerramos el archivo
} else {
Serial.println("Error al abrir el archivo");
}
}
void loop()
{
}