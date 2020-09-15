#include <iostream>
#include <string>
#include <map>
#include <vector>

//maps contenant les listes d'axiomes positifs et négatifs
std::map<int, std::vector<char> > positiveLists;
std::map<int, std::vector<char> > negativeLists;

int clausesCounter = 1;

void FillTheLists(std::string clauses)
{
	for (int i = 0; i < (int)clauses.size(); i++)
	{
		if (int(clauses[i]) == 44) //code ascii de la virgule
		{
			clausesCounter++;
		}

		if (int(clauses[i]) > 64 && int(clauses[i]) < 91) //code ascii des lettres de l'alphabet majuscules
		{
			if (i != 0 && int(clauses[i - 1]) == 110) //code ascii de la négation
			{
				bool compare = true;
				for (int j = 0; j < (int)negativeLists[clausesCounter - 1].size(); j++)
				{
					if (negativeLists[clausesCounter - 1][j] == clauses[i])
					{
						compare = false;
						break;
					}
				}
				if (compare)
					negativeLists[clausesCounter - 1].push_back(clauses[i]);
			}
			else
			{
				bool compare = true;
				for (int j = 0; j < (int)positiveLists[clausesCounter - 1].size(); j++)
				{
					if (positiveLists[clausesCounter - 1][j] == clauses[i])
					{
						compare = false;
						break;
					}
				}
				if (compare)
					positiveLists[clausesCounter - 1].push_back(clauses[i]);
			}
		}
	}
}

void FindProof()
{
	// On vérifie si les listes sont vides
	int empty = 0;
	for (int i = 0; i < clausesCounter; i++)
	{
		if (positiveLists[i].size() == 0 && negativeLists[i].size() == 0)
		{
			empty++;
		}
	}
	if (empty == clausesCounter)
	{
		std::cout << "Preuve contradictoire trouvée" << std::endl;
		return;
	}

	// On cherche deux clauses à simplifier et après simplification on relance le "FindProof"
	for (int i = 0; i < clausesCounter; i++)
	{
		for (int j = 0; j < clausesCounter; j++)
		{
			if (i != j && positiveLists[i].size() == 1 && negativeLists[i].size() == 0)
			{
				for (int k = 0; k < (int)negativeLists[j].size(); k++)
				{
					if (positiveLists[i][0] == negativeLists[j][k])
					{
						//std::cout << positiveLists[i][0] << std::endl;
						positiveLists[i].pop_back();
						std::vector<char> change;
						int size = negativeLists[j].size();
						for (int m = 0; m < size; m++)
						{
							if (m != k)
							{
								change.push_back(negativeLists[j][m]);
							}
						}
						for (int n = 0; n < size; n++)
						{
							negativeLists[j].pop_back();
						}
						for (int p = 0; p < (int)change.size(); p++)
						{
							negativeLists[j].push_back(change[p]);
						}
						FindProof();
					}
				}
			}
			if (i != j && negativeLists[i].size() == 1 && positiveLists[i].size() == 0)
			{
				for (int k = 0; k < (int)positiveLists[j].size(); k++)
				{
					if (negativeLists[i][0] == positiveLists[j][k])
					{
						//std::cout << negativeLists[i][0] << std::endl;
						negativeLists[i].pop_back();
						std::vector<char> change;
						int size = positiveLists[j].size();
						for (int m = 0; m < size; m++)
						{
							if (m != k)
							{
								change.push_back(positiveLists[j][m]);
							}
						}
						for (int n = 0; n < size; n++)
						{
							positiveLists[j].pop_back();
						}
						for (int p = 0; p < (int)change.size(); p++)
						{
							positiveLists[j].push_back(change[p]);
						}
						FindProof();
					}
				}
			}
		}
	}
	std::cout << "Pas de preuve trouvée" << std::endl;
}

int main()
{
	std::string ensembleClauses;
	std::cin >> ensembleClauses;
	FillTheLists(ensembleClauses);
	FindProof();
	return 0;
}