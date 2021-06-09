#ifndef TEXTSPECIALREPLACE_H
#define TEXTSPECIALREPLACE_H
#include <QString>
#include <QList>


class TextSpecialReplace
{
public:
    TextSpecialReplace(QString);
    QString txt;

private:
    QList<QString> symbols = QList<QString>() << "#@RUB@" << ".руб" << "#@PROM@" << "#@AUTH@" << "#@EUR@" << "#@R@";
    QList<QString> subs = QList<QString>() << "₽" << "₽" << "‰" << "©" << "€" << "®";

};

#endif // TEXTSPECIALREPLACE_H
