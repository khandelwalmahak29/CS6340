#include "DataflowAnalysis.h"

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
