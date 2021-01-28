// block.h


#ifndef BLOCk_H
#define BLOCk_H


// Inclusions
#include <map>
#include <memory>
#include "state.h"


//------------------------------------------------------------------------------
// Name:    nemesis
// Purpose: This namespace holds all aspects of the Nemesis Simulation Toolkit.
//------------------------------------------------------------------------------
namespace nemesis
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
    typedef std::pair<unsigned int, State::pointer> state;
    typedef std::multimap< unsigned int, State::pointer, std::greater<unsigned int> > state_list;

    // Destructor
    virtual ~Block();

    // Functionality
    void initialize(void);
    void propagate(void);
    void update(void);

  protected:
    // Stores all states associated wtih this block in order from highest to 
    // lowest order derivatives
    state_list States;

    //--------------------------------------------------------------------------
    // Name:    addState
    // Purpose: This method adds a new state to the block. It forwards the call 
    //          to placeState for implementation to encapsulate it where it is 
    //          more easily altered in the future.
    //--------------------------------------------------------------------------
    template <class T>
    void addState(T&           x_, 
                  T&           dx_, 
                  unsigned int order_)
    {
      placeState( State::create(x_, dx_), order_ );
    }

  private:
    // Functionality
    virtual void doInitialize(void) = 0;
    virtual void doUpdate(void)     = 0;
    virtual void doPropagate(void);

    void placeState(nemesis::State::pointer state_,
                    unsigned int            order_);
  };


} // !core


#endif // !BLOCk_H
