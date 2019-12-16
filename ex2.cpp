#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <locale>  //to lower
#include <cctype>
#include <numeric>
#include <iterator>
#include <utility>
#include <algorithm>
#include <vector>
#include <cmath>
#include <set>



int main() {

	//***************Detta funkar med att läsa in det med iterators********************//

	//std::vector<std::string> vec;
	//
	//std::ifstream in_file{ "C://Users//elidj//Cplus2//Labbar//Lab3//Code3//Code3//uppgift2//uppgift2_kort.txt" };

	////kollar att filen är ok
	//if (!in_file) {
	//	std::cout << "Could not open input file!!\n";
	//	return 1;
	//}
	//else {
	//	std::cout << "Open!!\n";
	//}

	////Läser in filen till en iterator
	//std::istream_iterator<std::string> first(in_file);
	//std::istream_iterator<std::string> last;
	//

	////skriver ut iteratorn till consolen
	//std::copy(first, last, std::ostream_iterator<std::string>(std::cout, " "));

	//in_file.close();
	//return 0;

	//*******************************************************************//
	//*******************************************************************//


	//************Läser in med kopy****************************//


	//std::vector<std::string> vec;
	//
	//std::ifstream in_file{ "C://Users//elidj//Cplus2//Labbar//Lab3//Code3//Code3//uppgift2//uppgift2_kort.txt" };

	////kollar att filen är ok
	//if (!in_file) {
	//	std::cout << "Could not open input file!!\n";
	//	return 1;
	//}
	//else {
	//	std::cout << "Open!!\n";
	//}

	////LÄser in en fil och kopierar över till en vector
	//std::copy(std::istream_iterator<std::string>(in_file), std::istream_iterator<std::string>(),
	//std::back_inserter(vec));

	//std::copy(vec.begin(), vec.end(), std::ostream_iterator<std::string>(std::cout, " "));


	////hash map
	////sorterar om orden i bokstavsordning


	////Läser in filen till en iterator
	////std::istream_iterator<std::string> first(in_file);
	////std::istream_iterator<std::string> last;
	//
	////skriver ut iteratorn till consolen
	////std::copy(first, last, std::ostream_iterator<std::string>(std::cout, " "));

	//in_file.close();
	//return 0;




	//*******************************************************************//


	//Detta är ett lambdaexpression
	//[]skickar in allt man vill fånga
	//() är som en konstructor
	//{}är allt vi vill göra som en loop ish
	//std::for_each(table.begin(), table.end(),
	//	[&](std::pair<const std::string, int>& a)
	//{
	//	vec.push_back(std::make_pair(a.first, a.second));
	//	uniqueValues++;
	//});

	//*******************************************************************//






	//Göra ett nytt enklare namn istället för std::map<std::string, std::set<std::string>> 
	using My_table = std::map<std::string, std::set<std::string>>;

	//skapar en map av string samt set av string, std::map<std::string, std::set<std::string>> 
	auto table = My_table{};

	//struct
	struct insertMap {
	public:
		//constructor
		//måste ha för att komma åt vår tabel utanför, använder &referens för att ändra
		insertMap(My_table &x) : T{ x } {}

		void operator() (std::string a) {

			//temp is sorted words/subject
			std::string temp{ a };
			std::sort(temp.begin(), temp.end());

			//Number of words read
			howMany++;

			//T.count(temp) kollar om map (a.first) är tom, i så fall skapas ett nytt sett
			//map tar bara in unika ord samt sorterar i bokstavsordning
			if (T.count(temp) == 0) {
				T[temp] = std::set<std::string>{ a };
			}
			else {
				//om det redan finns något i map så insertar man en extra i set. a är det riktiga ordet, temp är subjectet
				T[temp].insert(a);
			}
		}

		//måste vara public annars kan vi ej nå den
		int howMany = 0;

	private:
		My_table &T;
	};

	//std::ifstream in_file{ "X://TNG033//Labbar//Lab3NY//Code3//Code3//uppgift2//uppgift2.txt" };
	std::ifstream in_file{ "X://TNG033//Labbar//Lab3NY//Code3//Code3//uppgift2//uppgift2_kort.txt" };

	//kollar att filen är ok
	if (!in_file) {
		std::cout << "Could not open input file!!\n";
		return 1;
	}
	else {
		std::cout << "Open!!\n";
	}

	// Läser in filen med en iterator
	// std::istream_iterator<std::string> first(in_file); jobbar på en stream
	// jobbar på in_file (som är en stream)
	// varje gång man anropar next, får nästa ord

	std::istream_iterator<std::string> first(in_file);
	std::istream_iterator<std::string> last;

	//detta funkar ej eftersom då är iteratorerna redan använda på något sätt
	//int counter = distance(first, last);

	//denna läser in en fil
	//Den returnerar antalet instanser
	auto instanceOfInsertMap = std::for_each(first, last, insertMap{ table });
	
	//kallar på vår howMany från structen så att vi kommer åt antalet
	auto counter = instanceOfInsertMap.howMany;

	std::cout << "Numbers of words = " << counter << "\n\n";	std::cout << "--- ANAGRAMS --- " << "\n";

	std::for_each(table.begin(), table.end(),
		[](auto& a) {

		//sizen av set
		if (a.second.size() > 1) {
			//secound.begin() är början av setten
			std::for_each(a.second.begin(), a.second.end(),
				[](auto& b) {

				//skriver ut hela settet
				std::cout << b << " ";

			});
			//Antal ord i sett/antal anagram
			std::cout << "-> " << a.second.size() << " words" << "\n";
		}
	});



	in_file.close();
	return 0;

}