
void DrawString(string String, float Multiplier, float TotalStrings, bool Selected)
{
	float YOffset = 10;
	float XOffset = 15;
	float TextHight = 7;
	float CharWidth = 5;
	float CharSpacing = 1;
	float RectOffset = 3;
	float WindowHeight = 53;
	float WindowWidth = 100;

	nxtDisplayStringAt((XOffset + RectOffset), ((WindowHeight - TextHight - YOffset * 2) / TotalStrings) * Multiplier + TextHight + (YOffset), String);

	if(Selected)
	{
		nxtDrawRect(XOffset - 1, ((WindowHeight - TextHight - YOffset * 2) / TotalStrings) * Multiplier + TextHight + (YOffset) + RectOffset, XOffset + RectOffset * 2 + strlen(String) * (CharWidth + CharSpacing), ((WindowHeight - TextHight - YOffset * 2) / TotalStrings) * Multiplier + TextHight + (YOffset) - TextHight - RectOffset + 1);
	}
}

void DrawMenu(string MenuTitle, string One, string Two, string Three, bool OneB, bool TwoB, bool ThreeB)
{
	eraseDisplay();

	nxtDisplayString(1, "%s", MenuTitle);
	DrawString(One, 0, 3, OneB);
	DrawString(Two, 1.5, 3, TwoB);
	DrawString(Three, 3, 3, ThreeB);
}

void DrawMenu(string MenuTitle, string One, string Two, bool OneB, bool TwoB)
{
	eraseDisplay();

	nxtDisplayString(1, "%s", MenuTitle);
	DrawString(One, .5, 3, OneB);
	DrawString(Two, 2.5, 3, TwoB);
}

int Menu(string Title, string FirstString, string SecondString)
{
	string One = FirstString;
	string Two = SecondString;

	bool SelectedListOne = true;
	bool SelectedListTwo = false;

	DrawMenu(Title, One, Two, SelectedListOne, SelectedListTwo);

	sleep(500);

	while(nNxtButtonPressed != 3)
	{
		if(nNxtButtonPressed == 2)
		{
			SelectedListOne = !SelectedListOne;
			SelectedListTwo = !SelectedListTwo;

			DrawMenu(Title, One, Two, SelectedListOne, SelectedListTwo);

			sleep(200);
		}
		else if(nNxtButtonPressed == 1)
		{
			SelectedListOne = !SelectedListOne;
			SelectedListTwo = !SelectedListTwo;

			DrawMenu(Title, One, Two, SelectedListOne, SelectedListTwo);

			sleep(200);
		}
	}

	if(SelectedListOne)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int Menu(string Title, string FirstString, string SecondString, string ThirdString)
{
	string One = FirstString;
	string Two = SecondString;
	string Three = ThirdString;

	bool SelectedList[3];
	SelectedList[0] = true;
	SelectedList[1] = false;
	SelectedList[2] = false;

	DrawMenu(Title, One, Two, Three, SelectedList[0], SelectedList[1], SelectedList[2]);

	sleep(500);

	while(nNxtButtonPressed != 3)
	{
		if(nNxtButtonPressed == 2)
		{
			int i;
			for(i = 0; SelectedList[i] != true; i++)
			{
			}

			SelectedList[0] = false;
			SelectedList[1] = false;
			SelectedList[2] = false;

			SelectedList[(i + 1) % 3] = true;

			DrawMenu(Title, One, Two, Three, SelectedList[0], SelectedList[1], SelectedList[2]);

			sleep(200);
		}
		else if(nNxtButtonPressed == 1)
		{
			int i;
			for(i = 0; SelectedList[i] != true; i++)
			{
			}

			SelectedList[0] = false;
			SelectedList[1] = false;
			SelectedList[2] = false;

			if((i - 1) % 3 >= 0)
			{
				SelectedList[(i - 1) % 3] = true;
			}
			else
			{
				SelectedList[2] = true;
			}

			DrawMenu(Title, One, Two, Three, SelectedList[0], SelectedList[1], SelectedList[2]);

			sleep(200);
		}
	}

	int i;
	for(i = 0; SelectedList[i] != true; i++)
	{
	}

	return i;
}
