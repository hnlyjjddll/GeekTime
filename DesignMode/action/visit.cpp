//
// Created by jdl on 2020/8/6.
//

#include "visit.h"

void PdfFile::ExtractFile2Txt(Extract& oExtract){
    cout<<"extract pdf file"<<endl;
    oExtract.ExtractFile2Txt(*this);
}

void WordFile::ExtractFile2Txt(Extract& oExtract){
    cout<<"extract word file"<<endl;
    oExtract.ExtractFile2Txt(*this);
}

void Extract::ExtractFile2Txt(PdfFile& oPdfFile){
    cout<<"do extract pdf file"<<endl;
}

void Extract::ExtractFile2Txt(WordFile& oPdfFile){
    cout<<"do extract word file"<<endl;
}


int main(void){
    std::vector<shared_ptr<IFile>> vecFile;
    vecFile.push_back(make_shared<PdfFile>());
    vecFile.push_back(make_shared<WordFile>());
    Extract oExtract;
    for(auto poFile: vecFile){
        poFile->ExtractFile2Txt(oExtract);
    }
    return 0;
}