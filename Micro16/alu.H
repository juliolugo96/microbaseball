#ifndef ALU_H
#define ALU_H

/**
*   @name Arithmetic logic unit
*   @file alu.H
*   @author Micro 16 development team
*   @brief arithmetic logic unit designed and developed in C++ using
*   system-C library
*/

# include <systemc.h>
# include <iostream>

class alu : public sc_module
{
public:

  sc_in< sc_uint<4> > op;
  sc_in< sc_uint<32> > first;
  sc_in< sc_uint<32> > second;
  sc_out< sc_uint<32> > result;
  
  SC_CTOR(alu)
  {
    SC_METHOD(operation)
      sensitive << first << second << op;
  }

private:

  void operation()
  {
    switch(op.read())
    {
        ///Void operation, (used when instruction load is on the pipeline) let the first operator go through

      case  0:
            result.write(first.read());
            break;

        ///Void operation, (used when instruction store is on the pipeline) let the second operator go through

      case  1:
            result.write(second.read());
            break;

        ///Addition operation

      case  2: 
            result.write(first.read() + second.read());
            break;


        ///Substraction operation (only unsigned integers)

      case 3:
            if(first.read() > second.read()) 
              result.write(first.read() - second.read());
            else
              result.write(second.read() - first.read());
            break;


        ///Product operation

      case 4: 
            result.write(first.read() * second.read());
            break;

        ///Division operation

      case 5: 
            result.write(first.read() / second.read());
            break;

        ///Comparision operations

      case 6: 
            result.write(first.read() > second.read());
            break;

      case 7: 
            result.write(first.read() >= second.read());
            break;

      case 8: 
            result.write(first.read() < second.read());
            break;

      case 9:
            result.write(first.read() <= second.read());
            break;

      case 10: 
            result.write(first.read() == second.read());
            break;

      case 11: 
            result.write(first.read() != second.read());
            break;


          ///Logical operations

      case 12: 
            result.write(first.read() and second.read());
            break;

      case 13: 
            result.write(first.read() or second.read());
            break;

            ///'Greater than' and 'Smaller than' operations

      case 14: 
            if(first.read() > second.read())
              result.write(first.read());
            else if(first.read() < second.read())
              result.write(second.read());
            else
              result.write(0);
            break;

      case 15:
            if(first.read() < second.read())
              result.write(first.read());
            else if(first.read() > second.read())
              result.write(second);
            else
              result.write(0);
            break;

    }
  }


};

#endif