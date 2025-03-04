#ifndef DM_DOMUTILS_H
#define DM_DOMUTILS_H

#include <QDomElement>
#include <QString>
#include <QStringList>
#include <QColor>

#define _USE_MATH_DEFINES
#include <math.h>

class DM_DomUtils
{
private:
    static void warning(const QString& message)
    {
        qWarning("%s", message.toLatin1().constData());
    }

public:
    static qreal qrealFromDom(const QDomElement& e, const QString& attribute, qreal defValue)
    {
        qreal value = defValue;
        if (e.hasAttribute(attribute)) {
            const QString s = e.attribute(attribute);
            bool ok;
            value = s.toDouble(&ok);
            if (!ok) {
                warning(QString("'%1' is not a valid qreal syntax for attribute \"%2\" in initialization of \"%3\". Setting value to %4.")
                        .arg(s).arg(attribute).arg(e.tagName()).arg(QString::number(defValue)));
                value = defValue;
            }
        } else {
            warning(QString("\"%1\" attribute missing in initialization of \"%2\". Setting value to %3.")
                    .arg(attribute).arg(e.tagName()).arg(QString::number(value)));
        }

#if defined(isnan)
        // The "isnan" method may not be available on all platforms.
        // Find its equivalent or simply remove these two lines
        if (isnan(value))
            warning(QString("Warning, attribute \"%1\" initialized to Not a Number in \"%2\"")
                    .arg(attribute).arg(e.tagName()));
#endif

        return value;
    }

    static int intFromDom(const QDomElement& e, const QString& attribute, int defValue)
    {
        int value = defValue;
        if (e.hasAttribute(attribute))
        {
            const QString s = e.attribute(attribute);
            bool ok;
            value = s.toInt(&ok);
            if (!ok) {
                warning(QString("'%1' is not a valid integer syntax for attribute \"%2\" in initialization of \"%3\". Setting value to %4.")
                        .arg(s).arg(attribute).arg(e.tagName()).arg(QString::number(defValue)));
                value = defValue;
            }
        } else {
            warning(QString("\"%1\" attribute missing in initialization of \"%2\". Setting value to %3.")
                    .arg(attribute).arg(e.tagName()).arg(QString::number(value)));
        }

        return value;
    }

    static unsigned int uintFromDom(const QDomElement& e, const QString& attribute, unsigned int defValue)
    {
        unsigned int value = defValue;
        if (e.hasAttribute(attribute))
        {
            const QString s = e.attribute(attribute);
            bool ok;
            value = s.toUInt(&ok);
            if (!ok) {
                warning(QString("'%1' is not a valid unsigned integer syntax for attribute \"%2\" in initialization of \"%3\". Setting value to %4.")
                        .arg(s).arg(attribute).arg(e.tagName()).arg(QString::number(defValue)));
                value = defValue;
            }
        } else {
            warning(QString("\"%1\" attribute missing in initialization of \"%2\". Setting value to %3.")
                    .arg(attribute).arg(e.tagName()).arg(QString::number(value)));
        }

        return value;
    }

    static bool boolFromDom(const QDomElement& e, const QString& attribute, bool defValue)
    {
        bool value = defValue;
        if (e.hasAttribute(attribute))
        {
            const QString s = e.attribute(attribute);
            if (s.toLower() == QString("true"))
                value = true;
            else if (s.toLower() == QString("false"))
                value = false;
            else
            {
                warning(QString("'%1' is not a valid boolean syntax for attribute \"%2\" in initialization of \"%3\". Setting value to %4.")
                        .arg(s).arg(attribute).arg(e.tagName()).arg(defValue?"true":"false"));
            }
        } else {
            warning(QString("\"%1\" attribute missing in initialization of \"%2\". Setting value to %3.")
                    .arg(attribute).arg(e.tagName()).arg(value?"true":"false"));
        }

        return value;
    }

    static void setBoolAttribute(QDomElement& element, const QString& attribute, bool value) {
        element.setAttribute(attribute, (value ? "true" : "false"));
    }

    static QDomElement QColorDomElement(const QColor& color, const QString& name, QDomDocument& doc)
    {
        QDomElement de = doc.createElement(name);
        de.setAttribute("red", QString::number(color.red()));
        de.setAttribute("green", QString::number(color.green()));
        de.setAttribute("blue", QString::number(color.blue()));
        return de;
    }

    static QColor QColorFromDom(const QDomElement& e)
    {
        int color[3];
        QStringList attribute;
        attribute << "red" << "green" << "blue";
        for (int i=0; i<attribute.count(); ++i)
            color[i] = intFromDom(e, attribute[i], 0);
        return QColor(color[0], color[1], color[2]);
    }
};

#endif // DM_DOMUTILS_H
