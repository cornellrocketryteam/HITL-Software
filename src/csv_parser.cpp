#include <cstdio>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <fstream>

std::vector<std::string> SplitCSV(const std::string &data, char separator, char delimiter)
{
  std::vector<std::string> Values;
  std::string Val = "";
  bool VDel = false; // Is within delimiter?
  size_t CDel = 0; // Delimiters counter within delimiters.
  const char *C = data.c_str();
  size_t P = 0;
  do
  {
    if ((Val.length() == 0) && (C[P] == delimiter))
    {
      VDel = !VDel;
      CDel = 0;
      P++;
      continue;
    }
    if (VDel)
    {
      if (C[P] == delimiter)
      {
        if (((CDel % 2) == 0) && ( (C[P+1] == separator) || (C[P+1] == 0) || (C[P+1] == '\n') || (C[P+1] == '\r') ))
        {
          VDel = false;
          CDel = 0;
          P++;
          continue;
        }
        else
          CDel++;
      }
    }
    else
    {
      if (C[P] == separator)
      {
        Values.push_back(Val);
        Val = "";
        P++;
        continue;
      }
      if ((C[P] == 0) || (C[P] == '\n') || (C[P] == '\r'))
        break;
    }
    Val += C[P];
    P++;
  } while(P < data.length());

  Values.push_back(Val);
  return Values;
}

bool ReadCsv(const std::string &fname, std::vector<std::vector<std::string>> &data,
  char separator = ',', char delimiter = '\"')
{
  bool Ret = false;
  std::ifstream FCsv(fname);
  if (FCsv)
  {
    FCsv.seekg(0, FCsv.end);
    size_t Siz = FCsv.tellg();
    if (Siz > 0)
    {
      FCsv.seekg(0);
      data.clear();
      std::string Line;
      while (getline(FCsv, Line, '\n'))
        data.push_back(SplitCSV(Line, separator, delimiter));
      Ret = true;
    }
    FCsv.close();
  }
  return Ret;
}

// int main(int argc, char *argv[])
// {
//   std::vector<std::vector<std::string>> Data;
//   ReadCsv("fsample.csv", Data);
//   return 0;
// }


