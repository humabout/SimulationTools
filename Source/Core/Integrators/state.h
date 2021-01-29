// state.h


#ifndef STATE_H
#define STATE_H


// Inclusions
#include <memory>


//------------------------------------------------------------------------------
// Name:    nemesis
// Purpose: This namespace holds all aspects of the Nemesis Simulation Toolkit.
//------------------------------------------------------------------------------
namespace nemesis
{


  //--------------------------------------------------------------------------
  // Name:    State
  // Purpose: This class encapsulates state/state derivative pairs and 
  //          provides several useful functions for comparing states. Note 
  //          that while this contains references to variables, it does NOT
  //          own them and is not responsible for deallocating them.
  //--------------------------------------------------------------------------
  class State
  {
  public:
    // Typedefs
    typedef std::shared_ptr<State> pointer;

    // Constructor
    State() = delete;
    State(double& x_,
          double& dx_);
    State(const State& that);

    // Destructor
    virtual ~State();

    // Accesors
    double&       x(void) const;
    double&       dx(void) const;
    unsigned int& order(void);

    // Factory
    static State::pointer create(double& x_,
                                 double& dx_);

    // Copy Assignment Operator
    void operator=(const State& lhs);

    // Comparison Operators
    bool operator==(const State& lhs) const;
    bool operator!=(const State& lhs) const;
    bool operator< (const State& lhs) const;
    bool operator<=(const State& lhs) const;
    bool operator> (const State& lhs) const;
    bool operator>=(const State& lhs) const;

  protected:
    // Member Variables
    double*      State_Variable;
    double*      State_Derivative;
    unsigned int Order;


  }; // !State


} // !core


#endif // !STATE_H

