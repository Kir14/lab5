#include <iostream> 
#include <windows.h>
#include <iomanip>


using namespace std;

int mas1[10], mas2[10], mas3[10];

int thread01();
int thread02();


int main() 
{ 
	
	HANDLE hMutex = CreateMutex(NULL, FALSE, "MyMutex"); 
	if (hMutex == NULL) cout << "Create mutex failed" << GetLastError() << endl;

	HANDLE hTh01 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread01, NULL, 0, NULL);
	if (hTh01 == NULL) return GetLastError();
	

	HANDLE hTh02 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread02, NULL, 0, NULL);
	if (hTh02 == NULL) return GetLastError();

	cin.get();


	CloseHandle(hMutex); 

	CloseHandle(hTh01); 
	CloseHandle(hTh02); 
	return 0; 
}


int thread01()
{ 
	srand(static_cast<unsigned int>(time(0)));

	HANDLE hMutex01 = OpenMutex(SYNCHRONIZE, FALSE, "MyMutex");
	if (hMutex01 == NULL) cout << "Open mutex01 failed" << GetLastError() << endl;
	
	WaitForSingleObject(hMutex01, INFINITE);
	
	for (int i = 0;i < 10; i++)
	{
		LONG k = rand() % 3;
		mas1[i] = k;
		k =  rand() % 3;
		mas2[i] = k;
		k =  rand() % 3;
		mas3[i] = k;
	}
	cout << endl;
	cout << "thread 1" << endl;
	cout << setw(5) << "mas1" << setw(5) << "mas2" << setw(5) << "mas3" << endl;
	for (int i = 0; i < 10; i++)
	{
		cout << setw(5) << mas1[i] << setw(5) << mas2[i] << setw(5) << mas3[i] << endl;
	}
	ReleaseMutex(hMutex01);	
	CloseHandle(hMutex01);
	return 0;
}



int thread02() 
{
	srand(static_cast<unsigned int>(time(0)));

	HANDLE hMutex02 = OpenMutex(SYNCHRONIZE, FALSE, "MyMutex");
	if (hMutex02 == NULL) cout << "Open mutex02 failed" << GetLastError() << endl;
	
	WaitForSingleObject(hMutex02, INFINITE);

	for (int i = 0; i < 10; i++)
	{
		if (mas1[i] == 0)
		{
			LONG k =1+ rand() % 2;
			mas1[i] = k;
		}
		if (mas2[i] == 0)
		{
			LONG k =1+ rand() % 2;
			mas2[i] = k;
		}
		if (mas3[i] == 0)
		{
			LONG k =1+ rand() % 2;
			mas3[i] = k;
		}
	}
	cout << endl;
	cout << endl;
	cout << "thread 2" << endl;
	cout << setw(5) << "mas1" << setw(5) << "mas2" << setw(5) << "mas3" << endl;
	for (int i = 0; i < 10; i++)
	{
		cout << setw(5) << mas1[i] << setw(5) << mas2[i] << setw(5) << mas3[i] << endl;
	}
	ReleaseMutex(hMutex02);

	CloseHandle(hMutex02);
	return 0;
}