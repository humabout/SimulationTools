// block.h


#ifndef BLOCk_H
#define BLOCk_H


// Inclusions
#include <memory>


namespace nemesis
{
  class SimLoop;
}


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

    // Destructor
    ~Block();

    // Functionality
    void initialize(void);
    void registerWith(SimLoop* sim_);
    void update(void);

  private:
    // Functionality
    virtual void doInitialize(void)            = 0;
    virtual void doRegisterWith(SimLoop* sim_) = 0;
    virtual void doUpdate(void)                = 0;


  };


} // !core


// Forward Declaration Inclusions
#include "sim_loop.h"

#endif // !BLOCk_H
