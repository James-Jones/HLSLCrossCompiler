#ifndef CTRL_FLOW_GRAPH_H
#define CTRL_FLOW_GRAPH_H

#include "internal_includes/toGLSLInstruction.h"
#include "internal_includes/toGLSLOperand.h"
#include "internal_includes/languages.h"
#include "bstrlib.h"
#include "stdio.h"
#include "internal_includes/debug.h"

typedef struct CodeBlockEdge_TAG
{
    struct CodeBlock_TAG* dest;
    uint32_t destIndex;
} CodeBlockEdge;

//Flow control blocks can nest up to 64 deep per subroutine (and main)
#define MAX_BLOCK_LINKS 64

//The basic block. A length of code sequencially exectued code without any branches.
typedef struct CodeBlock_TAG
{
	int numInsts;
    Instruction** apsInsts;

    //Set of registers live on entry to the block.
    Operand* psLiveIn;
    //Set of registers live on exit from the block (after the block end jump).
    Operand* psLiveOut;

	//Predecessors
	int numPreds;
	CodeBlockEdge preds[MAX_BLOCK_LINKS];
	//Succssors
	int numSuccs;
	CodeBlockEdge succs[MAX_BLOCK_LINKS];

	struct CodeBlock_TAG* linkedListNext, *linkedListPrev;
} CodeBlock;


typedef struct ControlFlowGraph_TAG
{
    CodeBlock* root;

    uint32_t numBlocks;
    CodeBlock* blockList;
	CodeBlock* blockListTail;

} ControlFlowGraph;


void CFGBuildGraph(ControlFlowGraph* cfg, Instruction* insts, const int instCount);
void CFGFreeGraph(ControlFlowGraph* cfg);
void CFGVisualiseGraph(ControlFlowGraph* cfg);

#endif
