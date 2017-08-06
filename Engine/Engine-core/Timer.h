#pragma once
#include <Windows.h>
class Timer
{
   private:
	   LARGE_INTEGER m_Start;
	   LARGE_INTEGER frequency;
	   LARGE_INTEGER current;
   public:
	   Timer()
	   {
		   
		   reset();
		 
		   
	   }
	   void reset()
	   {
		   QueryPerformanceFrequency(&frequency);
		   QueryPerformanceCounter(&m_Start);
	   }

	   double elapsed()
	   {
		   
		   QueryPerformanceFrequency(&current);
		 

		   return  static_cast<double>(current.QuadPart - m_Start.QuadPart) / frequency.QuadPart;

	   }

	 

	  

		   
		   
	   

};
