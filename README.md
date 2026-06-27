# Proyek Akhir: Sistem Kontrol Lampu Otomatis Berbasis Sensor Cahaya & Blynk

Sistem manajemen pencahayaan pintar (*Smart Lighting*) berbasis **Internet of Things (IoT)** menggunakan mikrokontroler **ESP32**, **Sensor LDR (Lux Converter)**, dan platform **Blynk Cloud** untuk efisiensi energi listrik rumah tangga.

---

## 📝 Identitas Mahasiswa & Kelas

| Informasi | Detail |
| :--- | :--- |
| **Mata Kuliah** | Sistem Mikrokontroler |
| **Kelas** | TIF K 23 B – Departemen Informatika |
| **Institusi** | Universitas Teknologi Bandung |
| **Dosen Pengampu**| Muchamad Rusdan, S.T., M.T. |
| **Nama** | Irgi Alyansa Perdana |
| **NIM** | 23552011210 |

---

## 🚀 Fitur Utama Sistem

* **Dual-Mode Operational:** Mendukung pemosisian sistem dalam mode otomatis (otomatisasi lampu berdasarkan intensitas cahaya sekitar) dan mode manual (intervensi kendali penuh dari aplikasi Blynk).
* **Konversi Lux Fisika Presisi:** Mengintegrasikan rumus konversi logaritmik Kurva Karakteristik Gamma (0.7) agar pembacaan intensitas cahaya (Lux) di Blynk sinkron 100% dan akurat sesuai simulator Wokwi.
* **Monitoring & Interaksi Real-Time:** Menampilkan status kondisi lingkungan (`SIANG ☀️` / `MALAM 🌙`) serta grafik/gauge nilai Lux secara instan pada antarmuka *smartphone*.
* **Mekanisme Fail-Safe Mode:** Proteksi sistem yang menolak perintah saklar manual secara otomatis apabila sistem masih berada dalam mode otomatis, mencegah konflik logika program.

---

## 🛠️ Komponen & Skema Rangkaian

1. **ESP32 Wi-Fi NodeMCU** (Mikrokontroler Utama)
2. **Sensor LDR (Photoresistor)** + Resistor Pembagi Tegangan $10\text{ k}\Omega$
3. **Modul LED / Relay** (Aktuator Lampu)
4. **Konektivitas:** Wi-Fi 2.4 GHz & Blynk IoT Cloud

---

## 📈 Rumus Fisika & Matematika (Konversi Lux)

Program memproses sinyal analog mentah ADC (0-4095) dari ESP32 menjadi besaran fisika standar **Lux** melalui 3 tahapan matematis:

1. **Konversi ADC ke Tegangan ($V_{out}$):**
   $$V_{out} = \frac{\text{Nilai ADC}}{4095.0} \times 3.3$$

2. **Menghitung Resistansi LDR ($R_{LDR}$):**
   $$R_{LDR} = \frac{10000.0 \times V_{out}}{3.3 - V_{out}}$$

3. **Perhitungan Kurva Gamma Logaritmik (Karakteristik Sensor):**
   $$\text{Lux} = 10.0 \times \left(\frac{50000.0}{R_{LDR}}\right)^{\frac{1.0}{0.7}}$$

---

## 🌐 Arsitektur Protokol Jaringan

Sistem komunikasi dirancang secara *end-to-end* menggunakan kombinasi protokol berikut:
* **ESP32 $\leftrightarrow$ Blynk Cloud:** Berjalan di atas soket **TCP/IP** menggunakan **Blynk Proprietary Protocol** (protokol biner khusus yang hemat daya dan ringan untuk *hardware*).
* **Aplikasi Android $\leftrightarrow$ Blynk Cloud:** Menggunakan **WebSockets (WSS)** untuk pengiriman instruksi tombol secara instan (*real-time*) dan **HTTPS** untuk otentikasi akun serta penarikan data historis awal.

---
<img width="1910" height="817" alt="Screenshot 2026-06-27 114304" src="https://github.com/user-attachments/assets/7559be1b-1455-4ea1-84ef-b29d3749faff" />

