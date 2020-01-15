/****************************************************************************
 * This file is part of the "Introduction to programming" course. FMI 2019/20
 *****************************************************************************/

 /**
  * @file   yoda_talks.cpp
  * @author Ivan Filipov
  * @author Kristian Krastev
  * @author Vasilena Peycheva
  * @date   01.2020
  * @brief  Solution for advanced_string tasks from practice 10.
  */

#include <iostream>
#include <string.h> // strtok, strlen, strcpy
#include <time.h> 	// time
#include <stdlib.h> // rand

const unsigned int MAX_INPUT = 1024;

// how many spaces are out there + 1
size_t how_many_words(const char* str) {

	if (str == nullptr)
		return 0;

	size_t cnt = 1, i = 0; // at least one word

	while (str[i] != '\0') {

		if (str[i] == ' ')
			cnt++;

		i++;
	}

	return cnt;
}

void free_words(char**& words, size_t size) {

	for (size_t i = 0; i < size; i++)
		delete[] words[i];

	delete words;

	words = nullptr;
}

void yoda_talks(char** words, size_t size) {

	// here we will check the taken words
	bool* is_taken_word = new (std::nothrow) bool[size];

	if (is_taken_word == nullptr)
		return;

	// mark all as untaken
	for (size_t i = 0; i < size; i++)
		is_taken_word[i] = false;

	size_t num_taken = 0;
	size_t index;

	// while there is untaken word
	while (num_taken < size) {

		index = rand() % size; // trying to take this word

		while (is_taken_word[index])
			index = (index + 1) % size; // try the next one, if outsize array, start from the beg

		// mark it as taken
		is_taken_word[index] = true;
		num_taken++;

		// print it
		std::cout << words[index];

		if(num_taken != size) // no space after the last word
			std::cout << ' ';
	}

	delete[] is_taken_word;
}

int main() {

	char buff[MAX_INPUT];

	std::cin.getline(buff, MAX_INPUT);

	size_t words_cnt = how_many_words(buff);

	// allocating pointer for each string ( word )
	char** words = new char*[words_cnt];

	// taking the first word from the buff
	char* word = strtok(buff, " ");

	int i = 0;
	while (word != nullptr) {

		// allocating memory for the current word
		words[i] = new (std::nothrow) char[strlen(word) + 1];

		if (words[i] == nullptr) {

			std::cerr << "can't allocate memory :( !\n";
			free_words(words, i - 1);
			return -1;
		}

		// copying its content
		strcpy(words[i], word);

		i++;

		// taking the next word
		word = strtok(nullptr, " ");
	}

	// makes us sure that all the memory is successfully allocated and copied
	// for (int j = 0; j < i; j++)
	// std::cout << words[j] << std::endl;

	srand(time(nullptr));

	yoda_talks(words, words_cnt);

	free_words(words, words_cnt);

	return 0;
}