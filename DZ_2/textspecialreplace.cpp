#include "textspecialreplace.h"



TextSpecialReplace::TextSpecialReplace(QString text)
{
    for(int i = 0; i<symbols.size(); i++) {
        while(1) {
        qint32 fnd = text.indexOf(symbols[i]);
        if(fnd==-1) break;
        text.remove(fnd, symbols[i].length());
        text.insert(fnd, subs[i]);
        }
    }
    txt = text;
}
