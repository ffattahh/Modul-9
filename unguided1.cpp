#include <iostream>
#include <vector>
#include <set>
#include <climits>
#include <algorithm>

using namespace std;

// Struktur untuk merepresentasikan simpul dalam graph
struct Vertex {
    string nama;
    int jarak;
};

// Fungsi untuk membuat graph yang direpresentasikan sebagai adjacency matrix
vector<vector<int>> createGraph(vector<string>& vertices) {
    // Mendapatkan jumlah simpul dari user
    int numVertices_2311102019;
    cout << "Masukkan jumlah simpul: ";
    cin >> numVertices_2311102019;

    // Memasukkan nama simpul
    vertices.resize(numVertices_2311102019);
    for (int i = 0; i < numVertices_2311102019; i++) {
        cout << "Masukkan nama simpul " << i + 1 << ": ";
        cin >> vertices[i];
    }

    // Membangun adjacency matrix
    vector<vector<int>> adjacencyMatrix(numVertices_2311102019, vector<int>(numVertices_2311102019));
    for (int i = 0; i < numVertices_2311102019; i++) {
        for (int j = 0; j < numVertices_2311102019; j++) {
            if (i == j) {
                // Bobot untuk simpul yang sama selalu 0
                adjacencyMatrix[i][j] = 0;
            } else {
                cout << "Masukkan bobot " << vertices[i] << "-->" << vertices[j] << ": ";
                cin >> adjacencyMatrix[i][j];
            }
        }
    }

    return adjacencyMatrix;
}

// Fungsi untuk mencari jarak antara dua kota (simpul) dalam graph
int findDistance(const vector<vector<int>>& adjacencyMatrix, const vector<string>& vertices,
                 const string& startCity, const string& endCity) {
    // Mencari indeks kota awal dan kota tujuan dalam daftar simpul
    auto startIt = find(vertices.begin(), vertices.end(), startCity);
    auto endIt = find(vertices.begin(), vertices.end(), endCity);

    if (startIt == vertices.end() || endIt == vertices.end()) {
        return -1; // Kota tidak ditemukan
    }

    int startIndex = distance(vertices.begin(), startIt);
    int endIndex = distance(vertices.begin(), endIt);

    // Menghitung jarak menggunakan algoritma Dijkstra
    vector<int> distances(vertices.size(), INT_MAX);
    distances[startIndex] = 0;

    // Menginisialisasi set simpul yang belum dikunjungi
    set<int> unvisitedVertices;
    for (int i = 0; i < vertices.size(); i++) {
        unvisitedVertices.insert(i);
    }

    // Menjalankan algoritma Dijkstra
    while (!unvisitedVertices.empty()) {
        // Menemukan simpul dengan jarak terpendek dari simpul awal yang belum dikunjungi
        int currentVertex = *min_element(unvisitedVertices.begin(), unvisitedVertices.end(),
                                         [&](int i, int j) { return distances[i] < distances[j]; });

        // Menghapus simpul dari set simpul yang belum dikunjungi
        unvisitedVertices.erase(currentVertex);

        // Memperbarui jarak simpul yang terhubung dengan simpul saat ini
        for (int neighbor = 0; neighbor < vertices.size(); neighbor++) {
            if (adjacencyMatrix[currentVertex][neighbor] > 0 &&
                distances[currentVertex] + adjacencyMatrix[currentVertex][neighbor] < distances[neighbor]) {
                distances[neighbor] = distances[currentVertex] + adjacencyMatrix[currentVertex][neighbor];
            }
        }
    }

    // Mengembalikan jarak ke kota tujuan
    return distances[endIndex];
}

int main() {
    // Membangun graph
    vector<string> vertices;
    vector<vector<int>> adjacencyMatrix = createGraph(vertices);

    // Mencari jarak antara dua kota
    string kotaAwal, kotaAkhir;
    cout << "Masukkan nama kota awal: ";
    cin >> kotaAwal;
    cout << "Masukkan nama kota tujuan: ";
    cin >> kotaAkhir;

    int distance = findDistance(adjacencyMatrix, vertices, kotaAwal, kotaAkhir);

    // Menampilkan hasil
    if (distance == -1) {
        cout << "Tidak ada jalur dari " << kotaAwal << " ke " << kotaAkhir << "." << endl;
    } else {
        cout << "Jarak dari " << kotaAwal << " ke " << kotaAkhir << " adalah " << distance << " kilometer." << endl;
    }

    return 0;
}
