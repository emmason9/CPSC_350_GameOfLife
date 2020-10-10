//process files class

#include "FileProcessor.h"

//deafult constuctor
  FileProcessor::FileProcessor(){
    //everything is declared in header
  }

//making sure all the fstream objects get closed at the end
  FileProcessor :: ~FileProcessor(){
    if(Reader.is_open()){
      Reader.close();
    }
    if(Writer.is_open()){
      Writer.close();
    }
    if(Appender.is_open()){
      Appender.close();
    }
  }

//opens ifstream file that reads given file name
  bool FileProcessor::OpenReaderFile(string FileName){
    Reader.open(FileName);
    if (!Reader.is_open()){
  //    cout<< "reader is not open" <<endl;
      return false;
    }
    return true;

  }
//opens ofstream file that writes to given file name
  bool FileProcessor::OpenWriterFile(string FileName){
    Writer.open(FileName);
    if(!Writer.is_open()){
  //    cout<<"writer is not open"<<endl;
      return false;
    }
    return true;
  }
//opens ofstream file that appends to given file name
  bool FileProcessor::OpenAppenderFile(string FileName){
    Appender.open(FileName, ios::app);
    if(!Appender.is_open()){
//      cout<<"Appender is not open"<<endl;
      return false;
    }
    return true;
  }
