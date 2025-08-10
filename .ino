//codigo para MQ-2 en ESP32
//chatgpteado pero personalizado, la IA no tiene que hacer las cosas, vos tenes que decirle a la IA como queres que te haga
//para ver los datos en tiempo real, podes ir a "Tools>Serial Monitor" o en español "Herramientas>Monitor serie" y ahi ver los comentarios del estado del programa, si salen caracteres raros, setear la velocidad a 115200 Baudios

#include <WiFi.h>
#include <HTTPClient.h>

// Configuración WiFi
const char* ssidObjetivo = "NOMBRE DE TU RED WIFI"; //CAMBIAR
const char* password = "CONTRASEÑA DE TU RED WIFI"; //CAMBIAR


// Configuración MQ-2
const int pinMQ2 = 34;  // Pin analógico donde está conectado el MQ-2 (ADC1_CH6 en ESP32)

// Endpoint local
const char* endpoint = "http://<IP>:8080/MQ-2"; //CAMBIAR LA IP POR LA IP DONDE ESTA CORRIENDO TU WEB SERVICE

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("Escaneando redes WiFi...");
  int redesEncontradas = WiFi.scanNetworks();

  if (redesEncontradas == 0) {
    Serial.println("No se encontraron redes WiFi.");
    return;
  }

  bool redEncontrada = false;
  for (int i = 0; i < redesEncontradas; ++i) {
    String ssid = WiFi.SSID(i);
    int rssi = WiFi.RSSI(i);
    int canal = WiFi.channel(i);
    wifi_auth_mode_t seguridad = (wifi_auth_mode_t)WiFi.encryptionType(i);

    Serial.printf("%2d: %-30s  RSSI: %4d dBm  Canal: %2d  Seguridad: %d\n",
                  i + 1, ssid.c_str(), rssi, canal, seguridad);

    if (ssid == ssidObjetivo) {
      redEncontrada = true;
      if (canal > 11) {
        Serial.printf("La red '%s' está en canal %d (puede causar problemas para ESP32).\n", ssid.c_str(), canal);
      }
      Serial.printf("Red '%s' encontrada. Intentando conectar...\n", ssid.c_str());

      WiFi.begin(ssidObjetivo, password);

      unsigned long inicio = millis();
      while (WiFi.status() != WL_CONNECTED && millis() - inicio < 20000) {
        Serial.print(".");
        delay(500);
      }
      Serial.println();

      if (WiFi.status() == WL_CONNECTED) {
        Serial.println("Conectado con éxito!");
        Serial.print("IP: ");
        Serial.println(WiFi.localIP());
      } else {
        Serial.println("No se pudo conectar a la red.");
        Serial.print("Estado: ");
        Serial.println(WiFi.status());
      }
      break;  // Ya intentamos conectar, salimos del ciclo
    }
  }

  if (!redEncontrada) {
    Serial.printf("La red '%s' no se encontró en el escaneo.\n", ssidObjetivo);
  }
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    // Leer sensor MQ-2
    int valorAnalogico = analogRead(pinMQ2);
    // Convertir a voltaje (3.3V referencia y ADC de 12 bits: 0-4095)
    float voltaje = (valorAnalogico / 4095.0) * 3.3;

    Serial.printf("Sensor MQ-2 lectura analógica: %d, voltaje: %.3f V\n", valorAnalogico, voltaje);

    // Preparar JSON
    String jsonPayload = "{";
    jsonPayload += "\"nombre\":\"Sensor1\",";
    jsonPayload += "\"valor\":";
    jsonPayload += String(voltaje, 3);
    jsonPayload += "}";

    // Hacer POST HTTP
    HTTPClient http;
    http.begin(endpoint);
    http.addHeader("Content-Type", "application/json");

    int httpResponseCode = http.POST(jsonPayload);

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.printf("POST OK, código: %d, respuesta: %s\n", httpResponseCode, response.c_str());
    } else {
      Serial.printf("Error en POST: %d\n", httpResponseCode);
    }

    http.end();

  } else {
    Serial.println("No hay conexión WiFi, no se envía dato.");
  }

  delay(3000);  // Esperar 10 segundos entre lecturas y envíos
}
