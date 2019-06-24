#ifndef FIRST_PIPE_H
#define FIRST_PIPE_H


/**
*   @name First pipe
*   @file first_pipe.H
*   @author Micro 16 development team
*   @brief First pipe designed and developed in C++ using
*   system-C library
*/

#define instruction_length 16

# include <systemc.h>
# include <iostream>
# include <iomanip>




class first_pipe : public sc_module
{
public:
  sc_in <bool> clock;
  sc_in <bool> enable;
  sc_in < sc_uint<instruction_length> > instruction;

  sc_out < sc_uint<4> > op, r3, r2, r1;
  sc_out < sc_uint<8> > dir;

  SC_CTOR(first_pipe)
  {
    for(int i = 0 ; i < 3; i++)
      arit_log_reg[i] = 0;

    op_reg = 0;
    dir_reg = 0;

    SC_METHOD(write);
      sensitive << clock.pos() << enable << instruction;

    SC_METHOD(read);
      sensitive << clock.neg();
  }



private:
  sc_uint<4> op_reg;
  sc_uint <4> arit_log_reg[3];
  sc_uint <8> dir_reg;

  void write()
  {   
    if(enable)
      {
        op_reg = instruction.read().range(15, 12);

        for(int i = 0, j = 11; i < 3; i++, j -= 4)
          arit_log_reg[i] = instruction.read().range(j, j - 3);

        dir_reg = instruction.read().range(8, 0);
      }
  }

  void read()
  {
    op.write(op_reg);
    r3.write(arit_log_reg[0]);
    r1.write(arit_log_reg[1]);
    r2.write(arit_log_reg[2]);
    dir.write(dir_reg);

  }

};



#endif