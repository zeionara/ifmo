#include <stdio.h>
#include <errno.h>
#include <iostream>
#define BUF_SIZE 256

using namespace std;

int copyByCLib(const char* src, const char* dest){
  FILE *in_file, *out_file;
  char rec[BUF_SIZE];
  size_t bytes_in, bytes_out;

  in_file = fopen(src,"rb");

  if (in_file == NULL){
    return 1;
  }

  out_file = fopen(dest,"wb");
  if (out_file == NULL){
    return 1;
  }

  while((bytes_in = fread(rec, 1, BUF_SIZE, in_file))>0){
    bytes_out = fwrite(rec, 1, bytes_in, out_file);
    if (bytes_out != bytes_in){
      return 2;
    }
  }

  fclose(in_file);
  fclose(out_file);

  return 0;
}

int main(int argc, char* argv[]){
  if (argc != 3){
    cout << "Usage : cpc src dest" << endl;
    return 1;
  }

  int result = copyByCLib(argv[1],argv[2]);

  switch (result){
    case 0:
      cout << "Succesfully done!" << endl;
      return 0;
    case 1:
      cout << "Error when opening files" << endl;
      return 1;
    case 2:
      cout << "Internal error when copying" << endl;
      return 1;
  }
}
