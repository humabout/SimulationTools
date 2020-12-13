// block.h


#ifndef BLOCk_H
#define BLOCk_H


// Inclusions
#include <memory>
#include <vector>
#include "state.h"


//------------------------------------------------------------------------------
// Name:    kernel
// Purpose: This namespace holds all parts of the simulation kernel.
//------------------------------------------------------------------------------
namespace kernel
{


  //----------------------------------------------------------------------------
  // Name:    Block
  // Purpose: This abstract class exists as part of the simulation kernel and 
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


    // Constructors
    Block();
    Block(const Block& that);

    // Destructor
    virtual ~Block();

    // Adding States
    void add(double& x_, double& dx_);
    void add(double& x_, const State::pointer& dx_);
    void add(const State::pointer& state_);

    // Operators
    void operator<< (const std::shared_ptr<State>& state_);

    // Functionality
    void initialize(void);
    void propagate(void);
    void update(void);

  protected:
    // Stores all states associated wtih this block
    std::vector< std::shared_ptr<State> > States;

  private:

    // Functionality
    virtual void doInitialize(void) = 0;
    virtual void doUpdate(void) = 0;
    virtual void doPropagate(void);

  };


} // !kernel


#endif // !BLOCk_H
