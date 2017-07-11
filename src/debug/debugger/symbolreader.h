static const char *SymbolReaderDllName = "SOS.NETCore";
static const char *SymbolReaderClassName = "SOS.SymbolReader";

typedef  int (*ReadMemoryDelegate)(ULONG64, char *, int);
typedef  PVOID (*LoadSymbolsForModuleDelegate)(const char*, BOOL, ULONG64, int, ULONG64, int, ReadMemoryDelegate);
typedef  void (*DisposeDelegate)(PVOID);
typedef  BOOL (*ResolveSequencePointDelegate)(PVOID, const char*, unsigned int, unsigned int*, unsigned int*);
typedef  BOOL (*GetLocalVariableNameAndScope)(PVOID, int, int, BSTR*, unsigned int*, unsigned int*);
typedef  BOOL (*GetLineByILOffsetDelegate)(PVOID, mdMethodDef, ULONG64, ULONG *, BSTR*);
typedef  BOOL (*GetStepRangesFromIPDelegate)(PVOID, int, mdMethodDef, unsigned int*, unsigned int*);

BOOL SafeReadMemory (TADDR offset, PVOID lpBuffer, ULONG cb,
                     PULONG lpcbBytesRead);

class SymbolReader
{
private:
    PVOID m_symbolReaderHandle;

    static std::string coreClrPath;
    static LoadSymbolsForModuleDelegate loadSymbolsForModuleDelegate;
    static DisposeDelegate disposeDelegate;
    static ResolveSequencePointDelegate resolveSequencePointDelegate;
    static GetLocalVariableNameAndScope getLocalVariableNameAndScopeDelegate;
    static GetLineByILOffsetDelegate getLineByILOffsetDelegate;
    static GetStepRangesFromIPDelegate getStepRangesFromIPDelegate;

    static HRESULT PrepareSymbolReader();

    HRESULT LoadSymbolsForPortablePDB(
        WCHAR* pModuleName,
        BOOL isInMemory,
        BOOL isFileLayout,
        ULONG64 peAddress,
        ULONG64 peSize,
        ULONG64 inMemoryPdbAddress,
        ULONG64 inMemoryPdbSize);

public:
    SymbolReader()
    {
        m_symbolReaderHandle = 0;
    }

    ~SymbolReader()
    {
        if (m_symbolReaderHandle != 0)
        {
            disposeDelegate(m_symbolReaderHandle);
            m_symbolReaderHandle = 0;
        }
    }

    static void SetCoreCLRPath(const std::string &path) { coreClrPath = path; }

    HRESULT LoadSymbols(IMetaDataImport* pMD, ICorDebugModule* pModule);
    HRESULT GetLineByILOffset(mdMethodDef MethodToken, ULONG64 IlOffset, ULONG *pLinenum, WCHAR* pwszFileName, ULONG cchFileName);
    HRESULT GetNamedLocalVariableAndScope(ICorDebugILFrame * pILFrame, mdMethodDef methodToken, ULONG localIndex, WCHAR* paramName, ULONG paramNameLen, ICorDebugValue **ppValue, ULONG32* pIlStart, ULONG32* pIlEnd);
    HRESULT ResolveSequencePoint(WCHAR* pFilename, ULONG32 lineNumber, TADDR mod, mdMethodDef* pToken, ULONG32* pIlOffset);
    HRESULT GetStepRangesFromIP(ULONG64 ip, mdMethodDef MethodToken, ULONG32 *ilStartOffset, ULONG32 *ilEndOffset);
};
