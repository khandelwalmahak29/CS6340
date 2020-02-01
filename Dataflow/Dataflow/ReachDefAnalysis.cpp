#include "DataflowAnalysis.h"
#include "llvm/IR/Instructions.h"
#include <list>

namespace dataflow{
    struct ReachDefAnalysis: public DataflowAnalysis{
        static char ID;
        ReachDefAnalysis() : DataflowAnalysis(ID){}
        
    protected:
        /**
         *  Implement your analysis in this function. Store your results in DataflowAnalysis::inMap and
         *  DataflowAnalysis:outMap.
         */
        void doAnalysis(Function &F) override{
            // errs() << "Function " << F.getName() << '\n';
	SetVector<Instruction*> changedSet;
	int cnt = 0;
        for (inst_iterator I = inst_begin(F), E= inst_end(F); I != E; ++I){
		changedSet.insert(&(*I));
		cnt ++;
  	  //	errs() << "1 Instruction: " << isDef(&(*I)) << " "<< &(*I) << " : " << *I << '\n';
		/*
	    if (isDef(&(*I))) { // a set of locally available definitions;
		if (auto SI = dyn_cast<AllocaInst>(&(*I))) {
             	   errs() << "Alloca Instruction: " <<  SI << " : " << *SI << '\n';
		   } else if (auto SI = dyn_cast<LoadInst>(&(*I))) {
  		   errs() << "Load Define Instruction: " << SI << " : " << *SI << "Op[0]: " << SI->getOperand(0) << '\n';
		   } else {

  		   errs() << "Define Instruction: " << &(*I) << " : " << *I << '\n';
		   }
	    } else if (auto SI = dyn_cast<StoreInst>(&(*I))) {
             	   errs() << "Store Instruction: " <<  SI->getOperand(1) << " : " << *SI << '\n';
		   } else {

  		   errs() << "Instruction: " << &(*I) << " : " << *I << '\n';
		   }
		   */
	 }

 //	   errs() << "changedSet.size(): " << changedSet.size()  << " cnt: " << cnt << '\n';
	SetVector<Value*> Gen, tmp;

	while(!changedSet.empty()) {
	        auto s= *changedSet.begin();
  	//	errs() << "2 Instruction: " << s << " : " << *s  << inMap[s] << " " << outMap[s] << " inMap.size: " << inMap[s]->size() << '\n';
		changedSet.erase(changedSet.begin()); //cannot use reference as erase begin() iterator;
		inMap[s]->clear();
		
		for(Instruction* P : getPredecessors(s)){
		   inMap[s]->insert(outMap[P]->begin(), outMap[P]->end());
		}

		Gen.clear();
		tmp.clear();
		if (isDef(s)) { // a set of locally available definitions;
		   Gen.insert(s);
		}

	        Gen.insert(inMap[s]->begin(), inMap[s]->end());

		if (*outMap[s] != Gen){
		for(Instruction* P : getSuccessors(s)){
		   changedSet.insert(P);
		}
		}

		outMap[s]->clear();
		outMap[s]->insert(Gen.begin(), Gen.end());

	   }

        }
        
        virtual std::string getAnalysisName() override{
            return "ReachDef";
        }
    };
    
    char ReachDefAnalysis::ID = 1;
    static RegisterPass<ReachDefAnalysis> X("ReachDef", "Reach Definition Analysis",
                                            false /* Only looks at CFG */,
                                            false /* Analysis Pass */);
}
