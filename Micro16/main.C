#include <m_16.H>
#include <testbench.H>

int sc_main(int argc,char *argv[]){
  sc_time DELAY(10,SC_NS);
  sc_time PERIOD(10,SC_NS);
  
  sc_clock clk("clock",PERIOD,0.5,DELAY,true);
  sc_signal< sc_uint<5> > pc;
  sc_signal< sc_uint<32> > last_data;
  sc_signal< bool > enable;
  m_16 micro("micro");
  testbench test("test");

  micro.pc(pc);
  micro.last_data(last_data);
  micro.enable(enable);
  micro.clock(clk);
  
  test.pc(pc);
  test.last_data(last_data);
  test.enable(enable);
  test.clock(clk);
  

  sc_start();
  
return 0;
}
