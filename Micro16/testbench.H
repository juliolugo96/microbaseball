#ifndef TESTBENCH_H
#define TESTBENCH_H

/**
*   @name Micro 16 Testbench unit
*   @file Testbench.H
*   @author Micro 16 development team
*   @brief Testbench used by Micro 16 development team for testing our 
*   microprocessor
*/

# include <systemc.h>
# include <iostream>
# include <iomanip>

using namespace std;

class testbench : public sc_module
{
public:
  
  sc_in <bool> clock;

  sc_out < sc_uint<5> > pc;
  
  sc_out <bool> enable;

  sc_in < sc_uint<32> > last_data;  

  SC_CTOR(testbench)
  {
    SC_THREAD(test)
      {
        sensitive << clock.pos();
        dont_initialize();
      }
  }
  
private:

  void test()
  {
    
    for (int i = 0; i < 29; i++)
    {
      enable.write(true);
      pc.write(i);

      wait();
      print();
    }

    sc_stop();
  }

  void print()
  {
    cout << sc_time_stamp() << setw(10) << left << "    " <<last_data.read() << endl;
  }

};




#endif