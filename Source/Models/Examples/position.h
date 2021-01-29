// simple_integrator.h


#ifndef NEMESIS_MODEL_POSISTION_H
#define NEMESIS_MODEL_POSISTION_H


// Inclusions
#include <memory>
#include "../../Core/block.h"


namespace nemesis
{


  //----------------------------------------------------------------------------
  // Name:    examples
  // Purpose: This namespace contains examples of how to use Nemesis Took Kit.
  //----------------------------------------------------------------------------
  namespace examples
  {


    class Position : public Block
    {
    public:
      // Typedefs
      typedef std::shared_ptr<Position> pointer;

      // Constructors
      Position();
      Position(double position_,
               double velocity_,
               double acceleration_);

      // Destructor
      ~Position();

      // Accessors
      double position(void) const;
      double velocity(void) const;
      double acceleration(void) const;

      // Debug
      void print(void) const;

    private:
      // Data
      double pos;
      double vel;
      double acc;

      // Functionality Implementations
      void doInitialize(void);
      void doRegisterWith(SimLoop* sim_);
      void doUpdate(void);


    }; // !SimpleIntegrator


  } // !examples


} // !nemesis


#endif // !NEMESIS_MODEL_POSITION_H
