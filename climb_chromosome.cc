
#include "climb_chromosome.hh"


void ClimbChromosome::mutate() {
  auto currentBest = get_fitness();
  std::uniform_int_distribution<int> randomInt(0, order_.size()-1);
  unsigned p = randomInt(generator_);
  unsigned solution = 0; //0 = gene stays, 1 = swap with p-1, 2 = swap with p+1
  auto valueOfP = order_[p];
  if (p == 0) {                        //Swap p with p-1
    order_[0] = order_.back();
    order_.back() = valueOfP;
  }
  else {
    order_[p] = order_[p-1];
    order_[p-1] = valueOfP;
  }

  auto newBest = get_fitness();
  if (newBest >= currentBest) {       //Evaluate new best
    currentBest = newBest;
    solution = 1;
  }

  if (p == 0) {                       //Swap the values back
    order_.back() = order_[0];
    order_[0] = valueOfP;
  }
  else {
    order_[p-1] = order_[p];
    order_[p] = valueOfP;
  }

  if (p == order_.size()-1){           //Swap p with p+1
    order_.back() = order_[0];
    order_[0] = valueOfP;
  }
  else {
    order_[p] = order_[p+1];
    order_[p+1] = valueOfP;
  }

  newBest = get_fitness();
  if (newBest >= currentBest) {       //Evaluate new best
    currentBest = newBest;
    solution = 2;
  }

  if (solution == 0) {            //The original order was best. Change it back.
    if (p == order_.size()-1){
      order_[0] = order_[p];
      order_[p] = valueOfP;
    }
    else {
      order_[p+1] = order_[p];
      order_[p] = valueOfP;
    }
  }
  else if (solution == 1){        //The p-1 order was best. Change it to that.
    if (p == order_.size()-1){
      order_[0] = order_[p];
      order_[p] = valueOfP;
    }
    else {
      order_[p+1] = order_[p];
      order_[p] = valueOfP;
    }
    if (p == 0) {
      order_[0] = order_.back();
      order_.back() = valueOfP;
    }
    else {
      order_[p] = order_[p-1];
      order_[p-1] = valueOfP;
    }
  }
  else if (solution == 2){        //The p+1 order was best. Do nothing.
    //do nothing
  }
  else{
    assert(false); //This should never happen
  }
}
