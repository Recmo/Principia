#pragma once
#include <llvm/Pass.h>
#include <llvm/IR/BasicBlock.h>

class LlvmStoreLoadCombine: public llvm::BasicBlockPass
{
public:
	explicit LlvmStoreLoadCombine();
	virtual ~LlvmStoreLoadCombine();
	static char ID;
	virtual bool runOnBasicBlock(llvm::BasicBlock &BB);
};
