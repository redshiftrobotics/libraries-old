#include "drivers\hitechnic-irseeker-v2.h"

#warn "Unless you are a member of 2856, do not use this library! It does not use generalized functions."
#warn "A 2856 member should come integrate this library into their team-specific repository."

typedef struct
{
  int A;
  int B;
  int C;
  int D;
  int E;
} Values;

Values IR_LeftValue;
Values IR_RightValue;

const int Threashold = 100;

int IR_OneDegree()
{
	//the first IR sensor
	if(IR_LeftValue.B > Threashold && IR_LeftValue.C < Threashold)
	{
		return 50;
	}
	else if(IR_LeftValue.B > Threashold && IR_LeftValue.C > Threashold && IR_LeftValue.D < Threashold)
	{
		return 20;
	}
	else if(IR_LeftValue.C > Threashold && IR_LeftValue.B < Threashold && IR_LeftValue.D < Threashold)
	{
		return 0;
	}
	else if(IR_LeftValue.C > Threashold && IR_LeftValue.B > Threashold && IR_LeftValue.D > Threashold)
	{
		return 0;
	}
	else if(IR_LeftValue.C > Threashold && IR_LeftValue.D > Threashold && IR_LeftValue.B < Threashold)
	{
		return -20;
	}
	else if(IR_LeftValue.D > Threashold && IR_LeftValue.C < Threashold)
	{
		return -50;
	}



	return -1;
}


int IR_TwoDegree()
{
	//the first IR sensor
	if(IR_RightValue.B > Threashold && IR_RightValue.C < Threashold)
	{
		return -50;
	}
	else if(IR_RightValue.B > Threashold && IR_RightValue.C > Threashold && IR_RightValue.D < Threashold)
	{
		return -20;
	}
	else if(IR_RightValue.C > Threashold && IR_RightValue.B < Threashold && IR_RightValue.D < Threashold)
	{
		return 0;
	}
	else if(IR_RightValue.C > Threashold && IR_RightValue.B > Threashold && IR_RightValue.D > Threashold)
	{
		return 0;
	}
	else if(IR_RightValue.C > Threashold && IR_RightValue.D > Threashold && IR_RightValue.B < Threashold)
	{
		return 20;
	}
	else if(IR_RightValue.D > Threashold && IR_RightValue.C < Threashold)
	{
		return 50;
	}



	return -1;
}

void IR_Update()
{
	HTIRS2readAllACStrength(IROne, IR_LeftValue.A, IR_LeftValue.B, IR_LeftValue.C, IR_LeftValue.D, IR_LeftValue.E);
	HTIRS2readAllACStrength(IRTwo, IR_RightValue.A, IR_RightValue.B, IR_RightValue.C, IR_RightValue.D, IR_RightValue.E);
}
