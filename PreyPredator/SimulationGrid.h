#pragma once
#define MAX_ROWS 100
#define MAX_COLS 100

#include <string>
#include <vector>

// forward class declaration for Entity
class Entity;


class SimulationGrid
{
	friend class Entity;

public:

	SimulationGrid();
	SimulationGrid(int r, int c);
	SimulationGrid(std::string path);
	SimulationGrid(const SimulationGrid& other);

	~SimulationGrid();

	int get_rows();
	int get_cols();

	Entity* get_entity(int row, int col);
	Entity* createEntity(std::string s) const;

	void randomize();

	void set_entity(int row, int col, Entity* entity);

	friend std::ostream& operator<<(std::ostream& os, const SimulationGrid& obj);
	friend std::istream& operator>>(std::istream& is, SimulationGrid& obj);

	SimulationGrid& operator=(const SimulationGrid& other);

private:
	int rows;
	int cols;
	std::vector<Entity*> m_entities; //vector of entities
	Entity* grid[MAX_ROWS][MAX_COLS]; //entity pointer to the grid
};

class Simulation 
{
private:
    int rows;
    int cols;
    int numCycles;
    SimulationGrid even;
    SimulationGrid odd;

    void promptForGrid(SimulationGrid& g);
    

public:

    Simulation();

	void run();

};