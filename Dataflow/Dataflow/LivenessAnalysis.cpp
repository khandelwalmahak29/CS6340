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
