
#include "reflect.h"
#include <stdlib.h>

static uint32_t* ReadStringFromTokenStream(const uint32_t* tokens, char* str)
{
    char* charTokens = (char*) tokens;
    char nextCharacter = *charTokens++;
    int length = 0;

    //Add each individual character until
    //a terminator is found.
    while(nextCharacter != 0) {

        str[length++] = nextCharacter;

        if(length > MAX_RESOURCE_BINDING_NAME_LENGTH)
        {
            //Need to continue in order to return the token stream
            //at the end of the string.
            length--;
        }

        nextCharacter = *charTokens++;
    }

    str[length] = '\0';

    //return (charTokens + 3) &~ 3;
    return (uint32_t*)charTokens;
}

static const uint32_t* ReadResourceBinding(const uint32_t* pui32FirstResourceToken, const uint32_t* pui32Tokens, ResourceBinding* psBinding)
{
    uint32_t ui32NameOffset = *pui32Tokens++;

    ReadStringFromTokenStream((const uint32_t*)((const char*)pui32FirstResourceToken+ui32NameOffset), psBinding->Name);

    psBinding->eType = *pui32Tokens++;
    psBinding->ui32ReturnType = *pui32Tokens++;
    psBinding->ui32Dimension = *pui32Tokens++;
    psBinding->ui32NumSamples = *pui32Tokens++;
    psBinding->ui32BindPoint = *pui32Tokens++;
    psBinding->ui32BindCount = *pui32Tokens++;
    psBinding->ui32Flags = *pui32Tokens++;

    return pui32Tokens;
}

void ReadResources(const uint32_t* pui32Tokens,//in
                   ShaderInfo* psShaderInfo)//out
{
    ResourceBinding* psBindings;
    const uint32_t* pui32ConstantBuffers;
    const uint32_t* pui32ResourceBindings;
    const uint32_t* pui32FirstToken = pui32Tokens;
    uint32_t i;

    uint32_t ui32NumConstantBuffers = *pui32Tokens++;
    uint32_t ui32ConstantBufferOffset = *pui32Tokens++;

    uint32_t ui32NumResourceBindings = *pui32Tokens++;
    uint32_t ui32ResourceBindingOffset = *pui32Tokens++;
    uint32_t ui32ShaderModel = *pui32Tokens++;
    uint32_t ui32CompileFlags = *pui32Tokens++;//D3DCompile flags? http://msdn.microsoft.com/en-us/library/gg615083(v=vs.85).aspx

    pui32ConstantBuffers = (const uint32_t*)((const char*)pui32FirstToken + ui32ConstantBufferOffset);
    pui32ResourceBindings = (const uint32_t*)((const char*)pui32FirstToken + ui32ResourceBindingOffset);

    psBindings = malloc(sizeof(ResourceBinding)*ui32NumResourceBindings);

    psShaderInfo->ui32NumResourceBindings = ui32NumResourceBindings;
    psShaderInfo->psResourceBindings = psBindings;

    for(i=0; i < ui32NumResourceBindings; ++i)
    {
        pui32ResourceBindings = ReadResourceBinding(pui32FirstToken, pui32ResourceBindings, psBindings+i);
    }
}

int GetResourceFromBindingPoint(uint32_t ui32BindPoint, ShaderInfo* psShaderInfo, ResourceBinding** ppsOutBinding)
{
    uint32_t i;
    const uint32_t ui32NumBindings = psShaderInfo->ui32NumResourceBindings;
    ResourceBinding* psBindings = psShaderInfo->psResourceBindings;

    for(i=0; i<ui32NumBindings; ++i)
    {
        if(psBindings[i].ui32BindPoint == ui32BindPoint)
        {
            *ppsOutBinding = psBindings + i;
            return 1;
        }
    }
    return 0;
}

#if 0
switch(type)
{

    glGetSubroutineUniformLocation
    glGetSubroutineIndex


    uint32_t ui32Program;

    glGetIntegerv(GL_CURRENT_PROGRAM, &ui32Program);

    uint32_t ui32Location = glGetUniformLocation(program, Name);

    case RTYPE_CBUFFER:
    {
        break;
    }
    case RTYPE_TBUFFER:
    {
        break;
    }
    case RTYPE_TEXTURE:
    {
        break;
    }
    case RTYPE_SAMPLER:
    {
        break;
    }
    case RTYPE_UAV_RWTYPED:
    {
        break;
    }
    case RTYPE_STRUCTURED:
    {
        break;
    }
    case RTYPE_UAV_RWSTRUCTURED:
    {
        break;
    }
    case RTYPE_BYTEADDRESS:
    {
        break;
    }
    case RTYPE_UAV_RWBYTEADDRESS:
    {
        break;
    }
    case RTYPE_UAV_APPEND_STRUCTURED:
    {
        break;
    }
    case RTYPE_UAV_CONSUME_STRUCTURED:
    {
        break;
    }
    case RTYPE_UAV_RWSTRUCTURED_WITH_COUNTER:
    {
        break;
    }
}
#endif
