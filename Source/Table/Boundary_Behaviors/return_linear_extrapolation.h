// return_linear_extrapolation.h


#ifndef NEMESIS_RETURN_LINEAR_EXTRAPOLATION_H
#define NEMESIS_RETURN_LINEAR_EXTRAPOLATION_H


// Inclusions
#include "table_boundary_interface.h"


//------------------------------------------------------------------------------
// Name:    nemesis
// Purpose: This namespace holds all aspects of the Nemesis Simulation Toolkit.
//------------------------------------------------------------------------------
namespace nemesis
{
   

  //----------------------------------------------------------------------------
  // Name:    ReturnLinearExtapolation
  // Purpose: This concretion extrapolates linearly outward from the table 
  //          bounds and returns the value.
  //----------------------------------------------------------------------------
  class ReturnLinearExtapolation : public TableBoundaryInterface
  {
  public:
    // Constructors
    ReturnLinearExtapolation()
    {
      // Does Nothing
    }
    ReturnLinearExtapolation(Table* ptr)
    {
      table = Table::pointer(ptr);
      initialize();
    }


    // Destructor
    ~ReturnLinearExtapolation()
    {
      // Does Nothing
    }


    // Functionality
    float lookup(std::size_t index,
                 float       key) const
    {
      float extrapolation;
      if (key < table->Keys.front())
      {
        extrapolation = m_lower[index] * key + b_lower[index];
      }
      else if (key > table->Keys.back())
      {
        extrapolation = m_upper[index] * key + b_upper[index];
      }
      else
      {
        throw std::runtime_error("Fatal Error: Non-boundary value requested from boundary behavior class.");
      }
      return extrapolation;
    }


  private:
    // Data
    std::vector<float> m_lower;
    std::vector<float> m_upper;

    std::vector<float> b_lower;
    std::vector<float> b_upper;


    // Helper Functions
    void initialize(void)
    {
      // Calculating Upper Boundary Extrapolation Values
      std::vector<float>::iterator x_it = table->Keys.end() - 1;
      float x2 = *(x_it);
      float x1 = *(x_it - 1);
      std::vector< std::vector<float> >::iterator y_it = table->Entries.end() - 1;
      std::vector<float> y2 = *(y_it);
      std::vector<float> y1 = *(y_it - 1);
      for (std::size_t i = 0; i < table->Field_Names.size(); i++)
      {
        m_upper[i] = (y2[i] - y1[i]) / (x2 - x1);
        b_upper[i] = y1[i] - m_upper[i] * x1;
      }

      // Calculating Lower Boundary Extrapolation Values
      x_it = table->Keys.begin();
      x1 = *(x_it);
      x2 = *(x_it + 1);
      y_it = table->Entries.begin();
      y1 = *(y_it);
      y2 = *(y_it + 1);
      for (std::size_t i = 0; i < table->Field_Names.size(); i++)
      {
        m_lower[i] = (y2[i] - y1[i]) / (x2 - x1);
        b_lower[i] = y1[i] - m_lower[i] * x1;
      }
    }


  }; // !ReturnLinearExtapolation


} // !nemesis


#endif // !NEMESIS_RETURN_LINEAR_EXTRAPOLATION_H
