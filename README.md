"""# Proyek Akhir: Sistem Kontrol Lampu Otomatis Berbasis Sensor Cahaya & Blynk

Sistem manajemen pencahayaan pintar (*Smart Lighting*) berbasis **Internet of Things (IoT)** menggunakan mikrokontroler **ESP32**, **Sensor LDR (Lux Converter)**, dan platform **Blynk Cloud** untuk efisiensi energi listrik rumah tangga.

---

## 📝 Identitas Mahasiswa & Kelas

| Informasi | Detail |
| :--- | :--- |
| **Mata Kuliah** | Sistem Mikrokontroler |
| **Kelas** | Contoh TIF RM 22 CID – Departemen Informatika |
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

## 💻 Cara Instalasi & Penggunaan (Wokwi)

1. **Salin Berkas Proyek:** Masukkan berkas `sketch.ino`, `diagram.json`, dan `libraries.txt` ke dalam workspace simulator Wokwi Anda.
2. **Konfigurasi Blynk Console:**
   * Buat Datastream Baru pada Pin Virtual `V0` (Tipe: Double, Min: 0, Max: 10000, Unit: Lux).
   * Buat Datastream Tombol/Saklar pada `V1` (Mode Auto/Manual) dan `V2` (Kendali Lampu).
   * Buat Datastream Teks pada `V5` (Status Siang/Malam).
3. **Kredensial Token:** Sesuaikan baris `#define BLYNK_TEMPLATE_ID`, `BLYNK_TEMPLATE_NAME`, dan `BLYNK_AUTH_TOKEN` pada bagian teratas `sketch.ino` dengan kredensial dari *device* Blynk IoT Anda.
4. **Jalankan Simulasi:** Klik tombol *Play* pada Wokwi, geser *slider* interaktif LDR, dan amati sinkronisasi data pada *Dashboard* Blynk Android Anda!
"""

with open("README-v2.md", "w", encoding="utf-8") as f:
    f.write(readme_content_v2)

print("File README-v2.md berhasil dibuat dengan judul yang diperbarui.")
