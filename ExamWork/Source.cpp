#include <iostream>
#include "Gibbet.h"
#include <string>

int main()
{

	Gibbet game; //створюється об'єкт гри для взаємодії з її функціями

	while (true) //Зовнішній клас (запускає гру та оновлює її після закінчення раунду) 
	{
		try
		{
			game.start_resetGame(); //запускаємо гру (задаємо початкові значення) 
			std::cout << "Game started" << std::endl;

			std::string hidden_word = game.currentWord; //створюємо приховане слово та надаємо йому значення слова з файлу
			
			if (hidden_word.empty())
				throw std::runtime_error("Error while getting word"); //перевірка на порожність цього слова

			std::string guessedWord(hidden_word.length(), '_'); //створюємо слово, яке буде бачити гравець на екрані
			
			//Виводимо першу та останню літеру слова
			guessedWord[0] = hidden_word[0]; 
			guessedWord[hidden_word.length() - 1] = hidden_word[hidden_word.length() - 1]; 


			char letter; //літера, яку вводить гравець 
			bool isCorrect = false; //перевірка на перемогу (ПЕРЕМОГА БУДЕ) 
			size_t remainingAttempts = 6, attempts = 0;	 //Дві змінні для спроб. Перша для підрахунку загальних, інша для програшу
			auto startTime = std::chrono::high_resolution_clock::now(); //створюємо точку часу, коли почалася гра

			//цикл буде тривати доки залишились спроби дл програшу чи коли не буде оголошена перемога
			while (remainingAttempts > 0 && !isCorrect) 
			{
				try
				{
					system("cls"); 

					game.printGibbet(6 - remainingAttempts); //вивід на екран шибениці (в залежності від залишившихся спроб) 
					
					//Блок запросу літери в гравця
					std::cout << "Current word: " << guessedWord << std::endl; 
					std::cout << "Enter letter (Enter '0' to quit): "; 
					std::cin >> letter; 
					
					if (letter == '0') //вихід з програми
					{
						// R - рядковий літерал, який дозволяє зберігати таке ж саме положення тексту, як у коді 
						// (пробіли, переноси й інше) 
						system("cls"); 
						std::cout << R"(			
						BBBB  Y   Y EEEEE
						B   B  Y Y  E    
						BBBB    Y   EEEE 
						B   B   Y   E    
						BBBB    Y   EEEEE
						)" << std::endl;
						exit(0);
					}

					++attempts; //збільшуємо змінну загальних спроб

					if (!((letter >= 'a' && letter <= 'z') || (letter >= 'A' && letter <= 'Z'))) //перевірка чи літеру ввів гравець
					{
						std::cout << ("Your input is not letter!") << std::endl; 
						system("pause"); 
						continue; 
					}
						
					letter = tolower(letter); //на випадок, якщо гравець введе велику літеру

					if (std::find(game.getGuessedLetters().begin(), game.getGuessedLetters().end(), letter) != game.getGuessedLetters().end())
					{
						std::cout << "You have already entered that letter! Enter another!" << std::endl; 
						system("pause"); 
						continue; 
					}

					game.makeAttempt(letter); //робимо спробу (додаємо літеру у массив з літерами та перевіряємо на повторення) 

					bool found = false; 

					for (size_t i = 0; i < hidden_word.length(); ++i) //перевіряємо чи є в прихованому слові ця літера
					{
						if (hidden_word[i] == letter)
						{
							guessedWord[i] = letter; 
							found = true; 
						}
					}

					if (!found) //якщо літери нема то зменшуємо кількість залишившихся неправильних спроб (перемальовуємо шибеницю) 
					{
						--remainingAttempts;
					}

					if (guessedWord == hidden_word) //перевірка на перемогу
					{
						isCorrect = true; //зміна змінної для завершення внутрішнього циклу й перезапуску гри
						auto endTime = std::chrono::high_resolution_clock::now(); //створення точки часу (вона показує кінець таймеру)  
						std::chrono::duration<double> duration = endTime - startTime; // створення змінної тривалості (шаблонний клас duration)

						game.printStats(duration.count(), isCorrect, attempts);  //виклик функції виводу статистики гри (час, кількість спроб)
					}
				}
				catch (const std::exception& e) //обробка вийнятку
				{
					std::cerr << "Error: " << e.what() << std::endl; 
				}
			}
			if (remainingAttempts == 0 && !isCorrect) //перевірка на програш (перемоги не буде) 
			{
				system("cls");
				isCorrect = false; //на провсяк випадок змінюємо щоб не було помилок
				auto endTime = std::chrono::high_resolution_clock::now(); //створюємо кінцеву точку часу для підрахунку
				std::chrono::duration<double> duration = endTime - startTime;  //рахуємо проміжок

				game.printGibbet(6); //вивід у консоль шибениці (от подивись шо з людиною сталося через тебе!) 
				game.printStats(duration.count(), isCorrect, attempts); //вивід статистики за гру
			}
		}
		catch (std::exception& e) //обробка вийнятків 
		{
			std::cerr << "Error " << e.what() << std::endl; 
		}

	}
	return 0; 
}	