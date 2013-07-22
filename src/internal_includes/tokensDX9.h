
static const uint32_t D3D9SHADER_TYPE_VERTEX = 0xFFFE0000;
static const uint32_t D3D9SHADER_TYPE_PIXEL = 0xFFFF0000;

static SHADER_TYPE DecodeShaderTypeDX9(const uint32_t ui32Token)
{
    uint32_t ui32Type = ui32Token & 0xFFFF0000;
    if(ui32Type == D3D9SHADER_TYPE_VERTEX)
        return VERTEX_SHADER;

    if(ui32Type == D3D9SHADER_TYPE_PIXEL)
        return PIXEL_SHADER;

    return INVALID_SHADER;
}

static uint32_t DecodeProgramMajorVersionDX9(const uint32_t ui32Token)
{
    return ((ui32Token)>>8)&0xFF;
}

static uint32_t DecodeProgramMinorVersionDX9(const uint32_t ui32Token)
{
    return ui32Token & 0xFF;
}

typedef enum
{
    OPCODE_DX9_NOP          = 0,
    OPCODE_DX9_MOV          ,
    OPCODE_DX9_ADD          ,
    OPCODE_DX9_SUB          ,
    OPCODE_DX9_MAD          ,
    OPCODE_DX9_MUL          ,
    OPCODE_DX9_RCP          ,
    OPCODE_DX9_RSQ          ,
    OPCODE_DX9_DP3          ,
    OPCODE_DX9_DP4          ,
    OPCODE_DX9_MIN          ,
    OPCODE_DX9_MAX          ,
    OPCODE_DX9_SLT          ,
    OPCODE_DX9_SGE          ,
    OPCODE_DX9_EXP          ,
    OPCODE_DX9_LOG          ,
    OPCODE_DX9_LIT          ,
    OPCODE_DX9_DST          ,
    OPCODE_DX9_LRP          ,
    OPCODE_DX9_FRC          ,
    OPCODE_DX9_M4x4         ,
    OPCODE_DX9_M4x3         ,
    OPCODE_DX9_M3x4         ,
    OPCODE_DX9_M3x3         ,
    OPCODE_DX9_M3x2         ,
    OPCODE_DX9_CALL         ,
    OPCODE_DX9_CALLNZ       ,
    OPCODE_DX9_LOOP         ,
    OPCODE_DX9_RET          ,
    OPCODE_DX9_ENDLOOP      ,
    OPCODE_DX9_LABEL        ,
    OPCODE_DX9_DCL          ,
    OPCODE_DX9_POW          ,
    OPCODE_DX9_CRS          ,
    OPCODE_DX9_SGN          ,
    OPCODE_DX9_ABS          ,
    OPCODE_DX9_NRM          ,
    OPCODE_DX9_SINCOS       ,
    OPCODE_DX9_REP          ,
    OPCODE_DX9_ENDREP       ,
    OPCODE_DX9_IF           ,
    OPCODE_DX9_IFC          ,
    OPCODE_DX9_ELSE         ,
    OPCODE_DX9_ENDIF        ,
    OPCODE_DX9_BREAK        ,
    OPCODE_DX9_BREAKC       ,
    OPCODE_DX9_MOVA         ,
    OPCODE_DX9_DEFB         ,
    OPCODE_DX9_DEFI         ,

    OPCODE_DX9_TEXCOORD     = 64,
    OPCODE_DX9_TEXKILL      ,
    OPCODE_DX9_TEX          ,
    OPCODE_DX9_TEXBEM       ,
    OPCODE_DX9_TEXBEML      ,
    OPCODE_DX9_TEXREG2AR    ,
    OPCODE_DX9_TEXREG2GB    ,
    OPCODE_DX9_TEXM3x2PAD   ,
    OPCODE_DX9_TEXM3x2TEX   ,
    OPCODE_DX9_TEXM3x3PAD   ,
    OPCODE_DX9_TEXM3x3TEX   ,
    OPCODE_DX9_RESERVED0    ,
    OPCODE_DX9_TEXM3x3SPEC  ,
    OPCODE_DX9_TEXM3x3VSPEC ,
    OPCODE_DX9_EXPP         ,
    OPCODE_DX9_LOGP         ,
    OPCODE_DX9_CND          ,
    OPCODE_DX9_DEF          ,
    OPCODE_DX9_TEXREG2RGB   ,
    OPCODE_DX9_TEXDP3TEX    ,
    OPCODE_DX9_TEXM3x2DEPTH ,
    OPCODE_DX9_TEXDP3       ,
    OPCODE_DX9_TEXM3x3      ,
    OPCODE_DX9_TEXDEPTH     ,
    OPCODE_DX9_CMP          ,
    OPCODE_DX9_BEM          ,
    OPCODE_DX9_DP2ADD       ,
    OPCODE_DX9_DSX          ,
    OPCODE_DX9_DSY          ,
    OPCODE_DX9_TEXLDD       ,
    OPCODE_DX9_SETP         ,
    OPCODE_DX9_TEXLDL       ,
    OPCODE_DX9_BREAKP       ,

    OPCODE_DX9_PHASE        = 0xFFFD,
    OPCODE_DX9_COMMENT      = 0xFFFE,
    OPCODE_DX9_END          = 0xFFFF,

    OPCODE_DX9_FORCE_DWORD  = 0x7fffffff,   // force 32-bit size enum
} OPCODE_TYPE_DX9;

