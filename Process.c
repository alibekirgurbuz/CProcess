#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main()
{
	PROCESS_INFORMATION processInfo1, processInfo2;
	STARTUPINFO startupInfo1, startupInfo2;
	DWORD exitCode1, exitCode2;

	ZeroMemory(&startupInfo1, sizeof(startupInfo1));
	startupInfo1.cb = sizeof(startupInfo1);

	if (!CreateProcess(NULL, "notepad.exe", NULL, NULL, FALSE, 0, NULL, NULL, &startupInfo1, &processInfo1))
	{
		printf("CreateProcess failed for child 1\n");
		return 1;
	}

	FILE *file1 = fopen("notepad1.txt", "w");
	if (file1 == NULL)
	{
		perror("Failed to open file for writing");
		return 1;
	}
	int random_num1 = rand() % 100 + 1;
	fprintf(file1, "Rastgele Sayı: %d\n", random_num1);
	fclose(file1);

	WaitForSingleObject(processInfo1.hProcess, INFINITE);
	GetExitCodeProcess(processInfo1.hProcess, &exitCode1);
	printf("Child 1 exited with code: %lu\n", exitCode1);

	ZeroMemory(&startupInfo2, sizeof(startupInfo2));
	startupInfo2.cb = sizeof(startupInfo2);

	if (!CreateProcess(NULL, "notepad.exe", NULL, NULL, FALSE, 0, NULL, NULL, &startupInfo2, &processInfo2))
	{
		printf("CreateProcess failed for child 2\n");
		return 1;
	}

	FILE *file2 = fopen("notepad2.txt", "w");
	if (file2 == NULL)
	{
		perror("Failed to open file for writing");
		return 1;
	}
	int random_num2 = rand() % 100 + 1;
	fprintf(file2, "Rastgele Sayı: %d\n", random_num2);
	fclose(file2);

	WaitForSingleObject(processInfo2.hProcess, INFINITE);
	GetExitCodeProcess(processInfo2.hProcess, &exitCode2);
	printf("Child 2 exited with code: %lu\n", exitCode2);

	FILE *resultFile = fopen("result.txt", "w");
	if (resultFile == NULL)
	{
		perror("Failed to open result file for writing");
		return 1;
	}

	fprintf(resultFile, "Child 1'in Sayısı: %d\n", random_num1);
	fprintf(resultFile, "Child 2'nin Sayısı: %d\n", random_num2);
	fprintf(resultFile, "Toplam: %d\n", random_num1 + random_num2);
	fclose(resultFile);

	system("start notepad.exe result.txt");

	return 0;
}
