#include "internal_includes/controlFlowGraph.h"
#include "stdlib.h"
#include "stdio.h"

int CFGAddAsPredecessor(CodeBlock* predecessor, CodeBlock* block, int index)
{
	ASSERT((block->numPreds+1) < MAX_BLOCK_LINKS);
	block->preds[block->numPreds].dest = predecessor;
	block->preds[block->numPreds].destIndex = index;

	block->numPreds++;
	return block->numPreds - 1;
}

void CFGAddSuccssorEdge(CodeBlock* from, CodeBlock* to)
{
	int index = from->numSuccs++;
	CodeBlockEdge* edge = &from->succs[index];

	ASSERT(from->numSuccs < MAX_BLOCK_LINKS);

	edge->dest = to;
	edge->destIndex = CFGAddAsPredecessor(from, to, index);
}

void CFGAddInstruction(CodeBlock* block, Instruction* inst)
{
	block->apsInsts[block->numInsts++] = inst;
}

static int AddCodeBlock(ControlFlowGraph* cfg, Instruction* psInstructions, const int instCount)
{
	int i;
	CodeBlock* block = malloc(sizeof(CodeBlock));

	block->numInsts = 0;
	block->numPreds = 0;
	block->numSuccs = 0;
	block->linkedListNext = NULL;
	block->linkedListPrev = NULL;

	//Enough to hold all of the remaining instructions in the shader.
	//This will consume more memory than is necessary.
	block->apsInsts = malloc(sizeof(Instruction*) * instCount);

	for(i=0; i< instCount; ++i)
	{
		Instruction* inst = &psInstructions[i];
		switch(inst->eOpcode)
		{
			case OPCODE_INTERFACE_CALL:
			case OPCODE_ELSE:
			case OPCODE_ENDSWITCH:
			case OPCODE_ENDIF:
			case OPCODE_CONTINUE:
			case OPCODE_SWITCH:
			case OPCODE_CASE:
			case OPCODE_IF:
			case OPCODE_LOOP:
			case OPCODE_ENDLOOP:
			case OPCODE_BREAK:
			case OPCODE_BREAKC:
			{
				CFGAddInstruction(block, inst);
				//Next instruction belongs in a new block
				i+=1;
				goto AddCodeBlock_End;
			}
			default:
			{
				/* For all other opcodes control flow passes on to the next instruction
				 * and belongs in the same block */

				CFGAddInstruction(block, inst);
			}
		}
	}

AddCodeBlock_End:
	if(cfg->blockListTail)
	{
		cfg->blockListTail->linkedListNext = block;
		block->linkedListPrev = cfg->blockListTail;
	}
	else
	{
		cfg->blockList = block;
	}
	cfg->blockListTail = block;
	cfg->numBlocks++;
	return i;
}

void linkELSEandENDIF(CodeBlock* ifBlock)
{
	CodeBlock* block = ifBlock->linkedListNext;
	CodeBlock* nextBlock;

	CodeBlock* elseBlock = NULL;
	CodeBlock* endifBlock = NULL;

	int depth = 0;

	CFGAddSuccssorEdge(ifBlock, block);

	while(block)
	{
		nextBlock = block->linkedListNext;

		switch(block->apsInsts[block->numInsts-1]->eOpcode)
		{
			case OPCODE_IF://Block ends with if
				depth++;
				break;
			case OPCODE_ELSE://Block ends with else
				if(depth == 0)
				{
					ASSERT(elseBlock == NULL);
					elseBlock = nextBlock;
				}
				break;
			case OPCODE_ENDIF://Block ends with endif
				if(depth == 0)
				{
					ASSERT(endifBlock == NULL);

					endifBlock = nextBlock;

					if(elseBlock)
					{
						//end-of-if-block to endif
						CFGAddSuccssorEdge(elseBlock->linkedListPrev, endifBlock);

						CFGAddSuccssorEdge(ifBlock, elseBlock);

						//After if, before else, goto endif.
						CFGAddSuccssorEdge(elseBlock, endifBlock);
					}
					else
					{
						CFGAddSuccssorEdge(ifBlock, endifBlock);
					}
					return;
				}
				depth--;
				break;
		}
		block = nextBlock;
	}

	ASSERT(0);
}

void linkCONTINUEandBREAKandENDLOOP(CodeBlock* loopBlock)
{
	CodeBlock* block = loopBlock->linkedListNext;
	CodeBlock* nextBlock;
	CodeBlock* endloopBlock = 0;

	int depth = 0;

	CFGAddSuccssorEdge(loopBlock, loopBlock->linkedListNext);

	//Find the corresponding endloop
	while(block)
	{
		nextBlock = block->linkedListNext;

		switch(block->apsInsts[block->numInsts-1]->eOpcode)
		{
			case OPCODE_LOOP://Block ends with loop
				depth++;
				break;
			case OPCODE_SWITCH:
				depth++;
				break;
			case OPCODE_ENDSWITCH:
				depth--;
				break;
			case OPCODE_ENDLOOP://Block ends with endloop
				if(depth == 0)
				{
					endloopBlock = nextBlock;
					goto l_loopForBreaks;
				}
				depth--;
				break;
		}
		block = nextBlock;
	}

	//Link the break, breakc, continue blocks
	l_loopForBreaks:

	block = loopBlock->linkedListNext;

	depth = 0;

	while(block)
	{
		nextBlock = block->linkedListNext;

		switch(block->apsInsts[block->numInsts-1]->eOpcode)
		{
			case OPCODE_LOOP://Block ends with loop
				depth++;
				break;
			case OPCODE_SWITCH:
				depth++;
				break;
			case OPCODE_ENDSWITCH:
				depth--;
				break;
			case OPCODE_BREAK://Block ends with break;
				if(depth == 0)
				{
					CFGAddSuccssorEdge(block, endloopBlock);
				}
				break;
			case OPCODE_BREAKC:
				if(depth == 0)
				{
					CFGAddSuccssorEdge(block, endloopBlock);
					CFGAddSuccssorEdge(block, nextBlock);
				}
				break;
			case OPCODE_CONTINUE://Block ends with continue;
				if(depth == 0)
				{
					CFGAddSuccssorEdge(block, loopBlock->linkedListNext);
				}
				break;
			case OPCODE_ENDLOOP://Block ends with endloop
				if(depth == 0)
				{
					return;
				}
				depth--;
				break;
		}
		block = nextBlock;
	}

	ASSERT(0);
}

