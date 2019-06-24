#ifndef REGISTER_FILE_H
#define REGISTER_FILE_H

/**
*   @name Register file
*   @file register_file.H
*   @author Micro 16 development team
*   @brief register file used by microprocessor (it uses both operator) developed using system-C library
*/

# include <systemc.h>
# include <fstream>
 
#define REG_SIZE 16



class register_file : public sc_module
{
public:

  sc_in <bool> clock;
  sc_in<bool> enable;

  sc_in < sc_uint<4> > op;
  sc_in < sc_uint<4> > r1_dir;
  sc_in < sc_uint<4> > r2_dir;
  sc_in < sc_uint<4> > store_dir;

  sc_in < sc_uint<4> > write_back_dir;
  sc_in < sc_uint<32> > write_back_data;

  sc_out < sc_uint<32> > r1;
  sc_out < sc_uint<32> > r2;
  sc_out < sc_uint<32> > store;

  SC_CTOR(register_file )
  {

    SC_METHOD(read);
      sensitive << clock.neg() << r1_dir << r2_dir << store_dir;

    SC_METHOD(write);
      sensitive << clock.pos() << op << write_back_dir << write_back_data << enable;

    for(int i = 0; i < REG_SIZE; ++i)
      registers[i] = i;

  }

  ~register_file()
  {
    ofstream out("final_register.txt");

    for(int i = 0; i < REG_SIZE; ++i)
      out << registers[i].to_int() << endl;
    
  }

  

private:

  sc_uint<32> registers[REG_SIZE];

  void read()
  {
      r1.write( registers[ r1_dir.read() ] );
      r2.write( registers[ r2_dir.read() ] );
      store.write( registers[ store_dir.read() ] );
  }

  void write()
  {
    if(enable and (op.read() != 1))
      registers[write_back_dir.read()] = write_back_data.read();

    registers[0] = 0;
  }

};


#endif