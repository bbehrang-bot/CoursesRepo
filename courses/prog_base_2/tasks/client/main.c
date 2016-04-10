#include <stdio.h>
#include <stdlib.h>
#include <winsock.h>
#define BUFFER_SIZE 2000
void getSecret(char *fullAddr, SOCKET recvSocket, char *secretOut)
{
	int recvSize;
	char getMessage[200];
	char buffer[BUFFER_SIZE];

	sprintf(getMessage, "GET %s HTTP/1.1\r\n\r\n", fullAddr);
	if (send(recvSocket, getMessage, strlen(getMessage), 0)<0)
	{
		puts("Send failed");
		return;
	}

	if ((recvSize = recv(recvSocket, buffer, BUFFER_SIZE, 0)) == SOCKET_ERROR)
	{
		puts("Recv Failed");
		return;
	}
	buffer[recvSize] = '\0';
	char *secretLine = "secret=";
	char *secret = strstr(buffer, secretLine);
	int secPos = 0;
	while (secret[secPos] != '=')
		secPos++;
	secPos++;

	int secOutIndex = 0;
	while (secPos <= strlen(secret))
	{
		secretOut[secOutIndex] = secret[secPos];
		secPos++;
		secOutIndex++;
	}
	secretOut[secOutIndex] = '\0';
}

void getArray(char *fullAddr, SOCKET recvSocket, int arrOut[100][100],int *rows,int *cols)
{
	int recvSize;
	char getMessage[200];
	char buffer[BUFFER_SIZE];


	sprintf(getMessage, "GET %s HTTP/1.1\r\n\r\n", fullAddr);
	if (send(recvSocket, getMessage, strlen(getMessage), 0)<0)
	{
		puts("Send failed");
		return 1;
	}
	if ((recvSize = recv(recvSocket, buffer, BUFFER_SIZE, 0)) == SOCKET_ERROR)
	{
		puts("Recv Failed");
		return 1;
	}
	buffer[recvSize] = '\0';
	puts(buffer);

	char *arrLine = "Content-Length";
	char *arr = strstr(buffer, arrLine);
	int contentSize;
	sscanf(arr, "Content-Length: %i", &contentSize);

	while (arr[0] != '\n')
		arr++;
	arr += 3;
	int val;
	int arrOutIndex = 0;
	char *token = strtok(arr, "\n");
	int sum = 0;
	puts("");
	int row = 0;
	char arrRow[BUFFER_SIZE];
	int str_rowIndex = 0;
	int tmpIndex = 0;
	char tmp[100];
	while (token != NULL)
	{
		strcpy(arrRow, token);
		val = 0;
		arrOutIndex = 0;
		while (str_rowIndex < strlen(arrRow))
		{
		    strcpy(tmp,"");
            tmpIndex = 0;
			while (arrRow[str_rowIndex] != ' ')
			{
				tmp[tmpIndex] = arrRow[str_rowIndex];
				tmp[tmpIndex+1] = '\0';
				str_rowIndex++;
				tmpIndex++;
			}
			str_rowIndex++;
			sscanf(tmp, "%i", &val);
			arrOut[row][arrOutIndex] = val;
			arrOutIndex++;
		}
		str_rowIndex = 0;
		printf("\n");
		row++;
		token = strtok(NULL, "\n");
	}
	*rows = row;
	*cols = arrOutIndex;
}
int postResult(char *result,char *fullAddr,SOCKET recvSocket,char * response)
{
    char rcvResult[100];
    int rcvSize;
    sprintf(rcvResult,"result=%s",result);
    rcvResult[strlen(rcvResult) - 1] = '\0';
    char post[200];
    sprintf(post, "POST %s HTTP/1.1\r\n"
            "Content-length: %d\r\n\r\n"
            "%s", fullAddr, strlen(rcvResult), rcvResult);
    send(recvSocket,post,strlen(post),0);
    rcvSize = recv(recvSocket,response,BUFFER_SIZE,0);
    return rcvSize;
}

int rowSum(int rowNum,int rows,int cols,int arr[100][100])
{
    int i,j,sum=0;
    for(i=0;i<cols;i++)
    {
        sum+= arr[rowNum][i];
    }
    return sum;
}
void findBiggestRow(int rows,int cols,int arr[100][100],char *result){
    printArray(rows,cols,arr);
    int i,j,tmpSum;
    int biggestSum = rowSum(0,rows,cols,arr);
    int biggestRow=0;
    for(i=1;i<rows;i++)
    {
        tmpSum = rowSum(i,rows,cols,arr);
        if(tmpSum > biggestSum)
        {
            biggestRow = i;
        }
    }
    strcpy(result,"");
    for(i=0;i<cols;i++)
    {
        char tmp[10];
        itoa(arr[biggestRow][i], tmp, 10);
        strcat(tmp, " ");
        strcat(result, tmp);

    }
    result[strlen(result)] = '\0';

}
void printArray(int rows,int cols,int arr[100][100])
{
    int i=0;
	int j=0;
    for(i=0;i<rows;i++)
    {
        for(j=0;j<cols;j++)
            printf("%i  ",arr[i][j]);
    printf("\n");
    }
}

void initArray(int arr[100][100])
{
    int i,j;
    for(i=0;i<100;i++)
        for(j=0;j<100;j++)
            arr[i][j] = 0;
}


int main()
{
	WSADATA data;
	SOCKET recvSocket;
	struct sockaddr_in recvAddr;
	char* hostname = "pb-homework.appspot.com";
	char *var = "/var/10";
	char fullAddr[1000];
	char ip[100];
	char buffer[BUFFER_SIZE];
	struct hostent *he;
	struct in_addr **addr_list;
	int i;
	if (WSAStartup(MAKEWORD(2, 2), &data) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		return 1;
	}

	if ((recvSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
	{
		printf("Could not create socket : %d", WSAGetLastError());
	}

	if ((he = gethostbyname(hostname)) == NULL)
	{
		printf("gethostbyname failed : %d", WSAGetLastError());
		return 1;
	}

	addr_list = (struct in_addr**) he->h_addr_list;
	for (i = 0; addr_list[i] != NULL; i++)
	{
		strcpy(ip, inet_ntoa(*addr_list[i]));
	}
	printf("%s resolved to : %s\n", hostname, ip);


	recvAddr.sin_addr.s_addr = inet_addr(ip);
	recvAddr.sin_family = AF_INET;
	recvAddr.sin_port = htons(80);

	if (connect(recvSocket, (struct sockaddr*)&recvAddr, sizeof(recvAddr)) <0)
	{
		printf("connection failed : %d", WSAGetLastError());
	}
	strcpy(fullAddr, hostname);
	strcat(fullAddr, var);

	getSecret(fullAddr, recvSocket, buffer);
	printf("Secret received from server : %s\n", buffer);
	sprintf(fullAddr, "%s?secret=%s", fullAddr, buffer);
	int arr[100][100];
	initArray(arr);
	int rows=0;
	int cols=0;
	getArray(fullAddr, recvSocket, arr,&rows,&cols);
    char result[BUFFER_SIZE];
    findBiggestRow(rows,cols,arr,result);
     strcpy(fullAddr, hostname);
    strcat(fullAddr, var);
    int recvSize = postResult(result,fullAddr,recvSocket,buffer);
    buffer[recvSize] = '\0';
    puts("");
    puts(buffer);

	return 0;
}
