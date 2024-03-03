#pragma once
#include "EntityType.h"
#include "SimulationGrid.h"

class Entity
{
public:

	Entity();
	Entity(int r, int c);

	virtual int get_row();
    virtual int get_col();

    virtual void set_row(int r);
    virtual void set_col(int c);


	virtual std::string toString() const = 0;

	virtual EntityType what() = 0;

	virtual Entity* next(const SimulationGrid& g) = 0;

	void demographics(unsigned int population[], const SimulationGrid& g);

protected:
	 int row;
	 int col;
	
};


//--------------- SUBCLASSES ---------------//

class Empty : public Entity 
{
public:

	Empty();
	Empty(int row, int col);

	EntityType what() override;

	std::string toString() const override;

	Entity* next(const SimulationGrid& g) override;

	friend std::ostream& operator<<(std::ostream& os, const Entity& obj);
};

class Plant : public Entity 
{
public:

	Plant();
	Plant(int row, int col);

	EntityType what() override;

	std::string toString() const override;

	Entity* next(const SimulationGrid& g) override;

	friend std::ostream& operator<<(std::ostream& os, const Plant& plant);
};


class Animal : public Entity 
{
protected:
	int age;

public:

	int get_age() const;
	void set_age(int a);

};

class Fox : public Animal
{
public:

	Fox();
	Fox(int row, int col);

	EntityType what() override;

	std::string toString() const override;

	Entity* next(const SimulationGrid& g) override;

	friend std::ostream& operator<<(std::ostream& os, const Fox& fox);
};

class Gopher : public Animal
{
protected:
	int age;

public:

	Gopher();
	Gopher(int row, int col, int age);

	EntityType what() override;

	std::string toString() const override;

	Entity* next(const SimulationGrid& g) override;

	friend std::ostream& operator<<(std::ostream& os, const Gopher& gopher);
};