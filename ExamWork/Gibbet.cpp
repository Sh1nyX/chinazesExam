#include "Gibbet.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <ctime> //бібліотека для створення випадкових значень

void Gibbet::createWordlist() //функція створює список слів для гри й додає їх у файл
{
	try
	{
		//створюємо вєктор для подальшого запису його вмісту у файл
		std::vector<std::string> words = { "apple"
			, "banana"
			, "car"
			, "dog"
			, "elephant"
			, "fish"
			, "guitar"
			, "house"
			, "island"
			, "jacket"
			, "goyda" //easter egg
		};

		std::ofstream outputFile("wordlist.txt"); //створюємо файл
		if (!outputFile.is_open()) //перевірка чи відкрився файл, якщо ні, то викидаємо помилку
			throw std::runtime_error("error while opening file"); 
		for (const auto& word : words) //проходимо по всіх елементах вєктора зі словами
		{
			outputFile << word << std::endl; //запис слів у файл
		}

		outputFile.close(); //закриваємо файл 
	}
	catch (const std::runtime_error& e) //обробка вийнятків
	{
		std::cerr << "Error occured: " << e.what() << std::endl;
	}
}

std::string Gibbet::getRandomWord() //функція бере випадкове слово з файлу для гри 
{
	try
	{
		std::ifstream inputFile("wordlist.txt"); //створюємо змінну для зчитування з файлу

		if (!inputFile.is_open()) //перевірка чи відкрився файл
			throw std::runtime_error("Error while reading input file");

		m_wordList.clear(); //очищуємо список щоб уникнути помилок
		std::string word; //змінна для збереження зчитувального слова

		while (inputFile >> word) //зчитуємо всі слова з файлу
		{
			m_wordList.push_back(word);
		}

		if (m_wordList.empty()) //перевірка чи правильно зчитались слова (на порожність вєктора) 
			throw std::runtime_error("WordList is empty");

		size_t randIndex = rand() % m_wordList.size(); //створюємо випадковий індекс
		return m_wordList[randIndex]; //повертаємо випадкове слово з масиву 
	}
	catch (const std::runtime_error& e) //обробка вийнятків 
	{
		std::cerr << "Error during file operations: " << e.what() << "Returning NULL" << std::endl;
	}
	return "NULL"; 
}

void Gibbet::start_resetGame() //функція запускає гру та анулює значення після її завершення 
{
	currentWord = getRandomWord(); //присвоюємо значення випадкового слова для подальших перевірок протягом гри
	system("cls"); 
	m_playerLetters.clear();  //очищуємо список з літерами, що вводив гравець
	startTime = std::chrono::high_resolution_clock::now(); //створюємо точку часу початку гри
}

void Gibbet::makeAttempt(char letter) //функція для здійснення спроби (додає літеру у вєктор з літерами та перевіряє на повторення)
{
	try
	{
		for (char guessed_letter : m_playerLetters) //проходимо по вєктору літер, що вводив гравець
		{
			if (guessed_letter == letter) //якщо така літера вже є, викидаємо вийняток
				throw std::invalid_argument("You already guessed that letter!");
		}
		m_playerLetters.push_back(letter); //якщо все гаразд, то додаємо літеру у список
	}
	catch (const std::invalid_argument& e) //обробка вийнятків
	{
		std::cerr << "Error: " << e.what() << std::endl;
	}
}

const std::vector<char>& Gibbet::getGuessedLetters() const //повертає вєктор з літерами, що ввів гравець
{
	return m_playerLetters; 
}

void Gibbet::printStats(double duration, bool& isCorrect, size_t& attempts) const //виводить у консоль статистику гравця за гру
{ 
	if (!isCorrect) //перевірка виграв гравець чи програв
	{
		std::cout << "You lost!\n"; //перемоги не буде
	}
	else
		std::cout << "You won!\n"; //перемога буде

	std::cout << "Guessed word: " << currentWord; //слово, яке потрібно було вгадати
	std::cout << "\nNumber of attempts: " << attempts; //кількість спроб
	std::cout << "\nGame duration: " << duration << " seconds"; //час, витрачений на те, щоб вгадати
	std::cout << "\nGuessed letters: "; //список літер, які ввів гравець (правильні та неправильні) 
	for (char c : m_playerLetters) //виводимо ці літери
	{
		std::cout << c << " "; 
	}
	std::cout << std::endl; 
	system("pause"); 
}

void Gibbet::printGibbet(size_t incorrectAttempts) //графічний вивід шибениці (в залежності від залишившихся спроб гравця)
{
	switch (incorrectAttempts)
	{
		case 0:
			printGibbet0(); 
			break;
		case 1:
			printGibbet1();
			break;
		case 2:
			printGibbet2();
			break;
		case 3:
			printGibbet3();
			break;
		case 4:
			printGibbet4();
			break;
		case 5:
			printGibbet5();
			break;
		case 6:
			printGibbet6();
			break;
	}
}

void Gibbet::printGibbet0()
{
	std::cout << "______\n|    |\n|      \n|       \n|       \n|_____\n";
}

void Gibbet::printGibbet1()
{
	std::cout << "______\n|    | \n|    0  \n|       \n|       \n|_____\n";
}

void Gibbet::printGibbet2()
{
	std::cout << "______\n|    | \n|    0  \n|    |   \n|       \n|_____\n";
}

void Gibbet::printGibbet3()
{
	std::cout << "______\n|    |\n|    0\n|   -| \n|       \n|_____\n";
}

void Gibbet::printGibbet4()
{
	std::cout << "______\n|    | \n|    0 \n|   -|- \n|      \n|_____\n";
}

void Gibbet::printGibbet5()
{
	std::cout << "______\n|    |\n|    0 \n|   -|- \n|   |  \n|_____\n";
}

void Gibbet::printGibbet6()
{
	std::cout << "______\n|    | \n|    0 \n|   -|- \n|   | | \n|_____\n";
}




