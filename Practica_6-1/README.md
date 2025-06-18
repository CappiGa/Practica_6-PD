
# **Práctica 6-1 - Buses de comunicación II (SPI) - Lectura/Escritura en Memoria SD**  

## **1. Descripción**  
Esta práctica implementa el uso del bus **SPI** en el **ESP32-S3** para interactuar con una tarjeta **SD**, demostrando la escritura y lectura de archivos. Se explora el protocolo SPI, su configuración y las ventajas de su arquitectura maestro-esclavo en aplicaciones de almacenamiento.  
---

## **2. Objetivos**  
- Comprender el funcionamiento del bus **SPI** y su comparación con otros protocolos.  
- Configurar el ESP32-S3 para comunicación SPI con una tarjeta SD.  
- Escribir y leer datos en un archivo almacenado en la tarjeta SD.  

### **3. Resumen teórico**  
#### **Protocolo SPI**  
- **Arquitectura**: Maestro-esclavo con 4 líneas mínimas:  
  - **MOSI** (Master Out Slave In): Datos del maestro al esclavo.  
  - **MISO** (Master In Slave Out): Datos del esclavo al maestro.  
  - **SCK** (Clock): Señal de sincronización.  
  - **SS/CS** (Slave Select): Selección del dispositivo esclavo.  
- **Características**:  
  - **Full-duplex**: Transmisión bidireccional simultánea.  
  - **Alta velocidad**: Hasta 80 MHz en ESP32.  
  - **Modos de operación**: 4 posibles (SPI_MODE0 a SPI_MODE3) según polaridad y fase del reloj.  

#### **ESP32-S3 y SPI**  
- **Pines por defecto**:  
  - **MOSI**: GPIO11  
  - **MISO**: GPIO13  
  - **SCK**: GPIO12  
  - **CS**: GPIO10 (personalizable).  

---

## **4. Materiales**  
- **ESP32-S3**  
- **Tarjeta microSD** (formateada en FAT32).  
- **Lector de tarjetas SD** (compatible con SPI).    
- **Cable USB-C**.  
![Image](https://github.com/user-attachments/assets/3bccd17d-3587-4808-bc8b-18cb94ab9825)
---

## **5. Desarrollo**  

### **5.1 Preparación del entorno**
1. Crear un nuevo proyecto en PlatformIO.  
2. Configurar el archivo `platformio.ini`con el siguiente contenido:  
   ```ini
   [env:esp32-s3]
   platform = espressif32
   board = esp32-s3-devkitc-1
   framework = arduino
   monitor_speed = 9600
   lib_deps =
       SD(esp32)
   ```  

### **5.2 Programación**  
Código en `main.cpp`:  
```cpp
#include <Arduino.h>
#include <SD.h>

File myFile;

void setup() {
  Serial.begin(9600);
  Serial.print("Iniciando SD...");
  
  if (!SD.begin(4)) {  // Inicia SPI con CS en pin 4
    Serial.println("¡Error al inicializar la SD!");
    return;
  }
  Serial.println("SD inicializada correctamente.");

  // Escribir en archivo
  File archivo = SD.open("/ejemplo.txt", FILE_WRITE);
  if (archivo) {
    Serial.println("Escribiendo en archivo...");
    archivo.println("Hola, este es un archivo creado en la SD con ESP32-S3.");
    archivo.close();
    Serial.println("Escritura completada.");
  } else {
    Serial.println("Error al abrir el archivo para escritura.");
  }

  // Leer archivo
  myFile = SD.open("/ejemplo.txt");
  if (myFile) {
    Serial.println("Contenido de /ejemplo.txt:");
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    myFile.close();
  } else {
    Serial.println("Error al abrir el archivo para lectura.");
  }
}

void loop() {}  // No se usa
```  

**Explicación del código**:  
- **`SD.begin(4)`**: Inicia la comunicación SPI con el pin **GPIO4** como Chip Select (CS).  
- **Escritura**:  
  - `SD.open("/ejemplo.txt", FILE_WRITE)` abre el archivo en modo escritura.  
  - `archivo.println()` escribe líneas de texto.  
- **Lectura**:  
  - `SD.open("/ejemplo.txt")` abre el archivo en modo lectura.  
  - `myFile.read()` muestra el contenido por el puerto serie.  

### **5.3 Conexión física**  
1. Conectar el lector SD al ESP32-S3:  
   - **MOSI → GPIO11**  
   - **MISO → GPIO13**  
   - **SCK → GPIO12**  
   - **CS → GPIO4** (configurable en código).  
2. Alimentar el lector con **3.3V**.  

---

## **6. Resultados**  
- **Salida del monitor serie**:  
  ```plaintext
  Iniciando SD...SD inicializada correctamente.
  Escribiendo en archivo...
  Escritura completada.
  Contenido de /ejemplo.txt:
  Hola, este es un archivo creado en la SD con ESP32-S3.
  ```
 ![Image](https://github.com/user-attachments/assets/2aae0e8f-8e6e-4600-bf61-4c87a6b23ab9)
---
