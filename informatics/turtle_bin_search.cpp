#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>

int main()
{	
	// Open files
	std::ifstream input_file ("input.txt");
	if (!input_file.is_open())
	{
		std::cout << "Can't open input.txt\n";
		return 1;
	}
	
	std::ofstream output_file ("output.txt");
	if (!output_file.is_open())
	{
		std::cout << "Can't open output.txt\n";
		return 1;
	}
	
  long long v_max, eat_time, dand_num; 
  float last_dand_move_time;
  std::vector<long long> dand_grow_times;
  std::vector<float> dand_move_times;

  input_file >> v_max >> eat_time >> dand_num;
  
  dand_grow_times.resize(dand_num);
  dand_move_times.resize(dand_num);

  float time_sum = 0;
  long long dist;

  for (int i = 0; i < dand_num; i++)
  {    
    input_file >> dist;

    dand_move_times[i] = float(dist) / v_max;
	
    if (i == dand_num-1)
      last_dand_move_time = dand_move_times[i];

    dand_move_times[i] -= time_sum;

    time_sum += dand_move_times[i];

    char trash, hours_1, hours_2, mins_1, mins_2;
    input_file >> hours_1 >> hours_2 >> trash >> mins_1 >> mins_2;
    dand_grow_times[i] = ((hours_1-'0')*10 + (hours_2-'0'))*60 + (mins_1-'0')*10 + (mins_2-'0');
  }    

  float l = 0;
  float r = dand_grow_times[dand_num-1];

  float start_time;
  float there_time;

  while ( r - l > 0.1)
  {
    start_time = (l + r) / 2;

    there_time = start_time;

    for (int i = 0; i < dand_num - 1; i++)
    {
      there_time += dand_move_times[i];

      if (there_time >= dand_grow_times[i])
        there_time += eat_time;
    }

	there_time += dand_move_times[dand_num - 1];

    if (there_time >= dand_grow_times[dand_num-1])
      r = start_time;
    else
      l = start_time;
  }
  
  /*
  float part_time = 2 * last_dand_move_time - std::floor(2 * last_dand_move_time);
  there_time = r - part_time;

  for (int i = 0; i < dand_num - 1; i++)
  {
    there_time += dand_move_times[i];

    if (there_time >= dand_grow_times[i])
      there_time += eat_time;
  }

  there_time += dand_move_times[dand_num - 1];

  if (there_time >= dand_grow_times[dand_num-1])
    r -= part_time;
  */
  
  
  long long end_time = (long long) std::ceil (2 * last_dand_move_time + r + eat_time * dand_num);
    
	output_file << (end_time / 60) / 10 << (end_time / 60) % 10 << ":" 
              << (end_time % 60) / 10 << (end_time % 60) % 10 << std::endl;		 		
	
	input_file.close();	
	output_file.close();
	
	return 0;
}
