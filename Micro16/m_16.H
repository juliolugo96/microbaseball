#ifndef M_16_H
#define M_16_H

# include <systemc.h>
# include <instruction_memory.H>
# include <first_pipe.H>
# include <register_file.H>
# include <second_pipe.H>
# include <alu.H>
# include <third_pipe.H>
# include <memory.H>
# include <fourth_pipe.H>
# include <iostream>


#define instruction_length 16

using namespace std;

class m_16 : public sc_module
{
public:

  sc_in < sc_uint<5> > pc;
  sc_in <bool> clock;
  sc_in <bool> enable;

  sc_out < sc_uint<32> > last_data; 

  SC_CTOR(m_16)
  {

    SC_METHOD(prop_pipe_one)
      sensitive << pipe_one_op_sg << pipe_one_r3_sg;

    SC_METHOD(prop_pipe_two)
      sensitive << pipe_two_op_out_sg << pipe_two_dir_out_sg << pipe_two_r3_out_sg << pipe_two_store_out_sg;

    SC_METHOD(prop_pipe_three)
      sensitive << pipe_three_op_out_sg << pipe_three_result_out_sg << pipe_three_r3_out_sg;

    SC_METHOD(prop_pipe_four)
      sensitive << pipe_four_write_back_out_sg;



    
    pipe_one = new first_pipe("pipe_one");
    pipe_two = new second_pipe("pipe_two");
    pipe_three = new third_pipe("pipe_three");
    pipe_four = new fourth_pipe("pipe_four");
    ins_mem = new instruction_memory("ins_mem");  
    reg_file = new register_file("reg_file");
    ALU = new alu("ALU");
    data_memory = new memory("data_memory");

  /**
====================================================
    FETCH STAGE
====================================================

  */

    ins_mem -> address(pc);

    ins_mem -> instruction(ins_mem_sg);


  /**
====================================================
    FIRST PIPE
====================================================

  */

    pipe_one -> clock(clock);
    pipe_one -> enable(enable);
    pipe_one -> instruction(ins_mem_sg);

    pipe_one -> op(pipe_one_op_sg);
    pipe_one -> r3(pipe_one_r3_sg);
    pipe_one -> r2(pipe_one_r2_sg);
    pipe_one -> r1(pipe_one_r1_sg);
    pipe_one -> dir(pipe_one_dir_sg);


 /**
====================================================
    INSTRUCTION DECODING
====================================================

  */

    reg_file -> clock(clock);
    reg_file -> enable(enable);
    reg_file -> op(pipe_one_op_sg);
    reg_file -> store_dir(pipe_one_r3_sg);
    reg_file -> r1_dir(pipe_one_r1_sg);
    reg_file -> r2_dir(pipe_one_r2_sg);
    reg_file -> write_back_dir(pipe_four_r3_out_sg);
    reg_file -> write_back_data(pipe_four_write_back_out_sg);

    reg_file -> r1(reg_file_r1_sg);
    reg_file -> r2(reg_file_r2_sg);
    reg_file -> store(reg_file_store_sg);

/**
====================================================
    SECOND PIPE
====================================================

  */

    pipe_two -> clock(clock);
    pipe_two -> enable(enable);
    pipe_two -> op_in(op_one_sg);
    pipe_two -> r3_in(r3_one_sg);
    pipe_two -> r2_in(reg_file_r2_sg);
    pipe_two -> r1_in(reg_file_r1_sg);
    pipe_two -> store_in(reg_file_store_sg);
    pipe_two -> dir_in(pipe_one_dir_sg);

    pipe_two -> op_out(pipe_two_op_out_sg);
    pipe_two -> r3_out(pipe_two_r3_out_sg);
    pipe_two -> r2_out(pipe_two_r2_out_sg);
    pipe_two -> r1_out(pipe_two_r1_out_sg);
    pipe_two -> store_out(pipe_two_store_out_sg);
    pipe_two -> dir_out(pipe_two_dir_out_sg);




/**
====================================================
    ARITHMETIC LOGIC UNIT
====================================================

  */

    ALU -> op(pipe_two_op_out_sg);
    ALU -> first(pipe_two_r1_out_sg);
    ALU -> second(pipe_two_r2_out_sg);


    ALU -> result(result_sg);



/**
====================================================
    THIRD PIPE
====================================================

  */


    pipe_three -> clock(clock);
    pipe_three -> enable(enable);
    pipe_three -> op_in(op_two_sg);
    pipe_three -> r3_in(pipe_two_r3_out_sg);
    pipe_three -> result_in(result_sg);
    pipe_three -> store_in(pipe_two_store_out_sg);
    pipe_three -> dir_in(pipe_two_dir_out_sg);

    pipe_three -> op_out(pipe_three_op_out_sg);
    pipe_three -> r3_out(pipe_three_r3_out_sg);
    pipe_three -> result_out(pipe_three_result_out_sg);
    pipe_three -> store_out(pipe_three_store_out_sg);
    pipe_three -> dir_out(pipe_three_dir_out_sg);


/**
====================================================
    MEMORY ACCESS
====================================================

  */

    data_memory -> clock(clock);
    data_memory -> op(pipe_three_op_out_sg);
    data_memory -> address(pipe_three_dir_out_sg);
    data_memory -> input_data(pipe_three_store_out_sg);

    data_memory -> output_data(memory_sg);

/**
====================================================
    WRITE_BACK
====================================================

  */

    pipe_four -> clock(clock);
    pipe_four -> enable(enable);
    pipe_four -> op_in(op_three_sg);
    pipe_four -> r3_in(pipe_three_r3_out_sg);
    pipe_four -> result_in(pipe_three_result_out_sg);
    pipe_four -> load_in(memory_sg);

    pipe_four -> op_out(pipe_four_op_out_sg);
    pipe_four -> r3_out(pipe_four_r3_out_sg);
    pipe_four -> write_back_out(pipe_four_write_back_out_sg);



  }


