#define BLYNK_TEMPLATE_ID "TMPL6T6kfcowT"
#define BLYNK_TEMPLATE_NAME "LDR Control"
#define BLYNK_AUTH_TOKEN "r1vsjfDb3bMYI5Qz-wK9OcV_Uk8L-0JJ"


#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// Kredensial WiFi Simulator Wokwi
char ssid[] = "Wokwi-GUEST";
char pass[] = "";

// Definisi Pin ESP32
const int ldrPin = 34; // Pin Analog untuk Sensor LDR
const int ledPin = 2;  // Pin Digital untuk Lampu/Relay

// Variabel Global
int ldrValue = 0;
float luxValue = 0.0;
bool autoMode = true; // Default awal: Mode Otomatis aktif
bool manualLedState = false;

BlynkTimer timer;

// ==========================================
// FUNGSI 1: Dijalankan saat sukses terhubung ke Blynk
// ==========================================
BLYNK_CONNECTED() {
  Serial.println("Terhubung ke Server Blynk!");
  
  // Sinkronisasi status tombol mode (V1)
  Blynk.virtualWrite(V1, autoMode ? 1 : 0);
  
  // Atur kondisi awal indikator LED di Blynk
  if (autoMode) {
    Blynk.virtualWrite(V3, 0);   // LED Manual (V3) MATI
    Blynk.virtualWrite(V4, 255); // LED Otomatis (V4) NYALA
  } else {
    Blynk.virtualWrite(V3, 255); // LED Manual (V3) NYALA
    Blynk.virtualWrite(V4, 0);   // LED Otomatis (V4) MATI
  }
}

// ==========================================
// FUNGSI 2: Membaca Sensor LDR & Logika Otomatis
// ==========================================
void sendSensorData() {
  ldrValue = analogRead(ldrPin); // Membaca data mentah (0 - 4095)

  // -- RUMUS KONVERSI LUX AKURAT WOKWI --
  // 1. Konversi ADC ke Tegangan (Voltage 3.3V)
  float voltage = ldrValue / 4095.0 * 3.3;
  
  // Mencegah error pembagian dengan nol
  if (voltage >= 3.3) voltage = 3.299; 
  if (voltage <= 0) voltage = 0.001;
  
  // 2. Menghitung Resistansi LDR (Modul menggunakan resistor 10k Ohm)
  float rLDR = (10000.0 * voltage) / (3.3 - voltage);
  
  // 3. Konversi Logaritmik (Karakteristik Gamma = 0.7, RL10 = 50k)
  luxValue = 10.0 * pow((50000.0 / rLDR), (1.0 / 0.7));

  // Kirim nilai Lux ke Gauge Blynk (V0)
  Blynk.virtualWrite(V0, luxValue); 

  // -- LOGIKA PENENTU SIANG/MALAM & KONTROL LAMPU --
  // Batas 50 Lux digunakan sebagai penanda transisi siang/malam
  if (luxValue < 50) {
    Blynk.virtualWrite(V5, "MALAM 🌙"); // Kirim status ke V5
    
    if (autoMode) {
      digitalWrite(ledPin, HIGH); // Nyalakan lampu karena gelap
      Blynk.virtualWrite(V2, 1);  // Sinkronisasi tombol Blynk
    }
  } else {
    Blynk.virtualWrite(V5, "SIANG ☀️"); // Kirim status ke V5
    
    if (autoMode) {
      digitalWrite(ledPin, LOW);  // Matikan lampu karena terang
      Blynk.virtualWrite(V2, 0);  // Sinkronisasi tombol Blynk
    }
  }
}

// ==========================================
// FUNGSI 3: Menerima Perintah Tombol Mode (V1)
// ==========================================
BLYNK_WRITE(V1) {
  autoMode = param.asInt(); 
  
  if (autoMode) {
    Serial.println("Mode Sistem: OTOMATIS");
    Blynk.virtualWrite(V3, 0);   // LED Indikator Manual MATI
    Blynk.virtualWrite(V4, 255); // LED Indikator Otomatis NYALA
  } else {
    Serial.println("Mode Sistem: MANUAL");
    Blynk.virtualWrite(V3, 255); // LED Indikator Manual NYALA
    Blynk.virtualWrite(V4, 0);   // LED Indikator Otomatis MATI
  }
}

// ==========================================
// FUNGSI 4: Menerima Perintah Tombol Lampu (V2)
// ==========================================
BLYNK_WRITE(V2) {
  if (!autoMode) { 
    // Eksekusi jika dalam mode MANUAL
    manualLedState = param.asInt();
    digitalWrite(ledPin, manualLedState);
    
    if (manualLedState) {
      Serial.println("Lampu Dinyalakan secara MANUAL");
    } else {
      Serial.println("Lampu Dimatikan secara MANUAL");
    }
  } else {
    // Tolak eksekusi jika dalam mode OTOMATIS
    Blynk.virtualWrite(V2, digitalRead(ledPin)); // Kembalikan posisi tombol
    Serial.println("Peringatan: Gagal! Sistem sedang dalam mode OTOMATIS.");
  }
}

// ==========================================
// SETUP & LOOP UTAMA
// ==========================================
void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  pinMode(ldrPin, INPUT);

  Serial.println("Memulai sistem...");
  Serial.println("Menghubungkan ke WiFi dan Blynk...");
  
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Jalankan fungsi sendSensorData setiap 1000 milidetik (1 detik)
  timer.setInterval(1000L, sendSensorData);
}

void loop() {
  Blynk.run();
  timer.run();
}
