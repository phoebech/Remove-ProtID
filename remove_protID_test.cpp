#include "remove_protID.h"
#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

int main(int argc, char* argv[]) {

	// [execution name] [fasta file] [mart_export]
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

	return 0;
}