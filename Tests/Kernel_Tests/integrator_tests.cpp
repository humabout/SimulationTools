// integrator_tests.cpp


// Inclusions
#include <vector>
#include "../pch.h"
#include "../../Source/Core/Integrators/integrator.h"
#include "../../Source/Core/Integrators/integrator.cpp"


// Sample Integrator Class to Test Internals
namespace nemesis
{
  class IntegratorTest : public Integrator
  {
  public:
    // Required Functions
    IntegratorTest() {}
    ~IntegratorTest() {}
    void doUpdateStates(void) {}

    // Access to Integrator Internals
    std::vector<unsigned int>  getStateOrders(void)
    {
      std::vector<unsigned int> out;
      for (state_list::iterator state = States.begin();
        state != States.end();
        ++state)
      {
        out.push_back((*state).second.order());
      }
      return out;
    }

  };
}


// Test Fixture
struct IntegratorTests : public ::testing::Test 
{




};