  ~m_16()
  {
    delete pipe_one;
    delete pipe_two;
    delete pipe_three;
    delete pipe_four;
    delete ins_mem;
    delete reg_file;
    delete ALU;
    delete data_memory;
  }

private:
  
  //PIPES
  //-----

  first_pipe * pipe_one;
  second_pipe * pipe_two;
  third_pipe * pipe_three;
  fourth_pipe * pipe_four;

  //MODULES
  //-------

  instruction_memory * ins_mem;
  register_file *reg_file;
  alu *ALU;
  memory *data_memory;

  //SIGNALS
  //-------

  //Propagation signals
  sc_signal< sc_uint<4> > op_one_sg, op_two_sg, op_three_sg;
  sc_signal< sc_uint<4> > r3_one_sg;

  //Instruction memory signals
  sc_signal < sc_uint<instruction_length> > ins_mem_sg;

  //First pipe signals
  sc_signal < sc_uint<4> > pipe_one_op_sg, pipe_one_r3_sg, pipe_one_r2_sg, pipe_one_r1_sg;
  sc_signal < sc_uint<8> > pipe_one_dir_sg;

  //Register file signals
  sc_signal < sc_uint<32> > reg_file_r1_sg, reg_file_r2_sg, reg_file_store_sg;


  //Second pipe signals
  sc_signal < sc_uint<32> > pipe_two_r2_out_sg, pipe_two_r1_out_sg, pipe_two_store_out_sg;
  sc_signal < sc_uint<4> >  pipe_two_r3_out_sg, pipe_two_op_out_sg;
  sc_signal < sc_uint<8> > pipe_two_dir_out_sg;


  //ALU signal
  sc_signal < sc_uint<32> > result_sg;

  //third pipe signals
  sc_signal < sc_uint<4> > pipe_three_r3_out_sg, pipe_three_op_out_sg;
  sc_signal < sc_uint<8> > pipe_three_dir_out_sg;
  sc_signal < sc_uint<32> > pipe_three_result_out_sg, pipe_three_store_out_sg;

  //Memory signals
  sc_signal < sc_uint<32> > memory_sg;

  //fourth pipe signals
  sc_signal < sc_uint<4> > pipe_four_op_out_sg, pipe_four_r3_out_sg;
  sc_signal < sc_uint<32> > pipe_four_write_back_out_sg;


  //Propagation voids

  void prop_pipe_one()
  {
    op_one_sg = pipe_one_op_sg;
    r3_one_sg = pipe_one_r3_sg;
  }

  void prop_pipe_two()
  {
    op_two_sg = pipe_two_op_out_sg;
  }

  void prop_pipe_three()
  {
    op_three_sg = pipe_three_op_out_sg;
  }

  void prop_pipe_four()
  {
    last_data.write(pipe_four_write_back_out_sg.read());
  }

};



#endif