#ifndef THIRD_PIPE_H
#define THIRD_PIPE_H

/**
*   @name Third pipe
*   @file third_pipe.H
*   @author Micro 16 development team
*   @brief Third pipe designed and developed in C++ using
*   system-C library
*/

# include <systemc.h>
# include <iostream>

using namespace std;


class third_pipe : public sc_module
{
public:
  sc_in <bool> clock;
  sc_in <bool> enable;

  sc_in < sc_uint<4> > op_in, r3_in; 
  sc_in < sc_uint<32> > result_in, store_in;
  sc_in < sc_uint<8> > dir_in;

  sc_out < sc_uint<4> > op_out, r3_out; 
  sc_out < sc_uint<32> > result_out, store_out;
  sc_out < sc_uint<8> > dir_out;

  SC_CTOR(third_pipe)
  {
    for(int i = 0 ; i < 2; i++)
      arit_log_reg[i] = 0;

    op_reg = 0;
    dir_reg = 0;

    SC_METHOD(write);
      sensitive << clock.pos() << enable << op_in << r3_in << result_in << store_in << dir_in;

    SC_METHOD(read);
      sensitive << clock.neg();
  }



private:
  sc_uint<4> op_reg, r3_reg;
  sc_uint <32> arit_log_reg[2];
  sc_uint <8> dir_reg;

  void write()
  {   
    if(enable)
      {
        op_reg = op_in.read();
        r3_reg = r3_in.read();
        arit_log_reg[0] = result_in.read();
        arit_log_reg[1] = store_in.read();
        dir_reg = dir_in.read();
      }
  }

  void read()
  {
    op_out.write(op_reg);
    r3_out.write(r3_reg);
    result_out.write(arit_log_reg[0]);
    store_out.write(arit_log_reg[1]);
    dir_out.write(dir_reg);
  }

};



#endif