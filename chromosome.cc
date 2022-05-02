/*
 * Implementation for Chromosome class
 */

#include <algorithm>
#include <cassert>
#include <random>

#include "chromosome.hh"

//////////////////////////////////////////////////////////////////////////////
// Generate a completely random permutation from a list of cities
Chromosome::Chromosome(const Cities* cities_ptr)
  : cities_ptr_(cities_ptr),
    generator_(rand())
{
  Cities::permutation_t ret(cities_ptr->size()); //copy-pasted from cities.cc because that's the only way got it to work
  std::iota(ret.begin(), ret.end(), 0);

  static std::random_device rd;  // Static so we don't initialize every time
  static std::mt19937 g(rd());

  std::shuffle(ret.begin(), ret.end(), g);
  order_ = ret;


  assert(is_valid());
}

//////////////////////////////////////////////////////////////////////////////
/*/ Clean up as necessary
Chromosome::~Chromosome()
{
    delete cities_ptr_;
    while (order_.size() > 0)
    {
        order_.pop_back();
    }
}


/*/////////////////////////////////////////////////////////////////////////////
// Perform a single mutation on this chromosome
void
Chromosome::mutate()
{
  std::uniform_int_distribution<int> randomInt(0, order_.size()-1);
  int gene1Index = randomInt(generator_);
  int gene2Index = randomInt(generator_);
  while (gene1Index == gene2Index){
    gene1Index = randomInt(generator_);
   // gene2Index = randomInt(generator_); No need to rerandomize both
  }
  unsigned int temp = order_.at(gene1Index);
  order_.at(gene1Index) = order_.at(gene2Index);
  order_.at(gene2Index) = temp;

  assert(is_valid());
}

/* oops
void Chromosome::mutate()
{
    int size = static_cast<int>(order_.size());
    int indx1 = rand() % size;
    int indx2 = rand() % size;
    while (indx1 == indx2) //Just in case!
    {
        int indx2 = rand() % size;
    }
    auto tmp = order_[indx1];
    order_[indx1] = order_[indx2];
    order_[indx2] = tmp;

}
*/

//////////////////////////////////////////////////////////////////////////////
// Return a pair of offsprings by recombining with another chromosome
// Note: this method allocates memory for the new offsprings
std::pair<Chromosome*, Chromosome*>
Chromosome::recombine(const Chromosome* other)
{
 // std::cout << "Recombining...\n";
  assert(is_valid());
  assert(other->is_valid());
  //int size = static_cast<int>(order_.size());

    std::uniform_int_distribution<int> randomInt(0, order_.size()-1);
  unsigned b = randomInt(generator_);;
  unsigned e = randomInt(generator_);;
  while(b == e) //just in case!
  {
      b = randomInt(generator_);
  }
  if (b > e) //if b is greater, swaps the values
  {
      auto tmp = b;
      b = e;
      e = tmp;
  }
  ///  std::cout << b << " | " << e << "\n";
  std::pair<Chromosome*, Chromosome*> retval;
  retval.first = create_crossover_child(this, other, b, e);
  retval.second = create_crossover_child(other, this, b, e);
  return retval;
}



//////////////////////////////////////////////////////////////////////////////
// For an ordered set of parents, return a child using the ordered crossover.
// The child will have the same values as p1 in the range [b,e),
// and all the other values in the same order as in p2.
Chromosome*
Chromosome::create_crossover_child(const Chromosome* p1, const Chromosome* p2,
                                   unsigned b, unsigned e) const
{
  //
  Chromosome* child = p1->clone();

  // We iterate over both parents separately, copying from parent1 if the
  // value is within [b,e) and from parent2 otherwise
  unsigned i = 0, j = 0;

  for ( ; i < p1->order_.size() && j < p2->order_.size(); ++i) {
    if (i >= b and i < e) {
      child->order_[i] = p1->order_[i];
    }
    else { // Increment j as long as its value is in the [b,e) range of p1
      while (p1->is_in_range(p2->order_[j], b, e)) {
        ++j;
        assert(j < p2->order_.size());
      }
      child->order_[i] = p2->order_[j];
      j++;
    }
  }

  assert(child->is_valid());
  return child;
}

// Return a positive fitness value, with higher numbers representing
// fitter solutions (shorter total-city traversal path).
double
Chromosome::get_fitness() const
{
  double distance = cities_ptr_->total_path_distance(order_);
  assert(distance > 0.0);
  return order_.size() / distance;
}

// A chromsome is valid if it has no repeated values in its permutation,
// as well as no indices above the range (length) of the chromosome.
bool
Chromosome::is_valid() const
{
    unsigned int sz = order_.size();
    if (sz != cities_ptr_->size())
    {
        return false;
    }
  unsigned int count = 0;
 // std::cout << "Checking ";
  //for (auto it = order_.begin(); it != order_.end(); ++it) {
 //   std::cout << *it << " ";
 // }
//  std::cout << "\n";
    for (auto it = order_.begin(); it != order_.end(); ++it) //checks for duplicates
    {
        if(is_in_range(*it, count+1, sz))
        {
          //  std::cout << "Duplicate: " << *it << "\n";
            return false;
        }
        count++;
    }
    return true;

}

// Find whether a certain value appears in a given range of the chromosome.
// Returns true if value is within the specified the range specified
// [begin, end) and false otherwise.
bool
Chromosome::is_in_range(unsigned value, unsigned begin, unsigned end) const
{
    unsigned int count = 0;
    for (auto iter = order_.begin(); iter != order_.end(); ++iter)
    {
        if(count >= end)
        {
            break;
        }
        else if (count >= begin)
        {
            if (*iter == value)
            {
                return true;
            }
        }
        count++;
    }
    return false;
}
