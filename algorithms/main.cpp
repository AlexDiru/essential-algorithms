#include <iostream>
#include <vector>
#include <algorithm>

//Divide and Conquer algorithms
class DC
{
public:

	//Find the max and minimum values of a list
	static void MaxMin(const std::vector<int> &list)
	{
		int fmin, fmax;
		_MaxMin(list, 0, list.size()-1, fmin, fmax);
		std::cout << "(" << fmin << " , " << fmax << ")" << std::endl;
	}
	
	//Find the max and minimum values of a list
	static void MaxMin(const std::vector<int> &list, int& fmin, int &fmax)
	{
		_MaxMin(list, 0, list.size()-1, fmin, fmax);
	}

	//Paritions a list
	static void Partition(std::vector<int> &list)
	{
		_Partition(list, 0, list.size());
	}

	//Finds the positionth smallest element in the list
	static int Selection(std::vector<int> list, int position)
	{
		int first = 0;
		int last = list.size();
		int j;

		while (true)
		{
			j = _Partition(list, first, last);
			
			//Return positionth smallest
			if (position == j)
				break;

			if (position < j)
				//Search left sublist
				last = j - 1;
			else
				//Search right sublist
				first = j + 1;
		}

		return list[j];
	}

	//Sorts pairs by left value then right value
	//Currently uses bubblesort
	static void LexicographicSort(std::vector<std::pair<int,int>> &list)
	{
		//Sort left value
		for (int i = 0; i < list.size() - 1; i++)
		{
			for (int j = i + 1; j < list.size(); j++)
			{
				if (list[i].first > list[j].first)
					std::swap(list[i], list[j]);
			}
		}

		//Group by left values
		std::vector<std::vector<std::pair<int,int>*>> grouping;
		int currentValue = list[0].first;
		int currentGroup = 0;
		grouping.push_back(std::vector<std::pair<int,int>*>());

		for (int i = 0; i < list.size(); i++)
		{
			if (list[i].first != currentValue)
			{
				currentGroup++;
				//Allocate room for the new group
				grouping.push_back(std::vector<std::pair<int,int>*>());
				currentValue = list[i].first;
			}

			grouping[currentGroup].push_back(&list[i]);
		}

		//Clear out the original list ready for the new order
		list.clear();

		//Sort each group by right values
		for (int g = 0; g < grouping.size(); g++)
		{
			//Sort by right values
			for (int i = 0; i < grouping[g].size() - 1; i++)
			{
				for (int j = i + 1; j < grouping[g].size(); j++)
				{
					if (grouping[g][i]->second > grouping[g][j]->second)
						std::swap(*grouping[g][i], *grouping[g][j]);
				}
			}

			//Add the new order into the list
			for (int i = 0; i < grouping[g].size(); i++)
			{
				list.push_back(*grouping[g][i]);
			}
		}
	}

private:
	static void _MaxMin(const std::vector<int>& list, int i, int j, int& fmin, int& fmax)
	{
		//List has one element
		if (i == j)
		{
			fmax = list[i];
			fmin = list[i];
		}
		else
		{
			//List has two elements
			if (i == j - 1)
			{
				fmax = list[i];
				fmin = list[j];
				
				//Make a swap
				if (list[j] > list[i])
					std::swap(fmax, fmin);
			}
			else
			{
				//Get the middle of the list
				int mid = (i + j) >> 1;

				int gmin, gmax;
				int hmin, hmax;

				//Solve the subproblems
				DC::_MaxMin(list, i, mid, gmin, gmax);
				DC::_MaxMin(list, mid, j, hmin, hmax);

				//Get the final max and min values
				fmax = gmax > hmax ? gmax : hmax;
				fmin = gmin < hmin ? gmin : hmin;
			}
		}
	}

	static int _Partition(std::vector<int>& list, int first, int last)
	{
		int v = list[first];
		int i = first;
		int j = last;

		//Only one element in the list
		if (i == j)
			return j;

		do
		{
			do ++i; while (list[i] < v);
			do --j; while (list[j] > v);

			if (i < j)
				std::swap(list[i], list[j]);
		} while (i < j);

		list[first] = list[j];
		list[j] = v;
		return j;
	}
};

void OutputVector(const std::vector<int> &list)
{
	for (int i = 0; i < list.size(); i++)
		std::cout << list[i] << " | ";
	std::cout << std::endl;
}

void OutputVector(const std::vector<std::pair<int,int>> &list)
{
	for (int i = 0; i < list.size(); i++)
		std::cout << "(" << list[i].first << ", " << list[i].second << ")";
	std::cout << std::endl;
}

int main()
{
	std::vector<int> *a = new std::vector<int>();
	a->push_back(5);
	a->push_back(1);
	a->push_back(4);
	a->push_back(7);
	a->push_back(10);
	a->push_back(6);

	std::cout << DC::Selection(*a, 3) << std::endl;

	std::vector<std::pair<int,int>> b;
	b.push_back(std::pair<int,int>(1,5));
	b.push_back(std::pair<int,int>(1,9));
	b.push_back(std::pair<int,int>(1,0));
	b.push_back(std::pair<int,int>(1,6));
	b.push_back(std::pair<int,int>(11,3));
	b.push_back(std::pair<int,int>(2,2));
	b.push_back(std::pair<int,int>(2,1));
	b.push_back(std::pair<int,int>(2,7));
	b.push_back(std::pair<int,int>(2,5));
	
	DC::LexicographicSort(b);

	OutputVector(b);

	system("PAUSE");
	return 0;
}