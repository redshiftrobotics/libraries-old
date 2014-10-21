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

Values IR_OneValue;
Values IR_TwoValue;

const int Threashold = 100;

int IR_OneDegree()
{
	//the first IR sensor
	if(IR_OneValue.B > Threashold && IR_OneValue.C < Threashold)
	{
		return 50;
	}
	else if(IR_OneValue.B > Threashold && IR_OneValue.C > Threashold && IR_OneValue.D < Threashold)
	{
		return 20;
	}
	else if(IR_OneValue.C > Threashold && IR_OneValue.B < Threashold && IR_OneValue.D < Threashold)
	{
		return 0;
	}
	else if(IR_OneValue.C > Threashold && IR_OneValue.B > Threashold && IR_OneValue.D > Threashold)
	{
		return 0;
	}
	else if(IR_OneValue.C > Threashold && IR_OneValue.D > Threashold && IR_OneValue.B < Threashold)
	{
		return -20;
	}
	else if(IR_OneValue.D > Threashold && IR_OneValue.C < Threashold)
	{
		return -50
	}



	return -1;
}


int IR_TwoDegree()
{
	//the first IR sensor
	if(IR_TwoValue.B > Threashold && IR_TwoValue.C < Threashold)
	{
		return -50;
	}
	else if(IR_TwoValue.B > Threashold && IR_TwoValue.C > Threashold && IR_TwoValue.D < Threashold)
	{
		return -20;
	}
	else if(IR_TwoValue.C > Threashold && IR_TwoValue.B < Threashold && IR_TwoValue.D < Threashold)
	{
		return 0;
	}
	else if(IR_TwoValue.C > Threashold && IR_TwoValue.B > Threashold && IR_TwoValue.D > Threashold)
	{
		return 0;
	}
	else if(IR_TwoValue.C > Threashold && IR_TwoValue.D > Threashold && IR_TwoValue.B < Threashold)
	{
		return 20;
	}
	else if(IR_TwoValue.D > Threashold && IR_TwoValue.C < Threashold)
	{
		return 50
	}



	return -1;
}

void IR_Update()
{
	HTIRS2readAllACStrength(IROne, IR_OneValue.A, IR_OneValue.B, IR_OneValue.C, IR_OneValue.D, IR_OneValue.E);
	HTIRS2readAllACStrength(IRTwo, IR_TwoValue.A, IR_TwoValue.B, IR_TwoValue.C, IR_TwoValue.D, IR_TwoValue.E);
}
