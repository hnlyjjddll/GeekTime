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

class Visitor;

class IFile{
public:
    virtual void Visit(Visitor& oVisit){}
};

class PdfFile:public IFile{
public:
    void Visit(Visitor& oVisit);
};

class WordFile:public IFile{
public:
    void Visit(Visitor& oVisit);
};

class Visitor{
public:
    virtual void Visit(PdfFile& oPdfFile){}
    virtual void Visit(WordFile& oWordFile){}
};

class Extract: public Visitor{
public:
    void Visit(PdfFile& oPdfFile);
    void Visit(WordFile& oPdfFile);
};

class Compress: public Visitor{
public:
    void Visit(PdfFile& oPdfFile);
    void Visit(WordFile& oPdfFile);
};


#endif //STUDY_VISIT_H
