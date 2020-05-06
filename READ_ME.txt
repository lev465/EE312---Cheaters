Cheaters!
Luis Vazquez
05/07/2020
EE312
GitHub link: https://github.com/lev465/EE312---Cheaters

To run the program: 
	make
	./plagiarismCatcher <file_dir> <word_sequence> <similarity>

where <file_dir> - directory for the files intended to check
      <word_sequence> - number of consecutive words to check
      <similarity> - number of word_sequence matches that are deemed the minimum to consider cheating

EXAMPLE: 
	./plagiarismCatcher big_doc_set 6 200
this will check all files in big_doc_set for all documents that have more than 200 6-word sequence similarities in common.

Output will be to the main screen in the following format:
	<similarity>: <fileName1> - <fileName2>

example output:

	1824: smu0.txt - hce209.txt
	1675: sra31.txt - bgt61.txt

This program will determine similarities between documents that could suggest plagiarism.

Files of the given directory are read in through a queue for the number of words given by the program to concatenate.
Elements of the files read are evaluated as strings and all nonalphanumeric characters are removed. Additionally, all letters are converted to lower-case.
The string fed to the hash function, in turn, is the modified string of concatenated words from the file consisting of only lowercase letters and numbers.

The hash function for the strings is the following:
hash = sum(s[i]*11^i)%(hashtablesize)

This works best when more words are concatenated before being sent to the hash function and would be a poor indicator for lower-valued concatenations. Additionally, the hash table size was chosen based on the big_doc_set size, so running for smaller document sets means inefficiency in memory. 

From arguments being fed into the program from the command line, it is assumed that the directory given is valid.
