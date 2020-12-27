// block.h


#ifndef BLOCk_H
#define BLOCk_H


// Inclusions
#include <memory>
#include <vector>
#include "state.h"


//------------------------------------------------------------------------------
// Name:    core
// Purpose: This namespace holds all parts of the simulation core.
//------------------------------------------------------------------------------
namespace core
{


  //----------------------------------------------------------------------------
  // Name:    Block
  // Purpose: This abstract class exists as part of the simulation core and 
  //          encapsulates a model, process, or collection thereof that is 
  //          executed once per simulated time step. It defines their interface.
  //          Blocks are responsible for propagating their own states, and 
  //          reporting aspects of that state on request. Specific blocks are 
  //          defined by a collection of sates and the methods that act on them.
  //          This interface uses a template pattern to enforce the interface.
  //----------------------------------------------------------------------------
  class Block
  {
  public:
    // Typedefs
    typedef std::shared_ptr<Block> pointer;

    // Destructor
    virtual ~Block();

    // Functionality
    void initialize(void);
    void propagate(void);
    void update(void);

  protected:
    // Stores all states associated wtih this block
    std::vector< std::shared_ptr<State> > States;

    //------------------------------------------------------------------------------
    // Name:    addState
    // Purpose: This method adds a new state to the block. It forwards the call to 
    //          placeState for implementation to encapsulate it where it is more 
    //          easily altered in the future.
    //------------------------------------------------------------------------------
    template <class T>
    void addState(T& x_, T& dx_)
    {
      placeState( State::create(x_, dx_) );
    }

  private:
    // Functionality
    virtual void doInitialize(void) = 0;
    virtual void doUpdate(void)     = 0;
    virtual void doPropagate(void);

    void placeState(core::State::pointer state_);
  };


} // !core


#endif // !BLOCk_H
