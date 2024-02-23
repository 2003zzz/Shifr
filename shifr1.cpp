#include <iostream>
#include <fstream>
#include <locale.h>

using namespace std;

int main()
{
    setlocale(LC_ALL, "rus");


    ifstream inputFile("infile.txt", ios::binary);
    ofstream middleFile("middle.txt", ios::binary);
    ofstream outputFile("outfile.txt", ios::binary);

    middleFile.clear();
    outputFile.clear();

    const unsigned long blockSize = 64;
    char buffer[blockSize];
    bool stop = false;
    
    while (!inputFile.eof()) 
    {
        inputFile.read(buffer, blockSize); // Чтение блока данных

        streamsize bytesRead = inputFile.gcount(); // Получение количества реально прочитанных байт

        cout << "Размер исходника: " << inputFile.gcount() << " байт\nНе хватило до 64: " << (streamsize(64) - bytesRead) <<" байт\n";

        if (bytesRead < blockSize)
        {
            for (streamsize i = bytesRead; i < blockSize; ++i)
            {
                buffer[i] = '0';
            }
            buffer[bytesRead] = '1';

            middleFile.write(buffer,blockSize);// заносим в промежуточный 

            for (streamsize i = 0; i < bytesRead; ++i)
            {
                if (buffer[i] == '1')
                {
                    stop = true;
                    break;
                }
            }

            if (!stop) 
            {
                outputFile.write(buffer, bytesRead);
            }

            if (stop) // Прекращение чтения после обнаружения управляющего символа "1"
            {
                break;
            }
        }

    }
    outputFile.seekp(0, std::ios::end);
    streampos fileSize = outputFile.tellp();
    std::cout << "Размер выходного: " << fileSize << " байт\n\n\n\n";
    inputFile.close();
    outputFile.close();
    return 0;
}
