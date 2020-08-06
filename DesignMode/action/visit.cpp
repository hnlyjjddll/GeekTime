//
// Created by jdl on 2020/8/6.
//

#include "visit.h"

void PdfFile::Visit(Visitor& oVisit){
    cout<<"visit pdf file"<<endl;
    oVisit.Visit(*this);
}

void WordFile::Visit(Visitor& oVisit){
    cout<<"visit word file"<<endl;
    oVisit.Visit(*this);
}

void Extract::Visit(PdfFile& oPdfFile){
    cout<<"do extract pdf file"<<endl;
}

void Extract::Visit(WordFile& oPdfFile){
    cout<<"do extract word file"<<endl;
}

void Compress::Visit(PdfFile& oPdfFile){
    cout<<"do compress pdf file"<<endl;
}

void Compress::Visit(WordFile& oPdfFile){
    cout<<"do compress word file"<<endl;
}


int main(void){
    std::vector<shared_ptr<IFile>> vecFile;
    vecFile.push_back(make_shared<PdfFile>());
    vecFile.push_back(make_shared<WordFile>());
    Extract oExtract;
    Compress oCompress;
    for(auto poFile: vecFile){
        poFile->Visit(oExtract);
        poFile->Visit(oCompress);
    }
    return 0;
}