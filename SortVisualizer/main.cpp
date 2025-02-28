#include <SDL3/SDL.h>
#include <iostream>
#include <random>
#include <ranges>
#include <algorithm>
// Visualize the state
// getting the vector to know the state every time the loop update,
// passing renderer for visualization, 
// red and blue are for coloring the element sorted
void draw_state(std::vector<int>& v, SDL_Renderer* renderer, unsigned int red, unsigned int blue) 
{
	unsigned int index = 0;
	for (int i : v)
	{
		if (index == red)
		{
			SDL_SetRenderDrawColorFloat(renderer, 255, 0, 0, 255);
		}
		else if (index == blue)
		{
			SDL_SetRenderDrawColorFloat(renderer, 0, 0, 255, 255);

		}
		else
		{
			SDL_SetRenderDrawColorFloat(renderer, 255, 255, 255, 255);

		}
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderLine(renderer, (float)index, (float)99, (float)index, i);
		index += 1;
	}
}
int main()
{
	// Generate a random number from 1 to 99, vizualing  1 to 99 pixels on the screen
	std::random_device rd;
	std::uniform_int_distribution<> d(1,99);
	// populate the vector with random numbers
	std::vector<int> v;
	for (int i = 0; i < 100; i++)
	{
		v.push_back(d(rd));
	}

	// Create Window Renderer
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_CreateWindowAndRenderer("Main Window", 100*10,100*10, 0, &window, &renderer);
	SDL_SetRenderScale(renderer, 10, 10);
	

	// Sorting algorithm
	for (unsigned int i = 0; i < v.size(); i++)
	{
		for (unsigned int j = i; j < v.size(); j++)
		{
			// check if the element at position j is greater than position i, if true swap them.
			if (v[j] < v[i])
			{
				std::swap(v[j], v[i]);
			}
			// Clear the screen
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderClear(renderer);
			// Draw the state of the sort
			draw_state(v, renderer, i, j);


			// Show to the window
			SDL_RenderPresent(renderer);
			SDL_Delay(10); // 10 ms delay
		}
	}

	for (int i : v)
	{
		std::cout << i << " ";
	}
	if (std::ranges::is_sorted(v))
	{
		std::cout << "\nsorted\n";
	}
}