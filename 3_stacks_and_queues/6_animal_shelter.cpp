#include <iostream>
#include <memory>
#include <queue>
#include <array>
#include <limits>
#include <cassert>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
using namespace std;

/* ============= the Animal abstract class ========== */
class Animal {  
public:

  enum animalType {
    dog = 0,
    cat,

    // ...
    // insert new animal types here
    // ...

    kNumTypes // not a valid animal type! Used to determine the number of animal types
  };


  Animal(string name) : _name(move(name)) {};
  virtual ~Animal() {}; // virtual destructor to allow Animal to be used polymorphically
  virtual animalType get_type() const = 0;
  const string &getName() const { return _name; };

private:
  const string _name;
};

/* ============= the Dog and Cat subclasses ========== */

class Dog : public Animal {
  animalType get_type() const {
    return Animal::dog;
  }
};

class Cat : public Animal {
  animalType get_type() const {
    return Animal::cat;
  }
};

/* =========== class interface ============= */

class AnimalShelter {
public:

  AnimalShelter() : arrivalCounter(0) {};
  void enqueue(shared_ptr<Animal> animal);
  shared_ptr<Animal> dequeueAny();
  shared_ptr<Animal> dequeueType(Animal::animalType type);

private:

  class Ticket {
  public:
    Ticket(shared_ptr<Animal> animal, int time) : 
      _animal(animal), _arrivalTime(time) {};
    unsigned long long _arrivalTime;
    shared_ptr<Animal> _animal;
  };
  array<queue<Ticket>,Animal::kNumTypes> _animalQueues;
  unsigned long long arrivalCounter;
};


/* =========== method definitions ============= */

void AnimalShelter::enqueue(shared_ptr<Animal> animal) {
  assert(animal);
  _animalQueues[animal->get_type()].push(Ticket(animal, arrivalCounter++));
}

shared_ptr<Animal> AnimalShelter::dequeueType(Animal::animalType type) {
  if (_animalQueues[type].empty()) return nullptr;
  auto animal = _animalQueues[type].front()._animal;
  _animalQueues[type].pop();
  return animal;
}

shared_ptr<Animal> AnimalShelter::dequeueAny() {
  shared_ptr<Animal> animal = nullptr;
  int queue_idx = -1;
  unsigned long long arrival = numeric_limits<unsigned long long>::max();
  for (int idx = 0; idx < _animalQueues.size(); ++idx) {
    auto &queue = _animalQueues[idx];
    if (!queue.empty() && queue.front()._arrivalTime < arrival) {
      queue_idx = idx;
      arrival = queue.front()._arrivalTime;
    }
  }
  if (queue_idx >= 0) {
    animal = _animalQueues[queue_idx].front()._animal;
    _animalQueues[queue_idx].pop();
  }
  return animal;
}

int main(int argc, char **argv) {
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}
