#include <iostream>
#include <cstring>

using namespace std;

class Herbivore {
protected:
	int weight;
	bool life;
public:
	Herbivore(int weight_w) : weight(weight_w), life(true) {}
	~Herbivore() {}
	virtual void Eat_grass() {
		if (life == true) {
			weight += 10;
		}
	}
	bool Life() {
		return life;
	}
	int Weight() {
		return weight;
	}
	void die() {
		life = false;
	}
};

class Carnivore {
protected:
	int power;
public:
	Carnivore(int p) : power(p) {}
	~Carnivore() {}
	int Power() {
		return power;
	}
	virtual void Eat(Herbivore* herbivore) = 0;
};

class Wildebeest : public Herbivore {
public:
	Wildebeest(int w) : Herbivore(w) {}
	void Eat_grass() {
		if (life == true) {
			weight += 10;
			cout << "Wildebeest eats, weight: " << weight << endl;
		}
	}
};

class Bison : public Herbivore {
public:
	Bison(int w) : Herbivore(w) {}
	void Eat_grass() {
		if (life == true) {
			weight += 10;
			cout << "Bison eats, weight: " << weight << endl;
		}
	}
};

class Lion : public Carnivore {
public:
	Lion(int p) : Carnivore(p) {}
	void Eat(Herbivore* herbivore) override {
		if (herbivore->Life()) {
			if (power > herbivore->Weight()) {
				power += 10;
				herbivore->die();
				cout << "Lion eats, power: " << power << endl;
			}
			else {
				power -= 10;
				cout << "Lion fails to eat, power: " << power << endl;
			}
		}
	}
};

class Wolf : public Carnivore {
public:
	Wolf(int p) : Carnivore(p) {}
	void Eat(Herbivore* herbivore) override {
		if (herbivore->Life()) {
			if (power > herbivore->Weight()) {
				power += 10;
				herbivore->die();
				cout << "Wolf eats, power: " << power << endl;
			}
			else {
				power -= 10;
				cout << "Wolf fails to eat, power: " << power << endl;
			}
		}
	}
};

class Continent {
public:
	~Continent() {}
	virtual Herbivore** createHerbivores(int& size) const = 0;
	virtual Carnivore** createCarnivores(int& size) const = 0;
};

class Africa : public Continent {
public:
	Herbivore** createHerbivores(int& size) const override {
		size = 1;
		Herbivore** herbivores = new Herbivore * [size];
		herbivores[0] = new Wildebeest(50);
		return herbivores;
	}

	Carnivore** createCarnivores(int& size) const override {
		size = 1;
		Carnivore** carnivores = new Carnivore * [size];
		carnivores[0] = new Lion(70);
		return carnivores;
	}
};

class North_America : public Continent {
public:
	Herbivore** createHerbivores(int& size) const override {
		size = 1;
		Herbivore** herbivores = new Herbivore * [size];
		herbivores[0] = new Bison(80);
		return herbivores;
	}

	Carnivore** createCarnivores(int& size) const override {
		size = 1;
		Carnivore** carnivores = new Carnivore * [size];
		carnivores[0] = new Wolf(60);
		return carnivores;
	}
};

class AnimalWorld {
	Herbivore** herbivores;
	Carnivore** carnivores;
	int herbivoreSize;
	int carnivoreSize;
public:
	AnimalWorld(const Continent& continent) {
		herbivores = continent.createHerbivores(herbivoreSize);
		carnivores = continent.createCarnivores(carnivoreSize);
	}

	~AnimalWorld() {
		for (int i = 0; i < herbivoreSize; ++i) {
			delete herbivores[i];
		}
		delete[] herbivores;
		for (int i = 0; i < carnivoreSize; ++i) {
			delete carnivores[i];
		}
		delete[] carnivores;
	}

	void mealsHerbivores() {
		for (int i = 0; i < herbivoreSize; ++i) {
			herbivores[i]->Eat_grass();
		}
	}

	void nutritionCarnivores() {
		for (int i = 0; i < carnivoreSize; ++i) {
			for (int j = 0; j < herbivoreSize; ++j) {
				if (herbivores[j]->Life()) {
					carnivores[i]->Eat(herbivores[j]);
				}
			}
		}
	}
};

int main() {
	Africa africa;
	AnimalWorld africanWorld(africa);

	africanWorld.mealsHerbivores();
	africanWorld.nutritionCarnivores();

	North_America northAmerica;
	AnimalWorld northAmericanWorld(northAmerica);

	northAmericanWorld.mealsHerbivores();
	northAmericanWorld.nutritionCarnivores();
}