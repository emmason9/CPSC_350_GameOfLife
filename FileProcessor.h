//FileProcessor header files

#include <iostream>
#include <fstream>
using namespace std;

class FileProcessor{
  public:
    ifstream Reader;
    ofstream Writer;
    ofstream Appender;

    FileProcessor();
    ~FileProcessor();

    bool OpenReaderFile(string fileName);
    bool OpenWriterFile(string fileName);
    bool OpenAppenderFile(string fileName);

};
