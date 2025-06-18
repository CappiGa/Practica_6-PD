# **Práctica 6-2 - Buses de comunicación II (SPI) - Lectura de etiquetas RFID**  

## **1. Descripción**  
Esta práctica utiliza el bus **SPI** para comunicar un **ESP32** con un módulo **RC522** (lector RFID), permitiendo la identificación de tarjetas y tags mediante su UID único. Se demuestra el flujo de datos maestro-esclavo típico de SPI y su aplicación en sistemas de identificación.  

---

## **2. Objetivos**  
- Configurar el bus SPI para comunicar el ESP32 con el módulo **MFRC522**.  
- Leer e interpretar el **UID** (Identificador Único) de tarjetas RFID.  

---

## **3. Materiales**  
- **ESP32** (o ESP32-S3).  
- **Módulo RFID RC522**.  
- **Tarjetas/tags RFID** (MIFARE).  
  [Image](https://github.com/user-attachments/assets/274d03ef-78ae-4e1f-aab1-06bab13f6c04)
---

## **4. Desarrollo**  

### **4.1 Configuración del entorno**  
1. Archivo `platformio.ini`:  
   ```ini
   [env:esp32]
   platform = espressif32
   board = esp32dev
   framework = arduino
   monitor_speed = 115200
   lib_deps = 
     MFRC522
   ```  

### **4.2 Programación**  
Código en `main.cpp`:  
```cpp
#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 5   // GPIO5 para Chip Select
#define RST_PIN 2  // GPIO2 para Reset

MFRC522 rfid(SS_PIN, RST_PIN);  // Objeto RC522

void setup() {
  Serial.begin(115200);
  SPI.begin();       // Inicia bus SPI
  rfid.PCD_Init();   // Inicia módulo RFID
  Serial.println("Acerca una tarjeta RFID...");
}

void loop() {
  // Verifica si hay una tarjeta presente
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {
    return;  // Si no hay tarjeta, reinicia el loop
  }

  // Extrae el UID y lo imprime en hexadecimal
  Serial.print("UID detectado: ");
  for (byte i = 0; i < rfid.uid.size; i++) {
    Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(rfid.uid.uidByte[i], HEX);
  }
  Serial.println();

  rfid.PICC_HaltA();  // Detiene la comunicación
}
```  

**Explicación del código**:  
- **Inicialización SPI**:  
  - `SPI.begin()` configura los pines SPI por defecto (MOSI=23, MISO=19, SCK=18).  
  - `rfid.PCD_Init()` prepara el módulo RC522.  
- **Lectura del UID**:  
  - `PICC_IsNewCardPresent()` detecta la presencia de una tarjeta.  
  - `PICC_ReadCardSerial()` lee el UID y lo almacena en `rfid.uid`.  

### **4.3 Conexión física**  
| RC522  | ESP32  |  
|--------|--------|  
| SDA    | GPIO5  |  
| SCK    | GPIO18 |  
| MOSI   | GPIO23 |  
| MISO   | GPIO19 |  
| GND    | GND    |  
| 3.3V   | 3.3V   |  

---

## **5. Resultados**  
- **Salida del monitor serie** (ejemplo con tarjeta presente):  
  ```plaintext
  Acerca una tarjeta RFID...
  UID detectado:  01 A3 7B 2D
  ```
  ![Image](https://github.com/user-attachments/assets/b70ce971-eba7-49f2-8b3d-aa656d2b30dd)
- **Funcionamiento**:  
  - El módulo RC522 escanea continuamente.  
  - Al acercar una tarjeta, el UID se imprime en formato hexadecimal.
   ![Image](https://github.com/user-attachments/assets/0c9fa0f8-f1c0-471b-a016-4047de884134)
  - Si no hay tarjeta, el loop se reinicia sin mostrar datos.  

---
---
