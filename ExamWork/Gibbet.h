#ifndef GIBBET_H
#define GIBBET_H
#include <vector>
#include <iostream>
#include <string>
#include <chrono> //бібліотека з інструментами для роботи з часом (потрібна для створення точок у часі) 

class Gibbet
{
	void createWordlist(); //створює текстовий файл зі словами (завжди однакові) 

	std::vector<std::string> m_wordList; //Список слів які можуть випадати гравцю) 

	std::vector<char> m_player_letters; //літери, які вводив гравець протягом гри (раунду) 

	std::chrono::time_point<std::chrono::high_resolution_clock> startTime; //Точка часу початку гри 



public:
	std::string getRandomWord(); //Бере випадкове слово з текстового файлу

	std::string currentWord; //слово, яке вгадує гравець наразі

	void start_resetGame();  //починає та ресетає гру після закінчення 

	void makeAttempt(char letter); //робить спробу

	const std::vector<char>& getGuessedLetters() const; //повертає вєктор з літерами гравця

	void printStats(double duration, bool& isCorrect, size_t& attempts) const; //виводить у консоль статистику

	void printGibbet(size_t incorrectAttempts); //виводить у консоль шибеницю

	Gibbet() //конструктор класу (на початку програми створює файл та логіку випадкових чисел) 
	{
		createWordlist();
		srand(time(NULL));
	}

	~Gibbet() {} //деструктор

};

#endif

