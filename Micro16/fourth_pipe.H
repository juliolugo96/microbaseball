#ifndef FOURTH_PIPE_H
#define FOURTH_PIPE_H

/**
*   @name Fourth pipe
*   @file fourth_pipe.H
*   @author Micro 16 development team
*   @brief Fourth pipe designed and developed in C++ using
*   system-C library
*/

# include <systemc.h>


class fourth_pipe : public sc_module
{
public:
  sc_in <bool> clock;
  sc_in <bool> enable;

  sc_in < sc_uint<4> > op_in, r3_in; 
  sc_in < sc_uint<32> > result_in, load_in;

  sc_out < sc_uint<4> > op_out, r3_out; 
  sc_out < sc_uint<32> > write_back_out;

  SC_CTOR(fourth_pipe)
  {
    for(int i = 0 ; i < 2; i++)
      arit_log_reg[i] = 0;

    op_reg = 0;

    SC_METHOD(write);
      sensitive << clock.pos() << enable << op_in << r3_in << result_in << load_in;

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
        arit_log_reg[1] = load_in.read();
      }
  }

  void read()
  {
    op_out.write(op_reg);
    r3_out.write(r3_reg);

    if(op_reg.to_int() == 0)
      write_back_out.write(arit_log_reg[1]);
    else
      write_back_out.write(arit_log_reg[0]);
  }

};



#endif