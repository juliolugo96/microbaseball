#ifndef SECOND_PIPE_H
#define SECOND_PIPE_H

/**
*   @name second pipe
*   @file second_pipe.H
*   @author Micro 16 development team
*   @brief second pipe designed and developed in C++ using
*   system-C library
*/

# include <systemc.h>


class second_pipe : public sc_module
{
public:
  sc_in <bool> clock;
  sc_in <bool> enable;

  sc_in < sc_uint<4> > op_in, r3_in; 
  sc_in < sc_uint<32> > store_in, r2_in, r1_in;
  sc_in < sc_uint<8> > dir_in;

  sc_out < sc_uint<4> > op_out, r3_out; 
  sc_out < sc_uint<32> > store_out, r2_out, r1_out;
  sc_out < sc_uint<8> > dir_out;

  SC_CTOR(second_pipe)
  {
    for(int i = 0 ; i < 3; i++)
      arit_log_reg[i] = 0;

    op_reg = 0;
    dir_reg = 0;

    SC_METHOD(write);
      sensitive << clock.pos() << enable << op_in << r3_in << r2_in << r1_in << dir_in;

    SC_METHOD(read);
      sensitive << clock.neg();
  }



private:
  sc_uint<4> op_reg, r3_reg;
  sc_uint <32> arit_log_reg[3];
  sc_uint <8> dir_reg;

  void write()
  {   
    if(enable)
      {
        op_reg = op_in.read();
        arit_log_reg[0] = store_in.read();
        arit_log_reg[1] = r1_in.read();
        arit_log_reg[2] = r2_in.read();
        r3_reg = r3_in.read();
        dir_reg = dir_in.read();
      }
  }

  void read()
  {
    op_out.write(op_reg);
    r3_out.write(r3_reg);
    store_out.write(arit_log_reg[0]);
    r1_out.write(arit_log_reg[1]);
    r2_out.write(arit_log_reg[2]);
    dir_out.write(dir_reg);
  }

};



#endif