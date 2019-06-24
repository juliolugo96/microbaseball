#ifndef INSTRUCTION_MEMORY
#define INSTRUCTION_MEMORY


/**
*   @name Instruction memory
*   @file instruction_memory.H
*   @author Micro 16 development team
*   @brief instruction memory used by microprocessor developed using system-C library
*/


# include <systemc.h>
# include <fstream>
# include <iostream>
# include <vector>
# include <bitset>

using namespace std;

#define instruction_length 16

class instruction_memory : public sc_module
{

public:

  sc_in < sc_uint<5> > address;
  sc_out< sc_uint<instruction_length> > instruction;

  SC_CTOR(instruction_memory)
  {
    SC_METHOD(search);
      sensitive << address;

      memory_file.open("inst_mem.txt");
      dependencies_control(memory_file);

  }

  ~instruction_memory()
  {
    memory_file.close();
  }
  
  private:
    
    fstream memory_file;
    vector <string> aux_mem;

    ///'Solve depend' method allows to use stalls to attack data hazards

    void solve_depend(vector<string> &mem_aux, int pos_init, int pos_fin)
    {
      vector<string> init, final, stalls;
      int jump_pos = 0, num_stalls = 0;

      for(int i = 0; i < 4 - pos_fin + pos_init; ++i)
      {
        stalls.push_back("0000000000000000");
        num_stalls++;
      }

      for(int i = 0 ; i < pos_fin; ++i)
      {  
        
        if(mem_aux[i].substr(0,4) == "1111")
        {
          bitset<5> jump_bin(mem_aux[i].substr(4,5));
          jump_pos = jump_bin.to_ulong();

          if(jump_pos >= pos_fin)
          {
            jump_pos += num_stalls;
            jump_bin = jump_pos;
            mem_aux[i] = "1111" + jump_bin.to_string() + mem_aux[i].substr(9,7);
          }
        }

        init.push_back(mem_aux[i]);
      }

      int mem_aux_size = mem_aux.size();

      for (int i = pos_fin; i < mem_aux_size; ++i)
      {  
        
        if(mem_aux[i].substr(0,4) == "1111")
        {
          bitset<5> jump_bin(mem_aux[i].substr(4,5));
          jump_pos = jump_bin.to_ulong();

          if(jump_pos >= pos_fin)
          {
            jump_pos += num_stalls;
            jump_bin = jump_pos;
            mem_aux[i] = "1111" + jump_bin.to_string() + mem_aux[i].substr(9,7);
          }

        }

        final.push_back(mem_aux[i]);
      }

      mem_aux.clear();
      mem_aux.insert(mem_aux.end(), init.begin(), init.end());
      mem_aux.insert(mem_aux.end(), stalls.begin(), stalls.end());    
      mem_aux.insert(mem_aux.end(), final.begin(), final.end());

    }


 ///dependencies_control allows you to detect dependencies found in instruction memory file

    void dependencies_control(fstream & memory_file)
    {
      string data;
      memory_file.seekg(0, ios::beg);

      while(not memory_file.eof())
      {

        memory_file >> data;

        if (not memory_file.good())
          break;

        aux_mem.push_back(data);
      }

      for(unsigned int i = 0; i < aux_mem.size(); ++i)
      {
        if(aux_mem[i] == "0000000000000000")
          continue;

        string r3 = aux_mem[i].substr(4,4);
        for (unsigned int j = i + 1; j < i + 4 and j < aux_mem.size(); ++j)
          {
            if(aux_mem[j] == "0000000000000000")
              continue;
            
            string r1 = aux_mem[j].substr(8,4);
            string r2 = aux_mem[j].substr(12,4);

            if(r3 == r1 or r3 == r2)
            {
              solve_depend(aux_mem, i, j);
              break;
            }
          }
      }

      memory_file.clear();
      memory_file.seekp(0, ios::beg);

      for(unsigned int i = 0; i < aux_mem.size(); i++)
        memory_file << aux_mem[i] << endl;

    }

    void search()
    {
      unsigned int search_address = address.read();
      sc_uint< instruction_length > read_instruction;
      string temp_instruction;

        do
        {
          memory_file.seekg(search_address*(instruction_length + 1), ios::beg);
          memory_file >> temp_instruction;
          bitset<5> bits(temp_instruction.substr(4,5));
          search_address = bits.to_ulong();
        }while(temp_instruction.substr(0,4) == "1111");


      for (int i = 0; i < instruction_length; ++i)
        if(temp_instruction[i] == '1')
          read_instruction[instruction_length - 1 - i] = 1;
        else
          read_instruction[instruction_length - 1 - i] = 0;

         instruction.write(read_instruction);
    }
};

#endif