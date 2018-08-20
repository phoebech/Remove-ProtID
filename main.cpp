#include "remove_protID.h"
#include <fstream>
using namespace std;

// command line format: 
// [execution name] [fasta file] [mart_export] [new file]

int main(int argc, char* argv[]) {

	// error check
	if (argc != 4) {
		cout << "wrong # arguments" << endl;
		return 1;
	}

	Remove_ID removeID;

	// reading in fasta file
	ifstream fin_fasta;
	fin_fasta.open(argv[1]);
	if (!fin_fasta.is_open()) {
		cout << "failed fasta" << endl;
		return 1;
	}
	removeID.read_fasta(fin_fasta);
	fin_fasta.close();

	// reading in mart file
	ifstream fin_mart;
	fin_mart.open(argv[2]);
	if (!fin_mart.is_open()) {
		cout << "failed mart" << endl;
		return 1;
	}
	removeID.read_mart_export(fin_mart);
	fin_mart.close();

	removeID.store_to_insert();

	// writing out
	ofstream fout;
	fout.open(argv[3]);
	removeID.write(fout);
	fout.close();

	removeID.summary();

	return 0;
}