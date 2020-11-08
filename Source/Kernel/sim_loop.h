// sim_loop.h


#ifndef SIM_LOOP_H
#define SIM_LOOP_H


// Inclusions
#include <vector>
#include "block.h"
#include "Integration_Methods/integration_method.h"


//------------------------------------------------------------------------------
// Name:    kernel
// Purpose: This namespace holds all parts of the simulation kernel.
//------------------------------------------------------------------------------
namespace kernel
{


  //----------------------------------------------------------------------------
  // Name:    SimLoop
  // Purpose: This class is responsible for running the simulation loop until
  //          end conditions are met. It will use a strategy pattern to compose
  //          various parts of the loop, like end conditions and integration
  //          method from parts to give the user more flexibility when setting
  //          up a simulation.
  //----------------------------------------------------------------------------
  class SimLoop
  {
  public:
    // Constructors
    SimLoop();
    SimLoop(double                  time_step_,
            double                  time_max_,
            IntegrationMethod::type integration_method_);

    // Destructor
    ~SimLoop();

    // Functionality
    void add(Block* block_);
    void operator<< (Block* block_);
    void run(void);

  private:
    // Member Variables
    IntegrationMethod*  Integrator;
    std::vector<Block*> Blocks;
    double              Time_Step;
    double              Time_Max;
    // TODO:  Create and add a list of EndCondition objects that are checked to 
    //        see if end conditions are met. This might be tricky to set up, but
    //        it will add flexibility.

    // Functionality
    bool isEnd(void) const;

  }; // !SimLoop


} // !kernel


#endif // !SIM_LOOP_H
