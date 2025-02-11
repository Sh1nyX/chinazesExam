#include "Gibbet.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <ctime> //�������� ��� ��������� ���������� �������

void Gibbet::createWordlist() //������� ������� ������ ��� ��� ��� � ���� �� � ����
{
	try
	{
		//��������� ����� ��� ���������� ������ ���� ����� � ����
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

		std::ofstream outputFile("wordlist.txt"); //��������� ����
		if (!outputFile.is_open()) //�������� �� �������� ����, ���� �, �� �������� �������
			throw std::runtime_error("error while opening file"); 
		for (const auto& word : words) //��������� �� ��� ��������� ������ � �������
		{
			outputFile << word << std::endl; //����� ��� � ����
		}

		outputFile.close(); //��������� ���� 
	}
	catch (const std::runtime_error& e) //������� ��������
	{
		std::cerr << "Error occured: " << e.what() << std::endl;
	}
}

std::string Gibbet::getRandomWord() //������� ���� ��������� ����� � ����� ��� ��� 
{
	try
	{
		std::ifstream inputFile("wordlist.txt"); //��������� ����� ��� ���������� � �����

		if (!inputFile.is_open()) //�������� �� �������� ����
			throw std::runtime_error("Error while reading input file");

		m_wordList.clear(); //������� ������ ��� �������� �������
		std::string word; //����� ��� ���������� ������������� �����

		while (inputFile >> word) //������� �� ����� � �����
		{
			m_wordList.push_back(word);
		}

		if (m_wordList.empty()) //�������� �� ��������� ��������� ����� (�� ��������� ������) 
			throw std::runtime_error("WordList is empty");

		size_t randIndex = rand() % m_wordList.size(); //��������� ���������� ������
		return m_wordList[randIndex]; //��������� ��������� ����� � ������ 
	}
	catch (const std::runtime_error& e) //������� �������� 
	{
		std::cerr << "Error during file operations: " << e.what() << "Returning NULL" << std::endl;
	}
	return "NULL"; 
}

void Gibbet::start_resetGame() //������� ������� ��� �� ������ �������� ���� �� ���������� 
{
	currentWord = getRandomWord(); //���������� �������� ����������� ����� ��� ��������� �������� �������� ���
	system("cls"); 
	m_playerLetters.clear();  //������� ������ � �������, �� ������ �������
	startTime = std::chrono::high_resolution_clock::now(); //��������� ����� ���� ������� ���
}

void Gibbet::makeAttempt(char letter) //������� ��� ��������� ������ (���� ����� � ����� � ������� �� �������� �� ����������)
{
	try
	{
		for (char guessed_letter : m_playerLetters) //��������� �� ������ ����, �� ������ �������
		{
			if (guessed_letter == letter) //���� ���� ����� ��� �, �������� ��������
				throw std::invalid_argument("You already guessed that letter!");
		}
		m_playerLetters.push_back(letter); //���� ��� ������, �� ������ ����� � ������
	}
	catch (const std::invalid_argument& e) //������� ��������
	{
		std::cerr << "Error: " << e.what() << std::endl;
	}
}

const std::vector<char>& Gibbet::getGuessedLetters() const //������� ����� � �������, �� ��� �������
{
	return m_playerLetters; 
}

void Gibbet::printStats(double duration, bool& isCorrect, size_t& attempts) const //�������� � ������� ���������� ������ �� ���
{ 
	if (!isCorrect) //�������� ������ ������� �� �������
	{
		std::cout << "You lost!\n"; //�������� �� ����
	}
	else
		std::cout << "You won!\n"; //�������� ����

	std::cout << "Guessed word: " << currentWord; //�����, ��� ������� ���� �������
	std::cout << "\nNumber of attempts: " << attempts; //������� �����
	std::cout << "\nGame duration: " << duration << " seconds"; //���, ���������� �� ��, ��� �������
	std::cout << "\nGuessed letters: "; //������ ����, �� ��� ������� (�������� �� ����������) 
	for (char c : m_playerLetters) //�������� �� �����
	{
		std::cout << c << " "; 
	}
	std::cout << std::endl; 
	system("pause"); 
}

void Gibbet::printGibbet(size_t incorrectAttempts) //��������� ���� �������� (� ��������� �� ������������ ����� ������)
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




