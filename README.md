# 🧠 Sistema Distribuido de Monitoreo de Temperatura con MQTT  
**Arduino UNO R4 WiFi + Clean Architecture**

---

## 📦 Descripción general

Este proyecto implementa un sistema IoT distribuido con dos dispositivos **Arduino UNO R4 WiFi** que se comunican a través del protocolo **MQTT**:

- **`sensor_publisher/`**: Mide temperatura con un sensor **MAX6675** y publica alertas al tópico MQTT `sensor/alerta` si el valor está fuera del rango aceptable.
- **`led_subscriber/`**: Se suscribe al tópico de alerta y **enciende o apaga un LED** dependiendo del estado recibido.

Ambos módulos están estructurados siguiendo los principios de **Clean Architecture**, garantizando modularidad, claridad y escalabilidad.

---

## 🧱 Estructura del repositorio

```
final-mqtt/
├── sensor_publisher/
│   ├── src/
│   │   ├── domain/
│   │   ├── application/
│   │   ├── interfaces/
│   │   ├── infrastructure/
│   │   └── main.cpp
│   └── platformio.ini
│
├── led_subscriber/
│   ├── src/
│   │   ├── domain/
│   │   ├── application/
│   │   ├── interfaces/
│   │   ├── infrastructure/
│   │   └── main.cpp
│   └── platformio.ini
└── README.md
```

---

## ⚙️ Requisitos

- 2 placas Arduino UNO R4 WiFi (Renesas RA4M1)
- Sensor de temperatura MAX6675 + termopar tipo K (solo en `sensor_publisher`)
- Acceso a red WiFi
- Broker MQTT (ej: `broker.hivemq.com`)
- Editor: [VS Code + PlatformIO](https://platformio.org/)

---

## 📡 Comunicación MQTT

| Tópico          | Payload | Significado                    |
|-----------------|---------|-------------------------------|
| `sensor/alerta` | `"1"`   | Temperatura fuera de rango     |
| `sensor/alerta` | `"0"`   | Temperatura normal             |

---

## 📋 Configuración de PlatformIO

### `sensor_publisher/platformio.ini`

```ini
[env:sensor_publisher]
platform = renesas-ra
board = uno_r4_wifi
framework = arduino
lib_deps =
  robertalexa/MAX6675
  arduino-libraries/WiFiS3
  256dpi/MQTT
```

### `led_subscriber/platformio.ini`

```ini
[env:led_subscriber]
platform = renesas-ra
board = uno_r4_wifi
framework = arduino
lib_deps =
  arduino-libraries/WiFiS3
  256dpi/MQTT
```

---

## 🚀 Cómo funciona

### `sensor_publisher`:
- Lee temperatura cada 10 segundos
- Si está fuera del rango `15°C - 45°C`, publica `"1"` en `sensor/alerta`
- Si está dentro del rango, publica `"0"`

### `led_subscriber`:
- Se suscribe al tópico `sensor/alerta`
- Si recibe `"1"` → Enciende el LED (pin 8)
- Si recibe `"0"` → Apaga el LED

---

## 🧱 Clean Architecture aplicada

Cada módulo está organizado por capas:

- `domain/`: Entidades como `SensorReading` y `Alerta`
- `application/`: Casos de uso (`DetectarAlertaUseCase`, `ProcesarAlertaUseCase`)
- `interfaces/`: Interfaces (puertos) como `AlertaPublisherPort`
- `infrastructure/`: Adaptadores concretos como `LedAlertPresenter` o `MQTTPublisherAdapter`
- `main.cpp`: Punto de entrada con lógica de conexión e interacción

---


