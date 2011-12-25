/*
   Copyright (c) 2011 Chernihiv State Technological University

   Permission is hereby granted, free of charge, to any person obtaining a
   copy of this software and associated documentation files (the "Software"),
   to deal in the Software without restriction, including without limitation
   the rights to use, copy, modify, merge, publish, distribute, sublicense,
   and/or sell copies of the Software, and to permit persons to whom the
   Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
   FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
   DEALINGS IN THE SOFTWARE.
*/

#include "AST_FunctionCall.h"

lvalue::AST_FunctionCall::AST_FunctionCall(lvalue::LValueBuilder &builder,
        AST_Identifier &id,
        ExpressionList &arguments) 
        : AST_Node(builder), id(id), arguments(arguments)
{
    
  llvm::Function *function = builder.module->getFunction(id.name.c_str());
	if (function == NULL) {
		//std::cerr << "no such function " << id.name << std::endl;
	}
	std::vector<llvm::Value*> args;
	ExpressionList::const_iterator it;
	for (it = arguments.begin(); it != arguments.end(); it++) {
		args.push_back((**it).emmitCode());
	}
	llvm::CallInst *call = builder.CreateCall(function, args.begin(), args.end(), "");
	//std::cout << "Creating method call: " << id.name << std::endl;
	return call;
}