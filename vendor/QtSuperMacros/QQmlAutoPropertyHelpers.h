#ifndef QQMLAUTOPROPERTYHELPERS_H
#define QQMLAUTOPROPERTYHELPERS_H

#include <QObject>

#include "QQmlHelpersCommon.h"

// NOTE : individual macros for getter, setter, notifier, and member

#define QML_AUTO_GETTER(type, name) \
    CheapestType<type>::type_def MAKE_GETTER_NAME(name) (void) const { \
        return m_##name; \
    }

#define QML_AUTO_SETTER(type, name, prefix) \
    bool prefix##name (CheapestType<type>::type_def name) { \
        if (m_##name != name) { \
            m_##name = name; \
            emit name##Changed (); \
            return true; \
        } \
        else { \
            return false; \
        } \
    }

#define QML_AUTO_NOTIFIER(type, name) \
    void name##Changed (void);

#define QML_AUTO_MEMBER(type, name) \
    type m_##name;

// NOTE : actual auto-property helpers

#define QML_WRITABLE_AUTO_PROPERTY(type, name) \
    protected: \
        Q_PROPERTY (type name READ MAKE_GETTER_NAME(name) WRITE set_##name NOTIFY name##Changed) \
    private: \
        QML_AUTO_MEMBER (type, name) \
    public: \
        QML_AUTO_GETTER (type, name) \
        QML_AUTO_SETTER (type, name, set_) \
    Q_SIGNALS: \
        QML_AUTO_NOTIFIER (type, name) \
    private:

#define QML_READONLY_AUTO_PROPERTY(type, name) \
    protected: \
        Q_PROPERTY (type name READ MAKE_GETTER_NAME(name) NOTIFY name##Changed) \
    private: \
        QML_AUTO_MEMBER (type, name) \
    public: \
        QML_AUTO_GETTER (type, name) \
        QML_AUTO_SETTER (type, name, update_) \
    Q_SIGNALS: \
        QML_AUTO_NOTIFIER (type, name) \
    private:

#define QML_CONSTANT_AUTO_PROPERTY(type, name) \
    protected: \
        Q_PROPERTY (type name READ MAKE_GETTER_NAME(name) CONSTANT) \
    private: \
        QML_AUTO_MEMBER (type, name) \
    public: \
        QML_AUTO_GETTER (type, name) \
    private:

// NOTE : test class for all cases

class _Test_QmlAutoProperty_ : public QObject {
    Q_OBJECT

    QML_WRITABLE_AUTO_PROPERTY (bool,      var1)
    QML_WRITABLE_AUTO_PROPERTY (QString,   var2)
    QML_WRITABLE_AUTO_PROPERTY (QObject *, var3)

    QML_READONLY_AUTO_PROPERTY (bool,      var4)
    QML_READONLY_AUTO_PROPERTY (QString,   var5)
    QML_READONLY_AUTO_PROPERTY (QObject *, var6)

    QML_CONSTANT_AUTO_PROPERTY (bool,      var7)
    QML_CONSTANT_AUTO_PROPERTY (QString,   var8)
    QML_CONSTANT_AUTO_PROPERTY (QObject *, var9)
};

#endif // QQMLAUTOPROPERTYHELPERS_H