static void LinkCodeBlocks(ControlFlowGraph* cfg)
{
	CodeBlock* block = cfg->blockList;
	CodeBlock* nextBlock;

	while(block)
	{
		nextBlock = block->linkedListNext;

		switch(block->apsInsts[block->numInsts-1]->eOpcode)
		{
			case OPCODE_CONTINUE:
			case OPCODE_SWITCH:
			case OPCODE_CASE:
			case OPCODE_ELSE:
			case OPCODE_BREAK:
			case OPCODE_BREAKC:
			{
				break;
			}
			case OPCODE_ENDLOOP:
			case OPCODE_ENDIF:
			case OPCODE_ENDSWITCH:
			case OPCODE_INTERFACE_CALL:
			{
				CFGAddSuccssorEdge(block, nextBlock);
				break;
			}
			case OPCODE_LOOP:
			{
				linkCONTINUEandBREAKandENDLOOP(block);
				break;
			}
			case OPCODE_IF:
			{
				linkELSEandENDIF(block);
				break;
			}
			case OPCODE_RET:
			{
				return;
			}
			default:
			{
				ASSERT(0);
			}
		}
		

		block = nextBlock;
	}
}

void CFGBuildGraph(ControlFlowGraph* cfg, Instruction* psInstructions, const int instCount)
{
	int instructionIndex = 0;
	int instructionsLeft = instCount;

	cfg->numBlocks = 0;
	cfg->root = NULL;
	cfg->blockList = NULL;
	cfg->blockListTail = NULL;

	//Separate instructions into blocks of sequential instructions without branches
	do
	{
		int instructionsConsumed = AddCodeBlock(cfg, &psInstructions[instructionIndex], instructionsLeft);

		instructionsLeft -= instructionsConsumed; 
		instructionIndex += instructionsConsumed;
	}
	while(instructionIndex < instCount);

	//Connect the blocks with predecessor and successor relationships.
	LinkCodeBlocks(cfg);
}

void CFGFreeGraph(ControlFlowGraph* cfg)
{
	CodeBlock* block = cfg->blockList;
	CodeBlock* nextBlock;

	while(block)
	{
		nextBlock = block->linkedListNext;

		free(block->apsInsts);
		free(block);

		block = nextBlock;
	}
}

const char* GetOpcodeString(OPCODE_TYPE eOpcode)
{
	switch(eOpcode)
	{
		case OPCODE_INTERFACE_CALL:
			return "INTERFACE_CALL";
		case OPCODE_ENDSWITCH:
			return "ENDSWITCH";
		case OPCODE_CONTINUE:
			return "CONTINUE";
		case OPCODE_SWITCH:
			return "SWITCH";
		case OPCODE_CASE:
			return "CASE";
		case OPCODE_ENDLOOP:
			return "ENDLOOP";

		case OPCODE_ELSE:
			return "ELSE";
		case OPCODE_ENDIF:
			return "ENDIF";

		case OPCODE_LOOP:
			return "LOOP";

		case OPCODE_IF:
			return "IF";

		case OPCODE_RET:
			return "RET";

		case OPCODE_BREAK:
			return "BREAK";

		case OPCODE_BREAKC:
			return "BREAKC";
		default:
		{
			ASSERT(0);
		}
	}
	return "";
}

void DescribeBlock(CodeBlock* block,FILE* f)
{
	fprintf(f, "'%d", block->apsInsts[0]->id);
	fprintf(f, "-%d", block->apsInsts[block->numInsts-1]->id);
	fprintf(f, "-%s'", GetOpcodeString(block->apsInsts[block->numInsts-1]->eOpcode));
}

void CFGVisualiseBlock(CodeBlock* block, int* depth, FILE* f)
{
	CodeBlock* nextBlock;

	while(block)
	{
		int i;

		nextBlock = block->linkedListNext;

		DescribeBlock(block, f);
		fprintf(f, " : [");

		for(i=0; i< block->numSuccs; ++i)
		{
			CodeBlock* successor = block->succs[i].dest;

			DescribeBlock(successor, f);
			fprintf(f, ", ");
		}

		fprintf(f, "],\n");

		block = nextBlock;
	}
}

//Create an adjacency list representation and write it to a file
void CFGVisualiseGraph(ControlFlowGraph* cfg)
{
	CodeBlock* block = cfg->blockList;
	FILE* f = fopen("CFG.txt", "w");
	int depth = 0;

	fprintf(f, "{\n");
	CFGVisualiseBlock(block, &depth, f);
	fprintf(f, "}\n");

	fclose(f);
}
