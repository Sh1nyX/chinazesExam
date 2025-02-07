#ifndef GIBBET_H
#define GIBBET_H
#include <vector>
#include <iostream>
#include <string>
#include <chrono> //�������� � ������������� ��� ������ � ����� (������� ��� ��������� ����� � ���) 

class Gibbet
{
	void createWordlist(); //������� ��������� ���� � ������� (������ �������) 

	std::vector<std::string> m_wordList; //������ ��� �� ������ �������� ������) 

	std::vector<char> m_player_letters; //�����, �� ������ ������� �������� ��� (������) 

	std::chrono::time_point<std::chrono::high_resolution_clock> startTime; //����� ���� ������� ��� 



public:
	std::string getRandomWord(); //���� ��������� ����� � ���������� �����

	std::string currentWord; //�����, ��� ����� ������� �����

	void start_resetGame();  //������ �� ������ ��� ���� ��������� 

	void makeAttempt(char letter); //������ ������

	const std::vector<char>& getGuessedLetters() const; //������� ����� � ������� ������

	void printStats(double duration, bool& isCorrect, size_t& attempts) const; //�������� � ������� ����������

	void printGibbet(size_t incorrectAttempts); //�������� � ������� ��������

	Gibbet() //����������� ����� (�� ������� �������� ������� ���� �� ����� ���������� �����) 
	{
		createWordlist();
		srand(time(NULL));
	}

	~Gibbet() {} //����������

};

#endif

