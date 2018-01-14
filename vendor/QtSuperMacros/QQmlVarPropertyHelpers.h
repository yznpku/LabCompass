#ifndef QQMLVARPROPERTYHELPERS
#define QQMLVARPROPERTYHELPERS

#include <QObject>

#include "QQmlHelpersCommon.h"

#define QML_WRITABLE_VAR_PROPERTY(type, name) \
    protected: \
        Q_PROPERTY (type name READ MAKE_GETTER_NAME (name) WRITE set_##name NOTIFY name##Changed) \
    private: \
        type m_##name; \
    public: \
        type MAKE_GETTER_NAME (name) (void) const { \
            return m_##name ; \
        } \
    public Q_SLOTS: \
        bool set_##name (type name) { \
            bool ret = false; \
            if ((ret = (m_##name != name))) { \
                m_##name = name; \
                emit name##Changed (m_##name); \
            } \
            return ret; \
        } \
    Q_SIGNALS: \
        void name##Changed (type name); \
    private:

#define QML_READONLY_VAR_PROPERTY(type, name) \
    protected: \
        Q_PROPERTY (type name READ MAKE_GETTER_NAME (name) NOTIFY name##Changed) \
    private: \
        type m_##name; \
    public: \
        type MAKE_GETTER_NAME (name) (void) const { \
            return m_##name ; \
        } \
        bool update_##name (type name) { \
            bool ret = false; \
            if ((ret = (m_##name != name))) { \
                m_##name = name; \
                emit name##Changed (m_##name); \
            } \
            return ret; \
        } \
    Q_SIGNALS: \
        void name##Changed (type name); \
    private:

#define QML_CONSTANT_VAR_PROPERTY(type, name) \
    protected: \
        Q_PROPERTY (type name READ MAKE_GETTER_NAME (name) CONSTANT) \
    private: \
        type m_##name; \
    public: \
        type MAKE_GETTER_NAME (name) (void) const { \
            return m_##name ; \
        } \
    private:

class _QmlVarProperty_ : public QObject {
    Q_OBJECT
    QML_WRITABLE_VAR_PROPERTY (int,     var1)
    QML_READONLY_VAR_PROPERTY (bool,    var2)
    QML_CONSTANT_VAR_PROPERTY (QString, var3)
};

#endif // QQMLVARPROPERTYHELPERS
