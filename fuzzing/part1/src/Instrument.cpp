#include "Instrument.h"


using namespace llvm;

namespace instrument {

static const char *SanitizerFunctionName = "__dbz_sanitizer__";
static const char *CoverageFunctionName = "__coverage__";

/*
 * Implement divide-by-zero sanitizer.
 */
void instrumentSanitizer(Module *M, Function &F, Instruction &I) {

  /* Add your code here 
  Implement the instrumentSanitizer function to insert a __dbz_sanitizer__ check for
  a supplied Instruction
  */
    if(I.getOpcode() == 19) {
      //get variables
      auto Debug = I.getDebugLoc();
      auto num = I.getNumOperands();
      auto yValue = I.getOperand(0);
      auto xValue = I.getOperand(1);
      auto line = llvm::ConstantInt::get(llvm::Type::getInt32Ty(M->getContext()),Debug.getLine());
      auto col = llvm::ConstantInt::get(llvm::Type::getInt32Ty(M->getContext()),Debug.getCol());
        
      // Create the arguments vector from the my argument list
      SmallVector<Type *, 3> ArgTys; 
      ArgTys.push_back(Type::getInt32Ty(M->getContext())); 
      ArgTys.push_back(Type::getInt32Ty(M->getContext()));
      ArgTys.push_back(Type::getInt32Ty(M->getContext()));

      // Just get a void return type
      Type *RetTy = Type::getVoidTy(M->getContext()); 

      // Create a new function with MyArgs as arguments
      Constant *C = M->getOrInsertFunction(SanitizerFunctionName, FunctionType::get(RetTy, ArgTys, false));
      Function* sanitizer = cast<Function>(C);
    
      SmallVector<Value*, 3> Args;
      Args.push_back(xValue);
      Args.push_back(line);
      Args.push_back(col);

      //insert function sanitizer before instruction I
      //outs() << "called y value: " << F.getInstructionCount()<< "\n";

      CallInst *NewCall = CallInst::Create(sanitizer,Args, "", (Instruction *)(&I));
        //outs() << "called y value: " << F.getInstructionCount()<< "\n";
    }

}

/*
 * Implement code coverage instrumentation.
 */
void instrumentCoverage(Module *M, Function &F, Instruction &I) {
  /* Add your code here */
  //when running this instruction which has debug info, get instruction line and col, call coverage method
  auto Debug = I.getDebugLoc();
    if(Debug) {

      //get variables
      
      auto line = llvm::ConstantInt::get(llvm::Type::getInt32Ty(M->getContext()),Debug.getLine());
      auto col = llvm::ConstantInt::get(llvm::Type::getInt32Ty(M->getContext()),Debug.getCol());
        
      // Create the arguments vector from the my argument list
      SmallVector<Type *, 2> ArgTys; 
      ArgTys.push_back(Type::getInt32Ty(M->getContext())); 
      ArgTys.push_back(Type::getInt32Ty(M->getContext()));
      

      // Just get a void return type
      Type *RetTy = Type::getVoidTy(M->getContext()); 

      // Create a new function with MyArgs as arguments
      Constant *C = M->getOrInsertFunction(CoverageFunctionName, FunctionType::get(RetTy, ArgTys, false));
      Function* coverage = cast<Function>(C);
    
      SmallVector<Value*, 2> Args;
      Args.push_back(line);
      Args.push_back(col);

      //insert function sanitizer before instruction I
      //outs() << "called y value: " << F.getInstructionCount()<< "\n";

      CallInst *NewCall = CallInst::Create(coverage,Args, "", (Instruction *)(&I));
        //outs() << "called y value: " << F.getInstructionCount()<< "\n";
     }
}

bool Instrument::runOnFunction(Function &F) {
  for (inst_iterator I = inst_begin(F), E = inst_end(F); I != E; ++I){
    auto M = F.getParent();
    instrumentSanitizer(M,F,(*I));
    instrumentCoverage(M,F,(*I));
  }
  
  
  return true;
  
}

char Instrument::ID = 1;
static RegisterPass<Instrument>
    X("Instrument", "Instrumentations for Dynamic Analysis", false, false);

} // namespace instrument
