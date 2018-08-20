# Remove-ProtID

This is a program I developed while working as a research assistant at a Bioinformatics laboratory at the University of Michigan. This program traverses a large genomic dataset (.FASTA files - a text-based file format for representing DNA/RNA nucleotide sequences in Bioinformatics) and removes transcripts without a corresponding protein ID (uniproKD ID). The corresponding protein ID database is located at http://ensembl.org/biomart/martview/84bc3bb777a39e9b7c24df5683b20aff. Once the transcripts without a protein ID is removed, the FASTA file can undergo further statistical analyses.

Please see the "test" folder for examples of .FASTA files and protein database files. 
