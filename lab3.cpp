#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <cctype>
#include <numeric>
#include <iomanip>  //setw
#include <algorithm>
#include <vector>

struct MyComp {
	bool operator()(std::pair<std::string, int>& a, std::pair<std::string, int>& b) { return a.second > b.second; }
};

int main() {

	//Map kan ta in 2st v�rden
	// ett nyckel, l�gger un i mappen
	// int �r det vi vill ha, string �r nyckeln f�r att hitta int
	// om man fr�gar map om string finns/ej, f�rst sedan l�gga in int
	auto table = std::map<std::string, int>{};
	int counter{0};
	std::string word = "";

	// Vector: To find unique words
	//skriver ej vec(table.size()) f�r d� tomma slots eftersom vi tar bort v�rden i map
	std::vector<std::pair<std::string, int>> vec;

	//std::ifstream in_file{"X://TNG033//Labbar//Lab3NY//Code3//Code3//uppgift1//uppgift1.txt"};
	std::ifstream in_file{"X://TNG033//Labbar//Lab3NY//Code3//Code3//uppgift1//uppgift1_kort.txt"};

	//kollar att filen �r ok
	if (!in_file) {
		std::cout << "Could not open input file!!\n";
		return 1;
	}

	// counter = number of occurences
	// table keeps for each word the number of occurrences
	while (in_file >> word) {
		
		// f�r att to-low orden
		std::transform(word.begin(), word.end(), word.begin(), [](char c) {return static_cast<char>(std::tolower(c)); });

		// delete different signs
		// en iterator �r ett objekt som har egenskaper
		// std::remove(word.begin(), word.end(), ',' �r en iterator med villkor, vad den ska g�ra
		// anropar next fukntion, returnera n�sta som �r enligt krav
		// remove skapar en iteror som letar upp alla komma-tecken
		// erase anv�nder iteratorn f�r att ta bort ','
		// word.erase, det �r funktionen erase som tar bort tecknen fr�n objektet word

		word.erase(std::remove(word.begin(), word.end(), ','), word.end());
		word.erase(std::remove(word.begin(), word.end(), '.'), word.end());
		word.erase(std::remove(word.begin(), word.end(), '"'), word.end());
		word.erase(std::remove(word.begin(), word.end(), '?'), word.end());

		// L�gger in ord i v�r map
		//map l�gger bara in unika ord. Om ordet redan finns l�ggs den inte in.
		table[word]++;
		// counter = number of occurences
		++counter;
	}

	//vektorns storlek �r antalet unika ord eftersom vi l�gger �ver fr�n map till vec och map inneh�ller bara unika ord.
	int uniqueValues = 0;

	//const f�r att f� det att fungera
	// S�tter in v�ra unika ord i vektorn, �kar unika ord
	//vi kunde ej ta map.size() eftersom den r�knar alla element som l�ggs in allts� string och int. Vi vill ju endast antal strings.
	//vi m�ste ha const f�r for_each f� ej �ndra p� det den f�r in eftersom vi skickar in det som referens.
	//om vi skickar in det som kopy s� hade vi inte beh�vt ha konstan f�r d� �ndrar vi ej ursprungsv�rdet.
		std::for_each(table.begin(), table.end(),
		[&](std::pair<const std::string, int>& a) 
		{
			vec.push_back(std::make_pair(a.first, a.second));
			uniqueValues++;
		});

	//Kallar p� MyComp och sorterar efter frekvens, d�rf�r beh�ver vi sorteringsfunktion (MyComp)
	std::sort(vec.begin(), vec.end(), MyComp());
	
	//Skriver ut antal ord, counter, som �kas i v�r while-loop 
	std::cout << "Number of words in the file = " << counter << "\n";

	// Skriver ut v�ra unika ord, som �kas i for_each-loopen d�r vi l�gger in v�rden i vektorn
	std::cout << "Number unique  words in the file = " << uniqueValues << "\n\n";

	std::cout << "Frequency table sorted alphabetically ... " << "\n\n";

	// Skriver ut v�ra ord sorterade alfabetiskt
	// Map (table) sorterar automatiskt alfabetiskt och de l�gger bara in unika ord(??)
	std::for_each(table.begin(), table.end(),
	[](auto& a) { std::cout << std::setw(20) << std::left << a.first << a.second << "\n"; });

	std::cout << "\n\n" << "Frequency table sorted by frequence ... " << "\n\n";

	std::for_each(vec.begin(), vec.end(),
		[](auto& a) { std::cout << std::setw(20) << std::left << a.first << " " << a.second << "\n"; });

	//st�nger fil
	in_file.close();

	return 0;
}