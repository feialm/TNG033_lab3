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

	//***************Detta funkar med att l�sa in det med iterators********************//

	//std::vector<std::string> vec;
	//
	//std::ifstream in_file{ "C://Users//elidj//Cplus2//Labbar//Lab3//Code3//Code3//uppgift2//uppgift2_kort.txt" };

	////kollar att filen �r ok
	//if (!in_file) {
	//	std::cout << "Could not open input file!!\n";
	//	return 1;
	//}
	//else {
	//	std::cout << "Open!!\n";
	//}

	////L�ser in filen till en iterator
	//std::istream_iterator<std::string> first(in_file);
	//std::istream_iterator<std::string> last;
	//

	////skriver ut iteratorn till consolen
	//std::copy(first, last, std::ostream_iterator<std::string>(std::cout, " "));

	//in_file.close();
	//return 0;

	//*******************************************************************//
	//*******************************************************************//


	//************L�ser in med kopy****************************//


	//std::vector<std::string> vec;
	//
	//std::ifstream in_file{ "C://Users//elidj//Cplus2//Labbar//Lab3//Code3//Code3//uppgift2//uppgift2_kort.txt" };

	////kollar att filen �r ok
	//if (!in_file) {
	//	std::cout << "Could not open input file!!\n";
	//	return 1;
	//}
	//else {
	//	std::cout << "Open!!\n";
	//}

	////L�ser in en fil och kopierar �ver till en vector
	//std::copy(std::istream_iterator<std::string>(in_file), std::istream_iterator<std::string>(),
	//std::back_inserter(vec));

	//std::copy(vec.begin(), vec.end(), std::ostream_iterator<std::string>(std::cout, " "));


	////hash map
	////sorterar om orden i bokstavsordning


	////L�ser in filen till en iterator
	////std::istream_iterator<std::string> first(in_file);
	////std::istream_iterator<std::string> last;
	//
	////skriver ut iteratorn till consolen
	////std::copy(first, last, std::ostream_iterator<std::string>(std::cout, " "));

	//in_file.close();
	//return 0;




	//*******************************************************************//


	//Detta �r ett lambdaexpression
	//[]skickar in allt man vill f�nga
	//() �r som en konstructor
	//{}�r allt vi vill g�ra som en loop ish
	//std::for_each(table.begin(), table.end(),
	//	[&](std::pair<const std::string, int>& a)
	//{
	//	vec.push_back(std::make_pair(a.first, a.second));
	//	uniqueValues++;
	//});

	//*******************************************************************//






	//G�ra ett nytt enklare namn ist�llet f�r std::map<std::string, std::set<std::string>> 
	using My_table = std::map<std::string, std::set<std::string>>;

	//skapar en map av string samt set av string, std::map<std::string, std::set<std::string>> 
	auto table = My_table{};

	//struct
	struct insertMap {
	public:
		//constructor
		//m�ste ha f�r att komma �t v�r tabel utanf�r, anv�nder &referens f�r att �ndra
		insertMap(My_table &x) : T{ x } {}

		void operator() (std::string a) {

			//temp is sorted words/subject
			std::string temp{ a };
			std::sort(temp.begin(), temp.end());

			//Number of words read
			howMany++;

			//T.count(temp) kollar om map (a.first) �r tom, i s� fall skapas ett nytt sett
			//map tar bara in unika ord samt sorterar i bokstavsordning
			if (T.count(temp) == 0) {
				T[temp] = std::set<std::string>{ a };
			}
			else {
				//om det redan finns n�got i map s� insertar man en extra i set. a �r det riktiga ordet, temp �r subjectet
				T[temp].insert(a);
			}
		}

		//m�ste vara public annars kan vi ej n� den
		int howMany = 0;

	private:
		My_table &T;
	};

	//std::ifstream in_file{ "X://TNG033//Labbar//Lab3NY//Code3//Code3//uppgift2//uppgift2.txt" };
	std::ifstream in_file{ "X://TNG033//Labbar//Lab3NY//Code3//Code3//uppgift2//uppgift2_kort.txt" };

	//kollar att filen �r ok
	if (!in_file) {
		std::cout << "Could not open input file!!\n";
		return 1;
	}
	else {
		std::cout << "Open!!\n";
	}

	// L�ser in filen med en iterator
	// std::istream_iterator<std::string> first(in_file); jobbar p� en stream
	// jobbar p� in_file (som �r en stream)
	// varje g�ng man anropar next, f�r n�sta ord

	std::istream_iterator<std::string> first(in_file);
	std::istream_iterator<std::string> last;

	//detta funkar ej eftersom d� �r iteratorerna redan anv�nda p� n�got s�tt
	//int counter = distance(first, last);

	//denna l�ser in en fil
	//Den returnerar antalet instanser
	auto instanceOfInsertMap = std::for_each(first, last, insertMap{ table });
	
	//kallar p� v�r howMany fr�n structen s� att vi kommer �t antalet
	auto counter = instanceOfInsertMap.howMany;

	std::cout << "Numbers of words = " << counter << "\n\n";	std::cout << "--- ANAGRAMS --- " << "\n";

	std::for_each(table.begin(), table.end(),
		[](auto& a) {

		//sizen av set
		if (a.second.size() > 1) {
			//secound.begin() �r b�rjan av setten
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