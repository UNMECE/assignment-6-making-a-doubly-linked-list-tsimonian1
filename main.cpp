#include <iostream>
#include <cmath>
#include <vector>
#include <new>
#include <string>
#include <memory>
#include <iomanip>
#include "coordinate.h"
using namespace std;

void add_coordinate(Coordinate *list_end, float x, float y)	{

	Coordinate *new_coordinate = new Coordinate;
	new_coordinate->x = x;
	new_coordinate->y = y;
	new_coordinate->coord_id = list_end->coord_id + 1;
	new_coordinate->next = NULL;
	new_coordinate->previous = list_end;
	list_end->next = new_coordinate;

}

void forward_display(Coordinate *list_beginning)	{
	Coordinate *current = list_beginning;
	cout << "Coord ID" << setw(8) << "X" << setw(8) << "Y" << "\n";
	while(current != nullptr)	{
		cout << current->coord_id << setw(12) << current->x << setw(12) << current->y << "\n";
		current = current->next;
	}
}

void backward_display(Coordinate *&list_end)	{
	Coordinate *current = list_end;
	cout << "Coord ID" << setw(8) << "X" << setw(8) << "Y" << "\n";
	while (current != nullptr) {
		cout << current->coord_id << setw(12) << current->x << setw(12) << current->y << "\n";
		current = current->previous;
	}
}

void delete_coordinate(Coordinate *&list_beginning, Coordinate *&list_end, int coord_id_to_delete)	{
	Coordinate *current = list_beginning;
	while(current != nullptr)	{
        if(current->coord_id == coord_id_to_delete)     {
                if(current->previous == nullptr)        {
                        list_beginning = current->next;
                        list_beginning->previous = nullptr;
                        for(int id=coord_id_to_delete; id<list_end->coord_id;id++) {
                                current->coord_id = id;
                                current = current->next;
                        }
			delete current;
                }
                if(current->next == nullptr)    {
                        list_end = current->previous;
                        list_end->next = nullptr;
                        list_end->coord_id -= 1;
			delete current;
                }
                else
                	current->next->previous = current->previous;
                	current->previous->next = current->next;
			for(int id = coord_id_to_delete-1; id<list_end->coord_id; id++)	{
				current->coord_id = id;
				current = current->next;
			}
			return;
		}
        current = current->next;
	}
	cout << "Coordinate not found!\n";
	delete current;
}
	

int list_length(Coordinate *list_beginning)	{
	int count = 0;
	while (list_beginning != nullptr) {
		count++;
		list_beginning = list_beginning->next;
	}
	return count;
}

void closest_to(Coordinate *list_beginning, float x, float y)	{
	Coordinate *closest_to = list_beginning;
	Coordinate *ptr = list_beginning;
	double min_dist, dist = 0;
	min_dist = sqrt(pow(list_beginning->x - x, 2) + pow(list_beginning->y - y,2));
	while(ptr != nullptr)	{
		dist = sqrt(pow(ptr->x - x,2) + pow(ptr->y - y,2));
		if (dist <=  min_dist) {
			min_dist = dist;
			closest_to = ptr;
		}
		ptr = ptr->next;
	}
	cout << "The closest point is:\n";
	cout << "Coord ID:" << closest_to->coord_id << setw(10) << "X:" << closest_to->x << setw(10) <<  "Y:" << closest_to->y << "\n\n";
	cout << "Minimum distance between points is:" << min_dist << "\n";
}

int main(int argc, char* argv[]) {
	int input = stoi(argv[1]);
	Coordinate *list_start = new Coordinate;
	Coordinate *list_end = list_start;
	list_start->x = (rand() % 100+1);
	list_start->y = (rand() % 100+1);
	list_start->coord_id = 1;
	list_start->next = nullptr;
	list_start->previous = nullptr;
	list_start = list_end;
	for (int i = 1; i < input; i++) {
		add_coordinate(list_end, (rand() % 100+1), (rand() % 100+1));
		list_end = list_end->next;
	}
	cout << "Display of the list (forward):\n";
	forward_display(list_start);
	cout << "\n";
	cout << "Display of the list (backwards):\n";
	backward_display(list_end);
	cout << "\n";
	
	cout << "Length of the linked list is:" << list_length(list_start) << "\n\n";

	delete_coordinate(list_start, list_end, 7);

	cout << "Display the list with coordinate 7 now being deleted:\n";
	forward_display(list_start);
	cout << "\n";

	cout << "Length of the linked list is:" << list_length(list_start) << "\n\n";

	cout << "Find the coordinate with the closest distance to: x=32 and y=21:\n";
	closest_to(list_start, 32, 21);

	return 0;
}
