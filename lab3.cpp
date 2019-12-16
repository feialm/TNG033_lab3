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

	//Map kan ta in 2st värden
	// ett nyckel, lägger un i mappen
	// int är det vi vill ha, string är nyckeln för att hitta int
	// om man frågar map om string finns/ej, först sedan lägga in int
	auto table = std::map<std::string, int>{};
	int counter{0};
	std::string word = "";

	// Vector: To find unique words
	//skriver ej vec(table.size()) får då tomma slots eftersom vi tar bort värden i map
	std::vector<std::pair<std::string, int>> vec;

	//std::ifstream in_file{"X://TNG033//Labbar//Lab3NY//Code3//Code3//uppgift1//uppgift1.txt"};
	std::ifstream in_file{"X://TNG033//Labbar//Lab3NY//Code3//Code3//uppgift1//uppgift1_kort.txt"};

	//kollar att filen är ok
	if (!in_file) {
		std::cout << "Could not open input file!!\n";
		return 1;
	}

	// counter = number of occurences
	// table keeps for each word the number of occurrences
	while (in_file >> word) {
		
		// för att to-low orden
		std::transform(word.begin(), word.end(), word.begin(), [](char c) {return static_cast<char>(std::tolower(c)); });

		// delete different signs
		// en iterator är ett objekt som har egenskaper
		// std::remove(word.begin(), word.end(), ',' är en iterator med villkor, vad den ska göra
		// anropar next fukntion, returnera nästa som är enligt krav
		// remove skapar en iteror som letar upp alla komma-tecken
		// erase använder iteratorn för att ta bort ','
		// word.erase, det är funktionen erase som tar bort tecknen från objektet word

		word.erase(std::remove(word.begin(), word.end(), ','), word.end());
		word.erase(std::remove(word.begin(), word.end(), '.'), word.end());
		word.erase(std::remove(word.begin(), word.end(), '"'), word.end());
		word.erase(std::remove(word.begin(), word.end(), '?'), word.end());

		// Lägger in ord i vår map
		//map lägger bara in unika ord. Om ordet redan finns läggs den inte in.
		table[word]++;
		// counter = number of occurences
		++counter;
	}

	//vektorns storlek är antalet unika ord eftersom vi lägger över från map till vec och map innehåller bara unika ord.
	int uniqueValues = 0;

	//const för att få det att fungera
	// Sätter in våra unika ord i vektorn, ökar unika ord
	//vi kunde ej ta map.size() eftersom den räknar alla element som läggs in alltså string och int. Vi vill ju endast antal strings.
	//vi måste ha const för for_each få ej ändra på det den får in eftersom vi skickar in det som referens.
	//om vi skickar in det som kopy så hade vi inte behövt ha konstan för då ändrar vi ej ursprungsvärdet.
		std::for_each(table.begin(), table.end(),
		[&](std::pair<const std::string, int>& a) 
		{
			vec.push_back(std::make_pair(a.first, a.second));
			uniqueValues++;
		});

	//Kallar på MyComp och sorterar efter frekvens, därför behöver vi sorteringsfunktion (MyComp)
	std::sort(vec.begin(), vec.end(), MyComp());
	
	//Skriver ut antal ord, counter, som ökas i vår while-loop 
	std::cout << "Number of words in the file = " << counter << "\n";

	// Skriver ut våra unika ord, som ökas i for_each-loopen där vi lägger in värden i vektorn
	std::cout << "Number unique  words in the file = " << uniqueValues << "\n\n";

	std::cout << "Frequency table sorted alphabetically ... " << "\n\n";

	// Skriver ut våra ord sorterade alfabetiskt
	// Map (table) sorterar automatiskt alfabetiskt och de lägger bara in unika ord(??)
	std::for_each(table.begin(), table.end(),
	[](auto& a) { std::cout << std::setw(20) << std::left << a.first << a.second << "\n"; });

	std::cout << "\n\n" << "Frequency table sorted by frequence ... " << "\n\n";

	std::for_each(vec.begin(), vec.end(),
		[](auto& a) { std::cout << std::setw(20) << std::left << a.first << " " << a.second << "\n"; });

	//stänger fil
	in_file.close();

	return 0;
}