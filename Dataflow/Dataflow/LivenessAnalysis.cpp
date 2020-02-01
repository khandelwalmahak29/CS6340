#include "DataflowAnalysis.h"

namespace dataflow{
    struct LivenessAnalysis: public DataflowAnalysis{
        static char ID;
        LivenessAnalysis() : DataflowAnalysis(ID){}
        
    protected:
        /**
         *  Implement your analysis in this function. Store your results in DataflowAnalysis::inMap and
         *  DataflowAnalysis:outMap.
         */
        void doAnalysis(Function &F) override{

	SetVector<Instruction*> changedSet;
        for (inst_iterator I = inst_begin(F), E= inst_end(F); I != E; ++I){
		changedSet.insert(&(*I));
		/*
		errs() << "Instruction: " << *I << "\n"; 
		errs() << "Use set: [";
		for (Use& U : I->operands()){
			Value* v = U.get();
			// Check if Value v is a local variable.
			if(isa<Instruction>(v))
			errs() << *v << ", ";
	        }
		errs() << "]\n";
		*/
	}

	SetVector<Value*> Gen, tmp, in, out;
	
	while(!changedSet.empty()) {
	        auto s= *changedSet.begin();
  	//	errs() << "2 Instruction: " << s << " : " << *s  << inMap[s] << " " << outMap[s] << " inMap.size: " << inMap[s]->size() << '\n';
		changedSet.erase(changedSet.begin()); //cannot use reference as erase begin() iterator;
		in = *inMap[s];
		out = *outMap[s];
	//
	
		for(Instruction* P : getSuccessors(s)){
		   outMap[s]->insert(inMap[P]->begin(), inMap[P]->end());
		}

		for (Use& U : s->operands()){
			Value* v = U.get();
			// Check if Value v is a local variable.
			if(isa<Instruction>(v)) {
			  inMap[s]->insert(v);
			//errs() << *v << ", ";
			}
	        }
		
		inMap[s]->insert(outMap[s]->begin(), outMap[s]->end());
		if (isDef(s)) { // a set of locally available definitions;
            	for(SetVector<Value*>::iterator V = inMap[s]->begin(), VE = inMap[s]->end(); V != VE; ++V){
			if (*V == s){
			//errs() << *V << ", ";
			inMap[s]->erase(V);
			break;
			}
		}
		}

		if (*inMap[s] != in){
		for(Instruction* P : getPredecessors(s)){
		   changedSet.insert(P);
		}
		}
	   }
        }
        
        virtual std::string getAnalysisName() override{
            return "Liveness Analysis";
        }
    };
    
    char LivenessAnalysis::ID = 1;
    static RegisterPass<LivenessAnalysis> X("Liveness", "Liveness Analysis",
                                            false /* Only looks at CFG */,
                                            false /* Analysis Pass */);
}
