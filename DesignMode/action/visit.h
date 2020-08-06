//
// Created by jdl on 2020/8/6.
//

#ifndef STUDY_VISIT_H
#define STUDY_VISIT_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

class Extract;

class IFile{
public:
    virtual void ExtractFile2Txt(Extract& oExtract){}
};

class PdfFile:public IFile{
public:
    void ExtractFile2Txt(Extract& oExtract);
};

class WordFile:public IFile{
public:
    void ExtractFile2Txt(Extract& oExtract);
};

class Extract{
public:
    void ExtractFile2Txt(PdfFile& oPdfFile);

    void ExtractFile2Txt(WordFile& oPdfFile);
};

#endif //STUDY_VISIT_H
