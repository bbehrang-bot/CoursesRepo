const char * process(char * resultStr, const char * textLines[], int linesNum, const char * extraStr)
{

	int i = 0;
	int j = 0;
	int k = 0;
	int lineNumIndex = 0;
	int counter = 0;
	int lineLength = 0;

	int z = 0;
	int x = 0;


	for (i; i<linesNum; i++)
	{

		counter = 0;
		lineLength = strlen(textLines[i]);


		for (j = 0; j < lineLength; j++)
		{
			if (textLines[i][j] != ' '&&textLines[i][j] != '\0')
				counter++;

		}

		if (counter<10)
		{



			resultStr[k] = i + '0';
			k++;
			resultStr[k] = ' ';
			k++;
				for (x = 0; x < lineLength; x++)
				{
					resultStr[k] = textLines[i][x];
					k++;
				}
				resultStr[k] = ',';
				k++;


		}
	}

	return resultStr;





}