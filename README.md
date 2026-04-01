# Lock-Ransomware PoC v1.0 🛡️

**WARNING: FOR EDUCATIONAL PURPOSES ONLY.**
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
