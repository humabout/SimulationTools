// table_type_definitions.h


#ifndef NEMESIS_TABLE_TYPE_DEFINITIONS_H
#define NEMESIS_TABLE_TYPE_DEFINITIONS_H


namespace nemesis
{


  //----------------------------------------------------------------------------
  // Name:    table
  // Purpose: This is responsible for holding all enum values needed by the 
  //          Table class.
  //----------------------------------------------------------------------------
  namespace table
  {


    // Enums and Typedefs
    enum class at_boundary
    {
      return_zero,
      cap_at_end_value,
      linear_extrapolation
    }; // !at_boundary


    enum class lookup
    {
      next_lower_value,
      nearest_value,
      exact_value,
      linear_interpolation,
      spline_interpolation,
      next_higher_value
    }; // !lookup


  } // !table


} // !nemesis


#endif // !NEMESIS_TABLE_TYPE_DEFINITIONS_H