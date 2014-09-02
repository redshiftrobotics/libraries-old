bool Bluetooth_Initialized = false;

void Bluetooth_Initialize()
{
	if(!Bluetooth_Initialized)
	{
		Bluetooth_Initialized = true;
		while(bQueuedMsgAvailable())
		{
			ClearMessage();
		}
	}
}

bool Bluetooth_MessageAvailable()
{
	return bQueuedMsgAvailable();
}

bool Bluetooth_ReadMessage(int* One, int* Two, int* Three)
{
	Bluetooth_Initialize();

	if(bQueuedMsgAvailable())
	{
		eraseDisplay();

		nxtDisplayString(1, "%i", messageParm[0]);
		nxtDisplayString(2, "%i", messageParm[1]);
		nxtDisplayString(3, "%i", messageParm[2]);

		*One = messageParm[0];
		*Two = messageParm[1];
		*Three = messageParm[2];

		ClearMessage();

		return true;
	}
	else
	{
		return false;
	}
}
