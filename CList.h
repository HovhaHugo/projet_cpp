
#ifndef CEXCEPTION_H_CLIST_H
#define CEXCEPTION_H_CLIST_H

template<class Type>
class CList {

public:
    CList();
    CList(Type* ptypeList, unsigned int uiSize);
    CList(CList& LISList);
    ~CList();
    void LISSetSize(unsigned int uiSize);
    void LISAddElement(Type* ptypeToAdd);
    void LISSetElement(CList<Type>, unsigned int uiIndex);
    Type LISGetElement(unsigned int uiIndex);

private:
    Type* ptypeLISList;
    unsigned int uiLISSize;


};



#endif //CEXCEPTION_H_CLIST_H
