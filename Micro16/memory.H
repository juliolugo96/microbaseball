# ifndef MEMORY_H
# define MEMORY_H


/**
*   @name Memory
*   @file memory.H
*   @author Micro 16 development team
*   @brief DRAM memory developed using system-C library
*/

# include <systemc.h>
# include <fstream>

# define MEMORY_SIZE 256

using namespace std;

class memory : public sc_module
{
public:

  sc_in <bool> clock;

  sc_in < sc_uint<4> > op;

  sc_in < sc_uint<8> > address;
  sc_in < sc_uint<32> > input_data;
  sc_out < sc_uint<32> > output_data;

  SC_CTOR(memory)
  {
    SC_METHOD(load)
      sensitive << clock.neg() << address << op;

    SC_METHOD(store)
      sensitive << clock.pos() << input_data << address << op;
  }

  ~memory()
  {
    ofstream out("final_memory.txt");
    for(int i = 0 ; i < MEMORY_SIZE; i++)
      out << memory_adress[i].to_int() << endl;

  }
  
private:

  sc_bv <32> memory_adress[MEMORY_SIZE];

  void load()
  {
    if(op.read().to_int() == 0)
      output_data.write(memory_adress[address.read().to_int()]);
  }

  void store()
  {
    if(op.read().to_int() == 1)
      memory_adress[address.read().to_int()] = input_data.read();
  }
  
};


#endif