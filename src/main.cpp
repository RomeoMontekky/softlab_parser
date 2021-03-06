﻿#include "exceptions.h"
#include "parser.h"

#include <exception>
#include <iostream>

int main(int argc, char* argv[])
{
   if (argc != 3)
   {
      std::cout << "SoftLab Parser utility. Copyright (c) 2016 Roman Lapitsky." << std::endl
                << "Usage: softlab_parser.exe <INPUT_FILE> <OUTPUT_FILE>" << std::endl;
      return 0;
   }

   try
   {   
      SoftLab::Parser parser;
      parser.Parse(argv[1]);
      parser.SaveTo(argv[2]);
   }
   catch (const SoftLab::SyntaxException& ex)
   {
      std::cerr << "Syntax error at line " << ex.GetLineNumber() <<  ": "
                << ex.GetDescription() << std::endl;
      return -1;
   }
   catch (const SoftLab::Exception& ex)
   {
      std::cerr << "Error: " << ex.GetDescription() << std::endl;
      return -2;
   }
   catch (const std::exception& ex)
   {
      std::cerr << "System error: " << ex.what() << std::endl;
      return -3;
   }
   catch (...)
   {
      std::cerr << "Internal error." << std::endl;
      return -4;
   }
   
   return 0;
}
