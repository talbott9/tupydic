#include <string>
#include <iostream>
#include <fstream>

const int NUMBER_OF_ENTRIES = 700;

struct Entry {
	std::string word;
	std::string classification;
	std::string definition1;
	std::string definition2;
	std::string definition3;
	std::string commentary;
	std::string porDefinition1;
	std::string porDefinition2;
	std::string porDefinition3;
	std::string engDefinition1;
	std::string engDefinition2;
	std::string engDefinition3;
	std::string variant1;
	std::string variant2;
	std::string variant3;
};

std::string s;
Entry entries[NUMBER_OF_ENTRIES];
std::ifstream wordlist("words");
int count;
int i;
char c;
std::string input;
bool quit;
bool success;
bool commentarySwitch;
int commentaryN;
bool tupyMode = 1;
bool languageIsEnglish = 0;
int verbetes;

void indexWords() {
	while(wordlist.get(c)) {
		if((isspace(c) || ispunct(c)) && !commentarySwitch) {
				switch(count) {
					case 0: entries[i].word = s; count++; break;
					case 1: entries[i].classification = s; count++; break;
					case 2: entries[i].porDefinition1 = s; entries[i].definition1 = s; count++; break;
					case 3: entries[i].porDefinition2 = s; entries[i].definition2 = s; count++; break;
					case 4: entries[i].porDefinition3 = s; entries[i].definition3 = s; count++; break;
					case 5: entries[i].commentary = s; count++; break;
					case 6: entries[i].engDefinition1 = s; count++; break;
					case 7: entries[i].engDefinition2 = s; count++; break;
					case 8: entries[i].engDefinition3 = s; count++; break;
					case 9: entries[i].variant1 = s; count++; break;
					case 10: entries[i].variant2 = s; count++; break;
					case 11: entries[i].variant3 = s;
						i++; verbetes++; count = 0; break;
				}
				s = "";
		} else {
			if(isdigit(c)) {
				commentaryN++;
				if(commentaryN == 1)
					commentarySwitch = 1;
				else {
					commentarySwitch = 0;
					commentaryN = 0;
				}
			} else {
				s += c;
			}
		}
	}
}

int cmp_nocase(const std::string& s, const std::string& s2) {
	std::string::const_iterator p = s.begin();
	std::string::const_iterator p2 = s2.begin();
	std::string::const_iterator q = s.end();

	/*
	if(!(isalpha(*s.begin()))) {
		p++;
		q--;
	}

	//printf("%c\n", *(s.end() - 1));
	if(!(isalpha(*(s.end() - 1)))) {
		q -= 2;
	}*/
	
	while(p!=q && p2!=s2.end()) {
		if(toupper(*p) != toupper(*p2)) return (toupper(*p)<toupper(*p2)) ? -1 : 1;
		++p;
		++p2;
	}
	return(s2.size() == s.size()) ? 0 : (s.size() < s2.size()) ? -1 : 1;
}

int main(int args, char* argv) 
{
	indexWords();
	printf("%s%i%s\n", "\nDicionário breve da língua tupi (", verbetes, " entries) v1.0\nCopyright (c) 2022 by Henrique Costa - phbrownbr@hotmail.com\n   Type '!' to quit\n   Type '?P' for Portuguese-Tupi, '?T' for Tupi-Portuguese\n   Type '>e' to change translations to English, '>p' to change back to Portuguese\n");
	while(!quit) {
		success = 0;
		printf("%s", "=>");
		std::cin>>input;
		if(input == "!")
			quit = 1;
		else if(input == "?P") {
			tupyMode = 0;
			if(!languageIsEnglish)
				printf("Portuguese-Tupi mode is now on.\n\n");
			else
				printf("English-Tupi mode is now on.\n\n");
		}
		else if(input == "?T")  {
			tupyMode = 1;
			if(!languageIsEnglish)
				printf("Tupi-Portuguese mode is now on.\n\n");
			else
				printf("Tupi-English mode is now on.\n\n");
		}
		else if(input == ">e") {
			printf("Definitions are now in English.\n\n");
			languageIsEnglish = 1;
			for(int i = 0; i < NUMBER_OF_ENTRIES; i++) {
				entries[i].definition1 = entries[i].engDefinition1;
				entries[i].definition2 = entries[i].engDefinition2;
				entries[i].definition3 = entries[i].engDefinition3;
			}
		} 
		else if(input == ">p") {
			printf("Definitions are now in Portuguese.\n\n");
			languageIsEnglish = 0;
			for(int i = 0; i < NUMBER_OF_ENTRIES; i++) {
				entries[i].definition1 = entries[i].porDefinition1;
				entries[i].definition2 = entries[i].porDefinition2;
				entries[i].definition3 = entries[i].porDefinition3;
			}
		}
		else {
			for(int i = 0; i < NUMBER_OF_ENTRIES; i++) {
				if(tupyMode) {
					if(cmp_nocase(input, entries[i].word) == 0 || cmp_nocase(input, entries[i].variant1) == 0 || cmp_nocase(input, entries[i].variant2) == 0 || cmp_nocase(input, entries[i].variant3) == 0) {
						std::string symbol1 = "";
						std::string symbol2 = "";
						if(entries[i].classification == "SUF")
							symbol1 = "-";
						else if(entries[i].classification == "PREF")
							symbol2 = "-";
						std::cout << std::endl << symbol1 << entries[i].word << symbol2 << "     " << entries[i].classification << std::endl << entries[i].definition1 << "; ";
						if(entries[i].definition2 != "")
							std::cout << entries[i].definition2 << "; ";
						if(entries[i].definition3 != "")
							std::cout << entries[i].definition3 << "; ";
						if(entries[i].commentary != "")
							std::cout << "(" << entries[i].commentary << "); ";
						std::cout << std::endl;
						success = 1;
					}
				} else {
					if(cmp_nocase(input, entries[i].definition1) == 0 || cmp_nocase(input, entries[i].definition2) == 0 || cmp_nocase(input, entries[i].definition3) == 0) {
						std::string symbol1 = "";
						std::string symbol2 = "";
						if(entries[i].classification == "SUF")
							symbol1 = "-";
						else if(entries[i].classification == "PREF")
							symbol2 = "-";
						std::cout << std::endl << symbol1 << entries[i].word << symbol2 << "     " << entries[i].classification << std::endl << entries[i].definition1 << "; ";
						if(entries[i].definition2 != "")
							std::cout << entries[i].definition2 << "; ";
						if(entries[i].definition3 != "")
							std::cout << entries[i].definition3 << "; ";
						if(entries[i].commentary != "")
							std::cout << "(" << entries[i].commentary << "); ";
						std::cout << std::endl;
						success = 1;
					}
				}
			}
			if(!success)
				std::cout << input << "     ?????     UNKNOWN";
			std::cout << std::endl << std::endl;
		}
	}

}
