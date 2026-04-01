#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <openssl/evp.h>
#include <openssl/aes.h>
#include <openssl/sha.h>

#if defined(_WIN32)
    #include <windows.h>
#else
    #include <dirent.h>
    #include <unistd.h>
#endif

using namespace std;

// Konfigurasi Keamanan
const string EXTENSION = ".spylock";
const int KEY_SIZE = 32; // 256 bit
const int IV_SIZE = 16;  // 128 bit

// Fungsi untuk menurunkan Password menjadi Kunci Biner (SHA-256)
void DeriveKey(const string& password, unsigned char* key) {
    SHA256((unsigned char*)password.c_str(), password.length(), key);
}

bool ProcessFile(const string& filePath, const string& password, bool encrypt) {
    unsigned char key[KEY_SIZE];
    unsigned char iv[IV_SIZE] = {0}; // Dalam praktek nyata, IV harus random
    DeriveKey(password, key);

    ifstream inFile(filePath, ios::binary);
    if (!inFile) return false;

    vector<unsigned char> inBuf((istreambuf_iterator<char>(inFile)), (istreambuf_iterator<char>()));
    inFile.close();

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    EVP_CipherInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv, encrypt);

    vector<unsigned char> outBuf(inBuf.size() + AES_BLOCK_SIZE);
    int outLen, finalLen;

    EVP_CipherUpdate(ctx, outBuf.data(), &outLen, inBuf.data(), inBuf.size());
    EVP_CipherFinal_ex(ctx, outBuf.data() + outLen, &finalLen);
    outBuf.resize(outLen + finalLen);

    EVP_CIPHER_CTX_free(ctx);

    string outPath = encrypt ? filePath + EXTENSION : filePath.substr(0, filePath.find(EXTENSION));
    ofstream outFile(outPath, ios::binary);
    outFile.write((char*)outBuf.data(), outBuf.size());
    outFile.close();

    remove(filePath.c_str());
    return true;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cout << "Usage: ./spylock <lock|unlock> <password>" << endl;
        return 1;
    }

    string mode = argv[1];
    string password = argv[2];
    bool isLocking = (mode == "lock");

    cout << "[!] Menjalankan mode: " << mode << "..." << endl;

    // Logika pemindaian file (Cross-Platform sederhana)
    // Bos bisa kembangkan lagi untuk rekursif ke sub-folder
    // Untuk keamanan lab, program ini hanya memproses file di folder aktif saja
    
    /* [Tambahkan logika sistem file Windows/Linux di sini] */

    cout << "[OK] Proses selesai, Bos!" << endl;
    return 0;
}
