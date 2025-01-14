// Copyright (c) 2017 Samsung Electronics Co., LTD
// Distributed under the MIT License.
// See the LICENSE file in the project root for more information.
#pragma once

#include "cor.h"
#include "cordebug.h"

#include <list>
#include <string>
#include <vector>

namespace netcoredbg
{

class TypePrinter
{
    static HRESULT NameForTypeRef(mdTypeRef tkTypeRef, IMetaDataImport *pImport, std::string &mdName);
    static HRESULT AddGenericArgs(ICorDebugType *pType, std::list<std::string> &args);
    static PCCOR_SIGNATURE NameForTypeSig(PCCOR_SIGNATURE typePtr, const std::vector<std::string> &args, IMetaDataImport *pImport, std::string &out, std::string &appendix);
public:
    static HRESULT AddGenericArgs(ICorDebugFrame *pFrame, std::list<std::string> &args);
    static HRESULT NameForTypeDef(mdTypeDef tkTypeDef, IMetaDataImport *pImport, std::string &mdName,
                                  std::list<std::string> *args);
    static HRESULT NameForToken(mdToken mb, IMetaDataImport *pImport, std::string &mdName, bool bClassName,
                                std::list<std::string> *args);
    static HRESULT NameForTypeByToken(mdToken mb, IMetaDataImport *pImport, std::string &mdName, std::list<std::string> *args);
    static HRESULT NameForTypeByType(ICorDebugType *pType, std::string &mdName);
    static HRESULT NameForTypeByValue(ICorDebugValue *pValue, std::string &mdName);
    static void NameForTypeSig(PCCOR_SIGNATURE typePtr, ICorDebugType *enclosingType, IMetaDataImport *pImport, std::string &typeName);
    static HRESULT GetTypeOfValue(ICorDebugType *pType, std::string &output);
    static HRESULT GetTypeOfValue(ICorDebugValue *pValue, std::string &output);
    static HRESULT GetTypeOfValue(ICorDebugType *pType, std::string &elementType, std::string &arrayType);
    static HRESULT GetMethodName(ICorDebugFrame *pFrame, std::string &output);
    static HRESULT GetTypeAndMethod(ICorDebugFrame *pFrame, std::string &typeName, std::string &methodName);
    static std::string RenameToSystem(const std::string &typeName);
    static std::string RenameToCSharp(const std::string &typeName);
};

} // namespace netcoredbg
