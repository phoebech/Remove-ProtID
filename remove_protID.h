#ifndef REMOVE_ID_H
#define REMOVE_ID_H

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <cassert>

using namespace std;

class Remove_ID {

/************************************************************************
this program accounts for a different number of fasta and mart samples.
in the real file, there are more fasta samples than mart samples
fasta: 180869
mart: 104965
the program eliminates samples that:
1) does not have a protID
2) cannot be found in the biomart file
************************************************************************/

private:
	// sample sizes
	int num_samples_fasta;
	int num_samples_mart_export;
	int num_samples_to_insert;

	// KEY: <ENSG, ENST>
	// VALUE: whether it has a prot ID
	map< pair<string, string> , bool> mart;

	// KEY: <ENSG, ENST>
	// VALUE: <line1, rest of the lines>
	map< pair<string, string> , pair<string, string> > fasta;

	// stores the two lines to write to the new file
	vector< pair<string,string> > to_insert;

public:
	Remove_ID() {
		num_samples_fasta = 0;
		num_samples_mart_export = 0;
	}

	// EFFECTS: reads in the FASTA file and storing contents in "fasta"
	void read_fasta(istream& is) {

		string header;
		string sequence;
		vector<string> header_row;
		string gene_stable;
		string transcript_stable;

		char foo; is >> foo;

		while (getline(is, header)) {

			header_row = parse_line(header); // parses the header

			// erasing stuff to only have the gene/transcript ID
			// stores ENSG code in "gene_stable"
			// stores ENST code in "transcript_stable"
			gene_stable = header_row[3];
			gene_stable.erase(0, 5);
			gene_stable.erase(15, 3);
			transcript_stable = header_row[0];
			transcript_stable.erase(15, 2);

			// pair that stores the ENSG, ENST strings (KEY)
			pair<string, string> gene_names (gene_stable, transcript_stable);

			// pair that stores the contents of each sequence (VALUE)
			// line 1 (header), remaining
			pair<string, string> contents;

			contents.first = '>' + header;

			// reading in DNA sequence
			getline(is, sequence, '>');
			contents.second = sequence;

			pair< pair<string, string>, pair<string, string> > final;
			final.first = gene_names;
			final.second = contents;
			fasta.insert(final);

			++num_samples_fasta;
		}

		/*** TESTING ***/
		/*for (auto i:fasta) {
			cout << "ENSG: " << (i.first).first << endl;
			cout << "ENST: " << (i.first).second << endl;
			cout << "header: " << (i.second).first << endl;
			cout << "body: " << (i.second).second << endl << endl << endl;
		}*/


	}


	// EFFECTS: reads in the mart_export file and storing contents in "mart"
	void read_mart_export(istream& is) {

		string line;
		vector<string> row;
		string gene_stable;
		string transcript_stable;

		// reading in header
		getline(is, line);

		while (getline(is, line)) {

			// reading file (line by line) and storing it in the 3 variables
			row = parse_line(line);
			gene_stable = row[0];
			transcript_stable = row[1];

			// determining if a protID exists
			bool ID_exist = true;
			if (static_cast<int>(row.size()) == 2) {
				ID_exist = false;
			}

			// inserting into map "mart"
			pair<string, string> ID (gene_stable, transcript_stable);
			mart.insert( pair< pair<string,string>, bool>(ID, ID_exist));

			++num_samples_mart_export;	// to determine number of samples
		}

		/***** TESTING ****/
		/*for (auto i:mart) {
			cout << (i.first).first << endl;
			cout << (i.first).second << endl;
			cout << i.second << endl;
		}*/

	}


	// EFFECTS: parses a line of words into a vector of individual words
	vector<string> parse_line(const string &str) {
		istringstream source(str);
		vector<string> contents;
		string content;

		while (source >> content) {
			contents.push_back(content);
		}

		return contents;
	}


	// EFFECTS: determines what samples to write to the
	// 			new file and storing in "to_insert"
	void store_to_insert() {
		for (auto i:mart) {
			if (i.second == true) {
				to_insert.push_back(fasta[i.first]);
				++num_samples_to_insert;
			}
		}

		/**** TESTING ****/
		/*for (auto i:to_insert) {
			cout << i.first << endl;
			cout << i.second << endl;
		}
		cout << "num samples: " << num_samples_to_insert << endl;*/
	}


	// EFFECTS: writes only the samples with protID to a new file
	void write(ostream& os) {
		for (auto i:to_insert) {
			os << i.first << endl;
			os << i.second;
		}
	}

	// EFFECTS: summarizes the data files
	void summary() {
		cout << "SUMMARY: " << endl;
		cout << "number of fasta samples: " << num_samples_fasta << endl;
		cout << "number of mart samples: " << num_samples_mart_export << endl;
		cout << "number of final samples: " << num_samples_to_insert << endl;
		cout << endl;
	}

};

#endif



