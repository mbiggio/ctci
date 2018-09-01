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
public:
  Dog(string name): Animal(name) {};
  animalType get_type() const {
    return Animal::dog;
  }
};

class Cat : public Animal {
public:  
  Cat(string name): Animal(name) {};
  animalType get_type() const {
    return Animal::cat;
  }
};

/* =========== class interface ============= */

class AnimalShelter {
public:

  AnimalShelter() : arrivalCounter(0) {};
  void enqueue(unique_ptr<Animal> &&animal);
  unique_ptr<Animal> dequeueAny();
  unique_ptr<Animal> dequeueType(Animal::animalType type);

private:

  class Ticket {
  public:
    Ticket(unique_ptr<Animal> &&animal, int time) : 
      _animal(move(animal)), _arrivalTime(time) {};
    unsigned long long _arrivalTime;
    unique_ptr<Animal> _animal;
  };
  array<queue<Ticket>,Animal::kNumTypes> _animalQueues;
  unsigned long long arrivalCounter;
};


/* =========== method definitions ============= */

void AnimalShelter::enqueue(unique_ptr<Animal> &&animal) {
  assert(animal);
  int type = animal->get_type();
  _animalQueues[type].push(Ticket(move(animal), arrivalCounter++));
}

unique_ptr<Animal> AnimalShelter::dequeueType(Animal::animalType type) {
  if (_animalQueues[type].empty()) return nullptr;
  auto animal = move(_animalQueues[type].front()._animal);
  _animalQueues[type].pop();
  return animal;
}

unique_ptr<Animal> AnimalShelter::dequeueAny() {
  unique_ptr<Animal> animal = nullptr;
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
    animal = move(_animalQueues[queue_idx].front()._animal);
    _animalQueues[queue_idx].pop();
  }
  return animal;
}

TEST(animal_shelter_test, nominal) {
  AnimalShelter shelter;
  ASSERT_NO_THROW(shelter.enqueue(make_unique<Dog>("bobby")));
  ASSERT_NO_THROW(shelter.enqueue(make_unique<Dog>("golia")));
  ASSERT_NO_THROW(shelter.enqueue(make_unique<Cat>("pussy")));

  unique_ptr<Animal> a;

  // get bobby
  ASSERT_NE(nullptr, a = shelter.dequeueAny());
  ASSERT_EQ(Animal::dog, a->get_type());
  ASSERT_EQ("bobby", a->getName());

  // get pussy
  ASSERT_NE(nullptr, a = shelter.dequeueType(Animal::cat));
  ASSERT_EQ(Animal::cat, a->get_type());
  ASSERT_EQ("pussy", a->getName());

  // try to get cat
  ASSERT_EQ(nullptr, a = shelter.dequeueType(Animal::cat));

  // get golia
  ASSERT_NE(nullptr, a = shelter.dequeueAny());
  ASSERT_EQ(Animal::dog, a->get_type());
  ASSERT_EQ("golia", a->getName());

  // try to get cat
  ASSERT_EQ(nullptr, a = shelter.dequeueAny());
  ASSERT_EQ(nullptr, a = shelter.dequeueType(Animal::cat));
  ASSERT_EQ(nullptr, a = shelter.dequeueType(Animal::dog));
}


int main(int argc, char **argv) {
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}
