# Lock-Ransomware PoC v1.0 🛡️

**WARNING :**

FOR EDUCATIONAL PURPOSES ONLY.**
Alur kerja enkripsi data menggunakan AES-256 CBC Mode untuk riset keamanan siber.

## 🚀 Fitur
- **AES-256 Encryption**: Standar industri, bukan XOR biasa.
- **PBKDF (Password Based)**: Mengubah string password menjadi kunci biner SHA-256.
- **Cross-Platform**: Support Windows (CMD/PowerShell) & Linux Terminal.

## 🛠️ Instalasi
### Prerequisites
Anda wajib menginstall library **OpenSSL**.

**Linux (Ubuntu/Debian):**
```bash
sudo apt-get install libssl-dev
```
**Windows :**

Gunakan MSYS2 atau vcpkg untuk install OpenSSL, lalu link-kan ke compiler C++ Anda.
​Kompilasi

**Cara Penggunaan :**

​Pindahkan file executable ke folder eksperimen (Laptop Lab).
​Mengunci File:
```bash
./spylock lock RahasiaBos123
```
Membuka File :
```bash
./spylock unlock RahasiaBos123
```
**Tips Eksperimen di Laptop :**

* Coba buat password yang sangat panjang (32 karakter lebih).
* Coba kunci file `.png` (foto), lalu lihat apakah bisa dibuka tanpa di-unlock dulu.
* **Tantangan:** Coba hapus 1 byte saja di tengah file `.spylock`, lalu coba unlock. Bos akan melihat bahwa enkripsi modern sangat sensitif; rusak 1 bit saja, seluruh file tidak bisa dipulihkan. Ini yang disebut *Integrity Failure*.

**Alur Keamanan Password :**

Program ini menggunakan **SHA-256**. Jadi, meskipun anda masukkan password pendek seperti "ABC", program akan mengubahnya menjadi deretan kode unik sepanjang 256-bit yang konsisten. Berbeda dengan XOR yang hanya membolak-balik bit, AES melakukan proses substitusi, pergeseran baris, dan pencampuran kolom berkali-kali (rounds). Tanpa password yang benar-benar sama, mustahil mengembalikan file ini lewat *brute force* dalam waktu singkat.

**Disclaimer :**

​Penyalahgunaan alat ini untuk aktivitas ilegal adalah tanggung jawab pengguna. Penulis tidak bertanggung jawab atas kerusakan data akibat kehilangan password.
