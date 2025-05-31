 #include <iostream>
 #include <conio.h>
 #include <fstream>
 #include <string>
 
using namespace std;

#define TITLE "=== SIMERU ===\n"

struct JadwalKuliah {
	string matkul;
	string dosen;
	string waktu;
	string kebutuhan;
};

int getMaxId() {
	fstream index("index-jadwal.txt", fstream::in);
	
	int ID = 0;
	
	while (!index.eof()) {
		index.get();
		ID++;
	};
	
	index.close();
	return ID;
}

string getNewId() {
	int max = getMaxId();
	
	return to_string(max+1);
}

void registerNewId() {
	fstream index("index-jadwal.txt", fstream::out | fstream::app);
	
	index << '#';
	index.close();
}

string getJadwal(string id) {
	fstream f("jadwal/"+id+".txt", fstream::in);
	string a;
	
	if (f.is_open()) {	
		
		while (!f.eof()){
			char t = f.get();
			if (t=='-') return "removed";
			a.push_back(t);
		};
	} else {
		return "removed";
	}
	

	
	return a;
}

class User {
	
	private:
		bool HAS_ADMIN_ACCESS = false;
		bool LOGGED_IN = false;
	
	public:
		User (string username, string password) {
			if (username=="admin" && password=="1994") {
				HAS_ADMIN_ACCESS=true;
				LOGGED_IN=true;
			} else if (username=="mahasiswa" && password=="1994") {
				LOGGED_IN=true;
			}
		};
		
		bool authorized () {
			return LOGGED_IN;
		};
		
		bool is_admin() {
			return HAS_ADMIN_ACCESS;
		};
		
		void Jadwal() {
			system("cls");
			ShowJadwal();
			getch();
			Menu();
		};
		
		void ShowJadwal() {
			int ID_COUNT = getMaxId();
			
			for (int i = 0; i <= ID_COUNT; i++) {
				string id = to_string(i);
				string info = getJadwal(id);
				if (info != "removed") {
					cout << "id:"<<i<<" =================\n";
					cout << info << endl;
				}
			}
		}
		
		void DownloadJadwal() {
			fstream d("hasil-jadwal.txt", fstream::out);
			int ID_COUNT = getMaxId();
			for (int i = 0; i <= ID_COUNT; i++) {
				string id = to_string(i);
				string info = getJadwal(id);
				if (info != "removed") {
					d << "id:"<<i<<" =================\n";
					d << info << endl;
				}
			};
			
			cout << "Jadwal sudah di download di hasil-jadwal.txt.";
			getch();
			Menu();
		}
		
		void NewJadwal() {
			system("cls");
			
			JadwalKuliah baru;
			
			cout << "Mata Kuliah: "; cin >> baru.matkul;
			cout << "Dosen: "; cin >> baru.dosen;
			cout << "Waktu: "; cin >> baru.waktu;
			cout << "Kebutuhan Ruang: "; cin >> baru.kebutuhan;
			
			string id = getNewId();
			registerNewId();
			
			cout << "Menambahkan jadwal...\n";
			
			string dir = "jadwal/" + id + ".txt";
			
			fstream f(dir, fstream::out); 
			
			f << "Mata Kuliah: " << baru.matkul << '\n';
			f << "Dosen: " << baru.dosen << '\n';
			f << "Waktu: " << baru.waktu << '\n';
			f << "Kebutuhan Ruang: " << baru.waktu << '\n';
			
			f.close();
			
			cout << "Jadwal kuliah sudah ditambahkan!";
			getch();
			Menu();
		};
		
		void RemoveJadwal() {
			system("cls");
			ShowJadwal();
			cout << "\nPilih ID jadwal yang ingin dihapus:";
			int id;
			cin >> id;
			string dir = "jadwal/" + to_string(id) + ".txt";
			
			fstream f(dir, fstream::out);
			f << "-";
			
			f.close();
			
			cout << "Jadwal sudah dihapuskan.";
			getch();
			Menu();
		}
		
		void Menu () {
			system("cls");
			cout << TITLE;
			
			int validOptionCount = 2;
			
			cout << "1. Tampilkan Jadwal Kuliah\n";
			cout << "2. Unduh jadwal\n";
			
			if (HAS_ADMIN_ACCESS) {
				validOptionCount = 4;
				cout << "3. Tambah Jadwal Kuliah Baru\n";
				cout << "4. Hapus Jadwal Kuliah\n";
			};
			
			int option;
			
			cout << "Pilih opsi: "; cin >> option;
			bool INVALID = false;
			
			if (option > validOptionCount) {
				cout << "Opsi tidak valid!";
				INVALID=true;
				
			} else {
				switch (option) {
					case 1:
						Jadwal();
						break;
					case 2:
						DownloadJadwal();
						break;
					case 3:
						NewJadwal();
						break;
					case 4:
						RemoveJadwal();
						break;
					default:
						cout << "Opsi tidak valid!";
						INVALID=true;		
				}
			};
			
			if (INVALID) {
				getch();
				Menu();
			}
		}
};

User login() {
	system("cls");
	
	string username, password;
	
	cout << TITLE;
	cout << "Username: "; cin >> username;
	cout << "Password: "; cin >> password;
	
	User newUser(username, password);
	
	return newUser;
}

int main () {
	User user = login();
	
	if (user.authorized()) {
		user.Menu();
	} else {
		cout << "Username dan Password salah!";
	}
	
}