static OPCODE_TYPE_DX9 DecodeOpcodeTypeDX9(const uint32_t ui32Token)
{
    return (OPCODE_TYPE_DX9)(ui32Token & 0x0000FFFF);
}

static uint32_t DecodeInstructionLengthDX9(const uint32_t ui32Token)
{
    return (ui32Token & 0x0F000000)>>24;
}

static uint32_t DecodeCommentLengthDX9(const uint32_t ui32Token)
{
    return (ui32Token & 0x7FFF0000)>>16;
}

static uint32_t DecodeOperandRegisterNumberDX9(const uint32_t ui32Token)
{
    return ui32Token & 0x000007FF;
}

typedef enum
{
    OPERAND_TYPE_DX9_TEMP           =  0, // Temporary Register File
    OPERAND_TYPE_DX9_INPUT          =  1, // Input Register File
    OPERAND_TYPE_DX9_CONST          =  2, // Constant Register File
    OPERAND_TYPE_DX9_ADDR           =  3, // Address Register (VS)
    OPERAND_TYPE_DX9_TEXTURE        =  3, // Texture Register File (PS)
    OPERAND_TYPE_DX9_RASTOUT        =  4, // Rasterizer Register File
    OPERAND_TYPE_DX9_ATTROUT        =  5, // Attribute Output Register File
    OPERAND_TYPE_DX9_TEXCRDOUT      =  6, // Texture Coordinate Output Register File
    OPERAND_TYPE_DX9_OUTPUT         =  6, // Output register file for VS3.0+
    OPERAND_TYPE_DX9_CONSTINT       =  7, // Constant Integer Vector Register File
    OPERAND_TYPE_DX9_COLOROUT       =  8, // Color Output Register File
    OPERAND_TYPE_DX9_DEPTHOUT       =  9, // Depth Output Register File
    OPERAND_TYPE_DX9_SAMPLER        = 10, // Sampler State Register File
    OPERAND_TYPE_DX9_CONST2         = 11, // Constant Register File  2048 - 4095
    OPERAND_TYPE_DX9_CONST3         = 12, // Constant Register File  4096 - 6143
    OPERAND_TYPE_DX9_CONST4         = 13, // Constant Register File  6144 - 8191
    OPERAND_TYPE_DX9_CONSTBOOL      = 14, // Constant Boolean register file
    OPERAND_TYPE_DX9_LOOP           = 15, // Loop counter register file
    OPERAND_TYPE_DX9_TEMPFLOAT16    = 16, // 16-bit float temp register file
    OPERAND_TYPE_DX9_MISCTYPE       = 17, // Miscellaneous (single) registers.
    OPERAND_TYPE_DX9_LABEL          = 18, // Label
    OPERAND_TYPE_DX9_PREDICATE      = 19, // Predicate register
    OPERAND_TYPE_DX9_FORCE_DWORD  = 0x7fffffff,         // force 32-bit size enum
} OPERAND_TYPE_DX9;

static OPERAND_TYPE_DX9 DecodeOperandTypeDX9(const uint32_t ui32Token)
{
    return (OPERAND_TYPE_DX9)(((ui32Token & 0x70000000) >> 28) |
            ((ui32Token & 0x00001800) >> 8));
}

static uint32_t CreateOperandTokenDX9(const uint32_t ui32RegNum, const OPERAND_TYPE_DX9 eType)
{
    uint32_t ui32Token = ui32RegNum;
    ui32Token |= (eType <<28) & 0x70000000;
    ui32Token |= (eType <<8) & 0x00001800;
    return ui32Token;
}

static uint32_t DecodeUsageDX9(const uint32_t ui32Token)
{
    return ui32Token & 0x0000000f;
}

static uint32_t DecodeUsageIndexDX9(const uint32_t ui32Token)
{
    return (ui32Token & 0x000f0000)>>16;
}

static uint32_t DecodeOperandIsRelativeAddressModeDX9(const uint32_t ui32Token)
{
    return ui32Token & (1<<13);
}

static const uint32_t DX9_SWIZZLE_SHIFT = 16;
#define NO_SWIZZLE_DX9 ((0<<DX9_SWIZZLE_SHIFT)|(1<<DX9_SWIZZLE_SHIFT)|(2<<DX9_SWIZZLE_SHIFT)|(3<<DX9_SWIZZLE_SHIFT))

#define REPLICATE_SWIZZLE_DX9(CHANNEL) ((CHANNEL<<DX9_SWIZZLE_SHIFT)|(CHANNEL<<(DX9_SWIZZLE_SHIFT+2))|(CHANNEL<<(DX9_SWIZZLE_SHIFT+4))|(CHANNEL<<(DX9_SWIZZLE_SHIFT+6)))

static uint32_t DecodeOperandSwizzleDX9(const uint32_t ui32Token)
{
    return ui32Token & 0x00FF0000;
}

static const uint32_t DX9_WRITEMASK_0 = 0x00010000;  // Component 0 (X;Red)
static const uint32_t DX9_WRITEMASK_1 = 0x00020000;  // Component 1 (Y;Green)
static const uint32_t DX9_WRITEMASK_2 = 0x00040000;  // Component 2 (Z;Blue)
static const uint32_t DX9_WRITEMASK_3 = 0x00080000;  // Component 3 (W;Alpha)
static const uint32_t DX9_WRITEMASK_ALL = 0x000F0000;  // All Components

static uint32_t DecodeDestWriteMaskDX9(const uint32_t ui32Token)
{
    return ui32Token & DX9_WRITEMASK_ALL;
}

